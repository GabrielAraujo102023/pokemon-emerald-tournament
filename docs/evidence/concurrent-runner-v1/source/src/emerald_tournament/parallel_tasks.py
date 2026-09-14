"""Lazy deterministic match planning. Worker count and completion order are irrelevant."""
import itertools
from .result_store import identity

SEED_VERSION = 'sha256-canonical-pair-repetition-orientation-v1'

def pairs(ids, pairing):
    ids = sorted(ids)
    if pairing == 'all_pairs':
        yield from itertools.combinations(ids, 2)
    elif pairing == 'ring':
        yield from sorted({tuple(sorted((a, ids[(i + 1) % len(ids)]))) for i, a in enumerate(ids)})
    else:
        raise ValueError('Unknown pairing rule')

def count_tasks(ids, pairing, repetitions):
    n = len(ids)
    pair_count = n * (n - 1) // 2 if pairing == 'all_pairs' else (1 if n == 2 else n)
    return pair_count * repetitions * 2

def tasks(plan):
    ordinal = 0
    for a, b in pairs(plan['trainer_ids'], plan['pairing']):
        for repetition, budget in enumerate(plan['frame_budgets']):
            for orientation in (0, 1):
                seed = int(identity([SEED_VERSION, plan['master_seed'], a, b, repetition, orientation])[:8], 16)
                task = dict(ordinal=ordinal, trainer_a=b if orientation else a,
                            trainer_b=a if orientation else b, repetition=repetition,
                            orientation=orientation, seed=seed, max_frames=budget)
                task['match_id'] = identity([plan['plan_id'], task])
                yield task
                ordinal += 1
