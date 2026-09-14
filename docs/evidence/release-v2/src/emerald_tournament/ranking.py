"""Derived statistics only; never substitutes or modifies engine outcomes."""
def standings(results,trainer_ids,config):
    ranks={i:dict(trainer_id=i,wins=0,losses=0,draws=0,timeouts=0,games_played=0,elo=float(config['initial_elo'])) for i in trainer_ids}
    for entry in sorted(results,key=lambda r:r['ordinal']):
        r=entry['record'];a,b=ranks[r['trainer_a']],ranks[r['trainer_b']]
        if r['outcome']=='timeout':a['timeouts']+=1;b['timeouts']+=1;continue
        a['games_played']+=1;b['games_played']+=1
        if r['outcome']=='a_win':a['wins']+=1;b['losses']+=1;score=1
        elif r['outcome']=='b_win':b['wins']+=1;a['losses']+=1;score=0
        elif r['outcome']=='draw':a['draws']+=1;b['draws']+=1;score=config['draw_score']
        else:raise ValueError('Unknown immutable outcome')
        expected=1/(1+10**((b['elo']-a['elo'])/400))
        change=config['k']*(score-expected);a['elo']+=change;b['elo']-=change
    for r in ranks.values():
        r['attempts']=r['games_played']+r['timeouts']
        r['win_rate']=r['wins']/r['games_played'] if r['games_played'] else None
    return sorted(ranks.values(),key=lambda r:(-r['elo'],r['trainer_id']))
