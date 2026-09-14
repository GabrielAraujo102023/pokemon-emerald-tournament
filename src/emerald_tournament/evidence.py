"""Read-only assertions on recorded engine observations; no battle simulation."""
def simultaneous_fullrestore_eligible(state):
    return all(0 < state['hp'][s] < state['max_hp'][s] // 4 and 19 in state['inventory'][s] for s in (0, 1))


def status_applications(observations, field, mask):
    proofs=[]
    for before,after in zip(observations,observations[1:]):
        if before['slots']!=after['slots'] or before['species']!=after['species']:continue
        for side in (0,1):
            if before['hp'][side]>0 and after['hp'][side]>0 and not before[field][side]&mask and after[field][side]&mask:
                proofs.append({'side':side,'before':before,'after':after})
    return proofs


def damage_transitions(observations, critical=False):
    proofs=[]
    for before,after in zip(observations,observations[1:]):
        if before['slots']!=after['slots'] or before['species']!=after['species']:continue
        for side in (0,1):
            if before['hp'][side]>after['hp'][side] and (not critical or after['crit_multiplier']==2):
                proofs.append({'side':side,'before':before,'after':after})
    return proofs


def shadow_tag_active(state, side):
    return state['abilities'][1-side] == 23 and min(state['hp']) > 0


def no_reserve_switches(party, events, side):
    return len(party)==1 and any(e['event']=='move_selected' and e['battler']==side for e in events) and not any(e['event'] in ('switch_selected','replacement') and e['battler']==side for e in events)


def dig_cycles(observations, side, move_slot):
    """Require charge, later release and actual hit, with one PP consumption."""
    proofs=[]
    for i,(before,charged) in enumerate(zip(observations,observations[1:])):
        if before['status3'][side]&128 or not charged['status3'][side]&128 or charged['current_move']!=91:continue
        same=lambda v:v['slots']==charged['slots'] and v['species']==charged['species']
        # Last PP transition into this charged move must consume exactly one.
        use=next(((a,b) for a,b in reversed(list(zip(observations[:i+1],observations[1:i+2]))) if same(a) and same(b) and a['pp'][side][move_slot]!=b['pp'][side][move_slot]),None)
        if not use or use[1]['current_move']!=91 or use[0]['pp'][side][move_slot]-use[1]['pp'][side][move_slot]!=1:continue
        released=next((v for v in observations[i+2:] if same(v) and not v['status3'][side]&128 and v['current_move']==91),None)
        if not released:continue
        hit=next((v for v in observations[i+2:] if v['frame']>=released['frame'] and same(v) and v['current_move']==91 and v['attacker']==side and v['hp'][1-side]<charged['hp'][1-side]),None)
        if not hit:continue
        if any(not same(v) or v['pp'][side][move_slot]!=charged['pp'][side][move_slot] for v in observations if charged['frame']<=v['frame']<=hit['frame']):continue
        proofs.append(dict(side=side,pp_before=use[0],before=before,charged=charged,released=released,hit=hit))
    return proofs
