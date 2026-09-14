"""Profile one real diagnostic battle; no simulator replacements or edited parties."""
import argparse,cProfile,json,pstats,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.parallel_plan import prepare,ROOT
from emerald_tournament.parallel_worker import initialize,execute
from emerald_tournament.parallel_tasks import tasks

def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
 plan,context=prepare(ROOT/'config/parallel_benchmark.json');initialize(dict(context,work_root=a.output/'work'))
 task=next(tasks(plan));profile=cProfile.Profile();result=profile.runcall(execute,task);profile.dump_stats(a.output/'battle.pstats')
 stats=pstats.Stats(profile);entries=[]
 for (file,line,name),(cc,nc,tt,ct,callers) in stats.stats.items():
  if 'emu_battle' in file or 'emu_protocol' in file:entries.append(dict(file=file,line=line,function=name,calls=nc,self_seconds=tt,cumulative_seconds=ct))
 report=dict(passed=result['ok'],task=task,runtime_seconds=result['runtime_seconds'],cpu_seconds=result['cpu_seconds'],functions=sorted(entries,key=lambda x:-x['cumulative_seconds']),note='Cumulative time includes native emulator work while Python waits for replies; it is not pure IPC overhead.')
 (a.output/'profile.json').write_text(json.dumps(report,indent=2)+'\n');(a.output/'capture.zip').write_bytes(result['artifact']);assert result['ok'];print(json.dumps(report,indent=2))
if __name__=='__main__':main()
