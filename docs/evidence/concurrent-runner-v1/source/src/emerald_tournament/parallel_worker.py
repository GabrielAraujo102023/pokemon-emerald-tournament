"""Persistent spawn worker. Each task still uses one fresh authoritative mGBA core."""
import functools,hashlib,io,json,os,queue,signal,tempfile,threading,time,traceback,uuid,zipfile,multiprocessing
from datetime import datetime,timezone
from pathlib import Path
from . import emu_battle
from .admission import check_runtime
_CONTEXT=None
_ACTIVE_BRIDGE=None

class PipeBridge(emu_battle.Bridge):
    """Windows anonymous pipes are not selectable: one I/O reader, not a simulation thread."""
    def line(self):
        if not hasattr(self,'_lines'):
            self._lines=queue.Queue()
            def reader():
                try:
                    while True:
                        data=self.process.stdout.readline()
                        self._lines.put(data)
                        if not data:return
                except BaseException as e:self._lines.put(e)
            self._reader=threading.Thread(target=reader,daemon=True);self._reader.start()
        try:data=self._lines.get(timeout=30)
        except queue.Empty:raise RuntimeError('Bridge watchdog expired')
        if isinstance(data,BaseException):raise RuntimeError('Bridge reader failed') from data
        if not data:raise RuntimeError('Bridge exited before command completion')
        return data.rstrip(b'\r\n').decode('ascii')

class ManagedBridge(PipeBridge if os.name=='nt' else emu_battle.Bridge):
    def __init__(self,*args,**kwargs):
        global _ACTIVE_BRIDGE
        _ACTIVE_BRIDGE=self
        super().__init__(*args,**kwargs)
    def close(self):
        global _ACTIVE_BRIDGE
        try:super().close()
        finally:_ACTIVE_BRIDGE=None

def watch_parent():
    parent=multiprocessing.parent_process()
    if parent is None:return
    while parent.is_alive():time.sleep(.5)
    bridge=_ACTIVE_BRIDGE
    process=getattr(bridge,'process',None)
    if process is not None and process.poll() is None:
        try:
            process.terminate()
            process.wait(timeout=3)
        except Exception:
            try:process.kill()
            except OSError:pass
    os._exit(75)  # No worker owns SQLite; coordinator death leaves committed rows intact.

def fingerprint(path):
    s=Path(path).stat();return s.st_size,s.st_mtime_ns,s.st_ctime_ns

def initialize(context):
    global _CONTEXT
    signal.signal(signal.SIGINT,signal.SIG_IGN)
    _CONTEXT=context
    for name,expected in context['plan']['execution_hashes'].items():
        if hashlib.sha256((Path(__file__).parent/name).read_bytes()).hexdigest()!=expected:raise ValueError('Execution source changed before worker initialization')
    _CONTEXT['entries']={r['id']:r for r in context['population']['entries']}
    paths=list(context['paths'].values())+list(context['runtime_paths'].values())
    # Parent hashes once at launch; workers pin before reuse and reject changes.
    emu_battle.check_manifest(context['plan']['provenance'],**{k:v for k,v in context['paths'].items() if k!='manifest_path'})
    for k,p in context['runtime_paths'].items():
        if hashlib.sha256(p.read_bytes()).hexdigest()!=context['plan']['runtime_hashes'][k]:raise ValueError('Runtime changed before worker initialization')
    _CONTEXT['fingerprints']={p:fingerprint(p) for p in paths}
    # Cache symbol parsing only; battle bytes/checkpoint are still verified by run_battle.
    emu_battle.elf_symbol=functools.lru_cache(maxsize=128)(emu_battle.elf_symbol)
    emu_battle.Bridge=ManagedBridge
    threading.Thread(target=watch_parent,daemon=True,name='parent-watchdog').start()

def usage():
    try:
        import resource,sys
        own=resource.getrusage(resource.RUSAGE_SELF);child=resource.getrusage(resource.RUSAGE_CHILDREN)
        scale=1 if sys.platform=='darwin' else 1024
        return own.ru_utime+own.ru_stime+child.ru_utime+child.ru_stime,(own.ru_maxrss+child.ru_maxrss)*scale
    except ImportError:return None,None

def archive(folder):
    result=io.BytesIO()
    with zipfile.ZipFile(result,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=3) as z:
        if folder.exists():
            for p in sorted(folder.iterdir()):
                if p.is_file():
                    info=zipfile.ZipInfo(p.name,date_time=(1980,1,1,0,0,0));info.compress_type=zipfile.ZIP_DEFLATED
                    z.writestr(info,p.read_bytes())
    return result.getvalue()

def validate(folder,task,result,context):
    if result['provenance']!=context['plan']['provenance']:raise ValueError('Battle manifest changed')
    for f,k in [('events.bin','trace_sha256'),('initial_parties.bin','initial_party_sha256'),('stopped_parties.bin','stopped_party_sha256')]:
        if hashlib.sha256((folder/f).read_bytes()).hexdigest()!=result[k]:raise ValueError('Capture hash mismatch')
    if context['plan']['mode']!='benchmark':check_runtime(folder,context['plan']['admission_policy'])
    for side in 'ab':
        expected=context['entries'][task['trainer_'+side]]['party']
        actual=json.loads((folder/f'party_{side}.json').read_text())
        if len(actual)!=len(expected):raise ValueError('ARM/source party count mismatch')
        for a,b in zip(actual,expected):
            if (a['species'],a['level'],a['personality'],a['ability'])!=(b['species_id'],b['level'],b['personality'],b['ability_id']):raise ValueError('ARM/source construction mismatch')

def execute(task):
    started=time.perf_counter();cpu_before,_=usage()
    message=dict(ok=False,attempt_id=uuid.uuid4().hex,worker_pid=os.getpid(),artifact=b'',fatal=False)
    work=Path(_CONTEXT['work_root']);work.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='attempt-',dir=work) as temp:
        folder=Path(temp)/'capture'
        try:
            if any(fingerprint(p)!=v for p,v in _CONTEXT['fingerprints'].items()):
                message['fatal']=True;raise ValueError('Pinned execution files changed while workers were running')
            record=emu_battle.run_battle(**{k:task[k] for k in ('trainer_a','trainer_b','seed','max_frames')},**_CONTEXT['paths'],output=folder)
            validate(folder,task,record,_CONTEXT)
            message.update(ok=True,record=record)
        except Exception as e:
            message.update(error_type=type(e).__name__,error_message=str(e),traceback=traceback.format_exc())
        message['artifact']=archive(folder)
    cpu_after,rss=usage()
    message.update(runtime_seconds=time.perf_counter()-started,completed_at=datetime.now(timezone.utc).isoformat(),
                   cpu_seconds=None if cpu_before is None else cpu_after-cpu_before,approx_peak_worker_and_child_bytes=rss)
    return message
