"""Conservative source-based admission; never reconstructs canonical battle RNG."""
import hashlib,json,re
from pathlib import Path
from .teams import reconstruct

def sha(path):return hashlib.sha256(Path(path).read_bytes()).hexdigest()
def evaluate(trainer,generation,policy,upstream):
    reasons=[]; evidence=[]
    if trainer['category'] not in policy['categories']:reasons.append('category not admitted: '+trainer['category'])
    if trainer['double_battle']:reasons.append('double battle flag')
    if not 0<trainer['party_size']<=policy['max_party_size']:reasons.append('party size outside validated scope')
    if trainer['ai_flags'] not in policy['ai_flags']:reasons.append('AI flags outside validated scope')
    for ref in trainer['script_references']:
        path,line=ref.rsplit(':',1)
        source=(upstream/path).read_text().splitlines()[int(line)-1].strip()
        if re.match(r'('+'|'.join(policy['encounter_commands'])+r')\s+'+re.escape(trainer['constant'])+r'\s*,',source):
            evidence.append({'reference':ref,'command':source})
    if not evidence:reasons.append('no audited ordinary encounter command for this concrete entry')
    for item in trainer['battle_items']:
        if item not in policy['trainer_items']:reasons.append('unvalidated trainer item: '+str(item))
    party=reconstruct(trainer,generation)['party'] if trainer['party'] else []
    for mon in party:
        reasons += ['unvalidated move: '+m for m in mon['moves'] if m not in policy['moves']]
        if str(mon['ability_id']) not in policy['abilities']:reasons.append('unvalidated ability: '+str(mon['ability_id']))
        if mon['held_item'] not in policy['held_items']:reasons.append('unvalidated held item: '+str(mon['held_item']))
    return dict(id=trainer['id'],constant=trainer['constant'],category=trainer['category'],category_reason=trainer['classification_reason'],supported=not reasons,reasons=sorted(set(reasons)) or ['All declared capability and ordinary encounter checks passed'],encounter_evidence=evidence,party=party)

def build_population(root):
    root=Path(root);tp=root/'data/generated/trainers.json';gp=root/'data/generated/generation.json';pp=root/'config/admission_policy.json'
    trainers=json.loads(tp.read_text());generation=json.loads(gp.read_text());policy=json.loads(pp.read_text())
    if trainers['pokeemerald_commit']!=generation['pokeemerald_commit']:raise ValueError('Source mismatch')
    entries=[evaluate(t,generation,policy,root/'pokeemerald') for t in trainers['trainers']]
    return dict(schema_version=1,policy=policy,source_commit=trainers['pokeemerald_commit'],inputs={str(p.relative_to(root)):sha(p) for p in (tp,gp,pp)},entries=entries,supported_ids=[t['id'] for t in entries if t['supported']],total_entries=len(entries))

def check_runtime(capture,policy):
    """No unvalidated implicit move may silently enter immutable results."""
    result=json.loads((capture/'battle_result.json').read_text())
    if result.get('validation_overrides'):raise ValueError('Validation intervention is not a tournament battle')
    events=[json.loads(x) for x in (capture/'events.jsonl').read_text().splitlines()]
    for e in events:
        if e['event']=='move_execution' and e['value0'] not in policy['runtime_moves']:raise ValueError(f"Unvalidated executed move {e['value0']}")
    for e in events:
        if e['event']=='trainer_item_selected' and e['value0']!=19:raise ValueError('Unvalidated trainer item execution')
    return result
