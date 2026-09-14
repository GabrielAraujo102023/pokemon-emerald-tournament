"""Preserve the exact executable generation, patched source overlay and runtime."""
import argparse,hashlib,json,shutil,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False)
if subprocess.check_output(['git','-C',str(ROOT/'pokeemerald'),'status','--porcelain']).strip():raise RuntimeError('Upstream is dirty')
paths=['build/pokeemerald/pokeemerald_modern.gba','build/pokeemerald/pokeemerald_modern.elf','build/reports/constructor-ready.ss','build/reports/battle-manifest.json','build/emulator/emerald-mgba-bridge','build/mgba-prefix/lib/libmgba.0.10.5.dylib','build/reports/release-v2-regression.log','build/reports/autonomous-doctor.json','build/layout/layout.json']
paths += [str(x.relative_to(ROOT)) for x in (ROOT/'adapter').glob('*') if x.is_file()]
paths += ['tools/apply_battle_adapter.py','tools/apply_constructor_adapter.py','build/pokeemerald/Makefile']
paths += [str(x.relative_to(ROOT)) for x in (ROOT/'src/emerald_tournament').glob('*.py')]
overlay=[]
for area in ['src','include','data']:
 for x in sorted((ROOT/'build/pokeemerald'/area).rglob('*')):
  if not x.is_file() or x.suffix not in ('.c','.h','.s','.inc'):continue
  rel=x.relative_to(ROOT/'build/pokeemerald');original=ROOT/'pokeemerald'/rel
  if not original.exists() or x.read_bytes()!=original.read_bytes():overlay.append(str(x.relative_to(ROOT)))
paths+=overlay
hashes={}
for name in sorted(set(paths)):
 src=ROOT/name;dst=a.output/name;dst.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(src,dst);hashes[name]=hashlib.sha256(dst.read_bytes()).hexdigest()
report=dict(artifact_hashes=hashes,patched_source_files=overlay,upstream_clean=True,upstream_commit=subprocess.check_output(['git','-C',str(ROOT/'pokeemerald'),'rev-parse','HEAD'],text=True).strip(),scope='Exact executable and overlay used for the covered-normal-singles-v2 league; authorization recorded separately after audit')
(a.output/'release-manifest.json').write_text(json.dumps(report,indent=2)+'\n');print(len(hashes),'pinned files;',len(overlay),'patched source files')
