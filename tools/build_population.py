import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.admission import build_population
root=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);a=p.parse_args()
a.output.mkdir(parents=True,exist_ok=False)
r=build_population(root);(a.output/'population.json').write_text(json.dumps(r,indent=2)+'\n')
print('Admitted',len(r['supported_ids']),'of',r['total_entries'],r['supported_ids'])
