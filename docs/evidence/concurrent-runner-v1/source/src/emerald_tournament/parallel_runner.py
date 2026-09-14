"""Bounded spawn scheduler; only the parent writes SQLite."""
import concurrent.futures as futures
import json,multiprocessing,os,signal,time,traceback,uuid
from datetime import datetime,timezone
from pathlib import Path
from .parallel_platform import run_lock,worker_count
from .parallel_store import Store
from .parallel_tasks import tasks
from .parallel_worker import initialize,execute

def duration(seconds):
    if seconds is None:return 'unknown'
    seconds=int(max(0,seconds));days,seconds=divmod(seconds,86400);hours,seconds=divmod(seconds,3600);minutes,seconds=divmod(seconds,60)
    return f'{days}d {hours}h {minutes}m {seconds}s'

def progress(counts,total,workers,elapsed,new_done):
    rate=new_done/elapsed if elapsed else 0
    eta=counts['remaining']/rate if rate else None
    print(f"Completed: {counts['completed']} / {total} ({counts['completed']/total:.2%}) | Rate: {rate:.2f} battles/s | Elapsed: {duration(elapsed)} | ETA: {duration(eta)} | Failed: {counts['failed']} | Workers: {workers}",flush=True)

def run(plan,context,output,*,workers='auto',inflight=None,limit=None,retry_failed=False,retries=0,progress_seconds=10,verbose=False,new=False,stop_event=None):
    count=worker_count(workers)
    bound=inflight if inflight is not None else count*2
    if bound<count or retries<0 or progress_seconds<=0 or (limit is not None and limit<0):raise ValueError('Invalid scheduler limits')
    if new and output.exists():raise ValueError('--new requires a new output directory; refusing overwrite')
    output.mkdir(parents=True,exist_ok=True)
    with run_lock(output/'runner.lock'):
        db=Store(output/'results.sqlite',plan)
        started=time.perf_counter();before=db.counts();done_now=0;failed_now=0;scheduled=0
        peak=0;cpu_total=0.;runtimes=0.;archive_bytes=0;worker_pids=set();fatal=None
        stop=stop_event if stop_event is not None else __import__('threading').Event()
        previous={}
        def interrupted(signum,frame):
            if not stop.is_set():print('\nInterruption requested: stop scheduling; commit in-flight results, then close.',flush=True)
            stop.set()
        if __import__('threading').current_thread() is __import__('threading').main_thread():
            for name in ('SIGINT','SIGTERM'):
                sig=getattr(signal,name,None)
                if sig is not None:previous[sig]=signal.signal(sig,interrupted)
        existing=before['completed'] or before['failed_attempts']
        print(('Found existing tournament state. Resuming.' if existing else 'Starting new tournament state.')+f" Completed: {before['completed']}; remaining: {before['remaining']}; failed: {before['failed']}; incomplete/unstarted: {before['incomplete']}",flush=True)
        context=dict(context,work_root=output/'work')
        iterator=iter(tasks(plan));pending={};exhausted=False;last_report=started
        try:
            # Spawn even on Unix: workers import safely and never inherit the database connection.
            with futures.ProcessPoolExecutor(max_workers=count,mp_context=multiprocessing.get_context('spawn'),initializer=initialize,initargs=(context,)) as pool:
                def submit(task,attempt):
                    future=pool.submit(execute,task);pending[future]=(task,attempt)
                while True:
                    while not exhausted and not stop.is_set() and len(pending)<bound and (limit is None or scheduled<limit):
                        try:task=next(iterator)
                        except StopIteration:exhausted=True;break
                        state=db.state(task['match_id'])
                        if state=='completed' or (state=='failed' and not retry_failed):continue
                        submit(task,0);scheduled+=1
                    if not pending:break
                    ready,_=futures.wait(pending,timeout=min(progress_seconds,0.5),return_when=futures.FIRST_COMPLETED)
                    for future in ready:
                        task,attempt=pending.pop(future)
                        try:message=future.result()
                        except Exception as e:
                            # Infrastructure failures are real failures, never invented battle outcomes.
                            message=dict(ok=False,fatal=True,attempt_id=uuid.uuid4().hex,error_type=type(e).__name__,error_message=str(e),
                                         traceback=traceback.format_exc(),runtime_seconds=0,completed_at=datetime.now(timezone.utc).isoformat(),worker_pid=0,artifact=b'')
                        db.commit(task,message)  # FULL synchronous transaction before more scheduling.
                        worker_pids.add(message['worker_pid']);runtimes+=message['runtime_seconds'];archive_bytes+=len(message['artifact'])
                        peak=max(peak,message.get('approx_peak_worker_and_child_bytes') or 0)
                        cpu_total+=message.get('cpu_seconds') or 0
                        if message['ok']:done_now+=1
                        else:
                            failed_now+=1
                            if message.get('fatal'):fatal=message['error_message'];stop.set()
                            elif attempt<retries and not stop.is_set():submit(task,attempt+1)
                        if verbose:print(f"{task['ordinal']}: {'completed' if message['ok'] else message['error_type']}",flush=True)
                    now=time.perf_counter()
                    if now-last_report>=progress_seconds:
                        progress(db.counts(),plan['total_battles'],count,now-started,done_now);last_report=now
            after=db.counts();elapsed=time.perf_counter()-started
            summary=dict(plan_id=plan['plan_id'],workers=count,total=plan['total_battles'],**after,
                         completed_this_session=done_now,failed_attempts_this_session=failed_now,
                         elapsed_seconds=elapsed,battles_per_second=done_now/elapsed if elapsed else 0,
                         mean_battle_runtime_seconds=runtimes/(done_now+failed_now) if done_now+failed_now else None,
                         approx_peak_pool_bytes=peak*count if peak else None,
                         measured_worker_and_child_cpu_seconds=cpu_total,archive_bytes_written=archive_bytes,
                         worker_pids=sorted(worker_pids),interrupted=stop.is_set(),fatal_error=fatal,complete=after['completed']==plan['total_battles'])
            sessions=output/'sessions';sessions.mkdir(exist_ok=True)
            (sessions/f'{uuid.uuid4().hex}.json').write_text(json.dumps(summary,indent=2)+'\n')
            progress(after,plan['total_battles'],count,elapsed,done_now)
            return summary
        finally:
            for sig,handler in previous.items():signal.signal(sig,handler)
            db.close()
