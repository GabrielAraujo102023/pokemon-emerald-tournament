"""Actual spawn workers and actual backend input rejection; no mock battle results."""
import copy
from pathlib import Path
from emerald_tournament.parallel_plan import prepare
from emerald_tournament.parallel_runner import run
from emerald_tournament.result_store import identity
ROOT=Path(__file__).resolve().parents[1]

def test_failed_tasks_retry_boundedly_and_are_never_completed(tmp_path):
 plan,context=prepare(ROOT/'config/parallel_validation.json')
 # Deliberately invalid backend input in a test-only plan. CLI admission rejects this.
 # The real run_battle function must reject trainer zero, not return an invented loss.
 bad=copy.deepcopy(plan);bad.update(trainer_ids=[0,136],pairing='all_pairs',frame_budgets=[6000],total_battles=2)
 bad['plan_id']=identity(bad);context=dict(context,plan=bad)
 first=run(bad,context,tmp_path/'failures',workers=1,inflight=1,retries=1)
 assert first['completed']==0 and first['failed']==2 and first['failed_attempts']==4
 idle=run(bad,context,tmp_path/'failures',workers=1)
 assert idle['failed_attempts_this_session']==0
 retried=run(bad,context,tmp_path/'failures',workers=1,retry_failed=True)
 assert retried['failed_attempts_this_session']==2 and retried['failed_attempts']==6 and retried['completed']==0
