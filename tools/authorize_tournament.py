"""Audit the configured conservative league before granting exact authorization."""
import json,sys,subprocess
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'src'))
from emerald_tournament.admission import sha
from emerald_tournament.result_store import identity
from emerald_tournament.tournament import preflight
ROOT=Path(__file__).resolve().parents[1];release=ROOT/'docs/evidence/release-v2'
if (release/'authorization.json').exists():raise RuntimeError('Authorization already exists; never overwrite')
gate=ROOT/'docs/tournament_readiness_gate.md';text=gate.read_text()
assert 'Tournament authorized: no' in text and '- [ ]' not in text
snapshot=json.loads((release/'release-manifest.json').read_text())
for name,digest in snapshot['artifact_hashes'].items():
 assert sha(release/name)==digest and sha(ROOT/name)==digest, name
assert not subprocess.check_output(['git','-C',str(ROOT/'pokeemerald'),'status','--porcelain']).strip()
log=(release/'build/reports/release-v2-regression.log').read_text();assert '54 passed' in log and 'skipped' not in log and 'FAILED' not in log
assert json.loads((release/'build/reports/autonomous-doctor.json').read_text())['build_prerequisites_ready']
evidence=[
 'ring-v2-cycle/ring-v2-long/validation.json','fullrestore-cycle-v2/validation.json','concurrent-items-v2/validation.json',
 'restrictions-status-v2/switch-restrictions-v2/validation.json','restrictions-status-v2/status-proof-v2/validation.json',
 'effects-v2/effect-proof-v2-pp/validation.json','guards-v2/guard-state-v2/validation.json','guards-v2/guard-state-swapped-v2/validation.json',
 'curl-struggle-v2/curl-scratch-proof-v2/validation.json','curl-struggle-v2/struggle-proof-v2/validation.json',
 'smoke-v2/smoke-validation-v2/validation.json','smoke-v2/smoke-v2-replays/validation.json']
checks={}
for name in evidence:
 path=ROOT/'docs/evidence'/name;r=json.loads(path.read_text());assert r['passed'],name;checks[name]=sha(path)
smoke,_,_=preflight(ROOT/'config/smoke_singles.json')
assert smoke==json.loads((ROOT/'runs/smoke-v2/preflight.json').read_text())
assert smoke['supported_ids']==[114,136,320,523,526,532,535,605]
# Require immutable smoke completion and its no-op resume proof, not merely scaffolding.
validation=json.loads((ROOT/'docs/evidence/smoke-v2/smoke-validation-v2/validation.json').read_text());assert validation['resume']['complete'] and validation['resume']['completed']==32 and validation['resume']['newly_completed']==0
config_path=ROOT/'config/tournament_singles.yaml';config=json.loads(config_path.read_text());assert config['mode']=='full' and config['pairing']=='all_pairs' and config['repetitions']==2 and config['max_frames_by_repetition']==[36000,36000]
config['tournament_authorized']=True
# Every semantic execution setting except schedule and budget must equal the smoke.
for k in smoke['config']:
 if k not in ('mode','pairing','max_frames_by_repetition'):assert config[k]==smoke['config'][k],k
execution={k:v for k,v in smoke.items() if k not in ('config','population_sha256','run_id','unique_pairs','expected_battles','schedule')}
authorization=dict(authorized=True,scope='covered-normal-singles-v2; eight of 855 entries, 847 explicit exclusions',config_sha256=__import__('hashlib').sha256((json.dumps(config,indent=2)+'\n').encode()).hexdigest(),population_sha256=smoke['population_sha256'],execution_identity=identity(execution),release_manifest_sha256=sha(release/'release-manifest.json'),evidence=checks,expected_battles=112)
# Additive authorization is last, after all read-only evidence checks pass.
config_path.write_text(json.dumps(config,indent=2)+'\n')
(release/'authorization.json').write_text(json.dumps(authorization,indent=2)+'\n')
gate.write_text(text.replace('Tournament authorized: no','Tournament authorized: yes',1))
full,_,_=preflight(config_path);assert full['expected_battles']==112
(release/'authorized-preflight.json').write_text(json.dumps(full,indent=2)+'\n')
print('Authorized',full['expected_battles'],'battles; run',full['run_id'])
