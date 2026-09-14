"""Concurrent runner CLI; legacy tournament entry point remains available unchanged."""
import argparse,json,sys,sqlite3
from pathlib import Path
from .parallel_plan import prepare,ROOT
from .parallel_runner import run
from .parallel_store import status
from .parallel_benchmark import benchmark

def main():
    p=argparse.ArgumentParser(description='Durable local multiprocessing for the real Emerald backend')
    sub=p.add_subparsers(dest='command',required=True)
    launch=sub.add_parser('run')
    launch.add_argument('--config',type=Path,default=ROOT/'config/parallel_validation.json')
    launch.add_argument('--output',type=Path,default=ROOT/'runs/concurrent-validation')
    launch.add_argument('--workers',default='auto');launch.add_argument('--inflight',type=int)
    launch.add_argument('--limit',type=int);launch.add_argument('--retry-failed',action='store_true')
    launch.add_argument('--retries',type=int,default=0,help='additional tries per selected failed task, per invocation')
    launch.add_argument('--progress-seconds',type=float,default=10);launch.add_argument('--verbose',action='store_true')
    mode=launch.add_mutually_exclusive_group();mode.add_argument('--new',action='store_true');mode.add_argument('--resume',action='store_true',help='resume is automatic; this additionally requires existing state')
    inspect=sub.add_parser('status');inspect.add_argument('--output',type=Path,default=ROOT/'runs/concurrent-validation')
    planning=sub.add_parser('plan');planning.add_argument('--config',type=Path,default=ROOT/'config/parallel_singles.json')
    bench=sub.add_parser('benchmark');bench.add_argument('--config',type=Path,default=ROOT/'config/parallel_benchmark.json');bench.add_argument('--output',type=Path,required=True);bench.add_argument('--workers',nargs='+',type=int)
    export=sub.add_parser('export');export.add_argument('--output',type=Path,required=True);export.add_argument('--match',required=True);export.add_argument('--destination',type=Path,required=True)
    args=p.parse_args()
    try:
        if args.command=='status':print(json.dumps(status(args.output/'results.sqlite'),indent=2));return 0
        if args.command=='plan':
            plan,_=prepare(args.config,enforce=False)
            print(json.dumps({k:plan[k] for k in ('plan_id','mode','scope','total_battles','trainer_ids','unsupported_ids')},indent=2));return 0
        if args.command=='benchmark':benchmark(args.config,args.output.resolve(),args.workers);return 0
        if args.command=='export':
            from .parallel_export import export_capture
            print(export_capture(args.output.resolve(),args.match,args.destination.resolve()));return 0
        if args.resume and not (args.output/'results.sqlite').exists():raise ValueError('--resume requires an existing results.sqlite')
        plan,context=prepare(args.config)
        if plan['mode']=='benchmark':raise ValueError('Use benchmark command for diagnostic fixtures')
        result=run(plan,context,args.output.resolve(),workers=args.workers,inflight=args.inflight,limit=args.limit,
                   retry_failed=args.retry_failed,retries=args.retries,progress_seconds=args.progress_seconds,verbose=args.verbose,new=args.new)
        print(json.dumps(result,indent=2))
        return 130 if result['interrupted'] else 1 if result['failed'] else 0
    except (ValueError,OSError,RuntimeError,sqlite3.Error) as e:
        print(f'Runner refused/failed: {e}',file=sys.stderr);return 2

if __name__=='__main__':raise SystemExit(main())
