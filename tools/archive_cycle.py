"""Copy completed real-run folders once and record per-file integrity hashes."""
import argparse,hashlib,json,shutil
from pathlib import Path

def main():
 p=argparse.ArgumentParser();p.add_argument('--output',required=True,type=Path);p.add_argument('inputs',nargs='+',type=Path);args=p.parse_args()
 if len({i.name for i in args.inputs})!=len(args.inputs):p.error('Input basenames must be unique')
 args.output.mkdir(parents=True,exist_ok=False)
 for source in args.inputs:
  if source.is_dir():shutil.copytree(source,args.output/source.name)
  else:shutil.copyfile(source,args.output/source.name)
 hashes={str(f.relative_to(args.output)):hashlib.sha256(f.read_bytes()).hexdigest() for f in sorted(args.output.rglob('*')) if f.is_file()}
 (args.output/'artifact_hashes.json').write_text(json.dumps(hashes,indent=2)+'\n')
if __name__=='__main__':main()
