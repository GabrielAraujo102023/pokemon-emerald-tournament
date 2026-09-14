"""One durable writer, append-only results, and bounded-memory resume queries."""
import hashlib,json,sqlite3
from .result_store import canonical

class Store:
    def __init__(self,path,plan):
        self.db=sqlite3.connect(path,timeout=30)
        try:
            tables={r[0] for r in self.db.execute("SELECT name FROM sqlite_master WHERE type='table'")}
            if tables:
                if 'metadata' not in tables or 'plan' not in {r[1] for r in self.db.execute('PRAGMA table_info(metadata)')}:raise ValueError('Not a concurrent-run database; use the legacy CLI for legacy results')
                existing=self.db.execute('SELECT plan FROM metadata WHERE id=1').fetchone()
                if existing and existing[0]!=canonical(plan):raise ValueError('Incompatible tournament configuration/provenance; use a new output directory')
            self.db.execute('PRAGMA journal_mode=WAL')
            self.db.execute('PRAGMA synchronous=FULL')
            self.db.execute('PRAGMA fullfsync=ON')
            self.db.execute('PRAGMA checkpoint_fullfsync=ON')
            self.db.execute('PRAGMA busy_timeout=30000')
            self.db.execute('PRAGMA foreign_keys=ON')
            self.db.executescript('''
            CREATE TABLE IF NOT EXISTS metadata(id INTEGER PRIMARY KEY CHECK(id=1),plan TEXT NOT NULL);
            CREATE TABLE IF NOT EXISTS results(
              match_id TEXT PRIMARY KEY, ordinal INTEGER NOT NULL UNIQUE,
              trainer_a INTEGER NOT NULL,trainer_b INTEGER NOT NULL,repetition INTEGER NOT NULL,
              orientation INTEGER NOT NULL CHECK(orientation IN(0,1)),seed INTEGER NOT NULL,
              outcome TEXT NOT NULL CHECK(outcome IN('a_win','b_win','draw','timeout')),
              turns INTEGER NOT NULL,frames INTEGER NOT NULL,runtime_seconds REAL NOT NULL,
              completed_at TEXT NOT NULL,worker_pid INTEGER NOT NULL,
              record TEXT NOT NULL,record_sha256 TEXT NOT NULL,artifact BLOB NOT NULL,artifact_sha256 TEXT NOT NULL,
              UNIQUE(trainer_a,trainer_b,repetition));
            CREATE TABLE IF NOT EXISTS failures(
              attempt_id TEXT PRIMARY KEY,match_id TEXT NOT NULL,ordinal INTEGER NOT NULL,
              task TEXT NOT NULL,error_type TEXT NOT NULL,error_message TEXT NOT NULL,traceback TEXT NOT NULL,
              runtime_seconds REAL NOT NULL,completed_at TEXT NOT NULL,worker_pid INTEGER NOT NULL,
              artifact BLOB NOT NULL,artifact_sha256 TEXT NOT NULL);
            CREATE INDEX IF NOT EXISTS failure_match ON failures(match_id);
            ''')
            for table in ('metadata','results','failures'):
                for operation in ('UPDATE','DELETE'):
                    self.db.execute(f"CREATE TRIGGER IF NOT EXISTS {table}_no_{operation.lower()} BEFORE {operation} ON {table} BEGIN SELECT RAISE(ABORT,'immutable {table}'); END")
            row=self.db.execute('SELECT plan FROM metadata WHERE id=1').fetchone()
            if row and row[0]!=canonical(plan):raise ValueError('Incompatible tournament configuration/provenance; use a new output directory')
            if not row:
                with self.db:self.db.execute('INSERT INTO metadata VALUES(1,?)',(canonical(plan),))
            self.plan=plan
        except BaseException:
            self.db.close();raise

    def state(self,match_id):
        if self.db.execute('SELECT 1 FROM results WHERE match_id=?',(match_id,)).fetchone():return 'completed'
        if self.db.execute('SELECT 1 FROM failures WHERE match_id=? LIMIT 1',(match_id,)).fetchone():return 'failed'
        return 'incomplete'

    def counts(self):
        done=self.db.execute('SELECT count(*) FROM results').fetchone()[0]
        failed=self.db.execute('SELECT count(DISTINCT match_id) FROM failures f WHERE NOT EXISTS(SELECT 1 FROM results r WHERE r.match_id=f.match_id)').fetchone()[0]
        attempts=self.db.execute('SELECT count(*) FROM failures').fetchone()[0]
        return dict(completed=done,remaining=self.plan['total_battles']-done,failed=failed,
                    incomplete=self.plan['total_battles']-done-failed,failed_attempts=attempts)

    def commit(self,task,message):
        archive=message['artifact'];archive_hash=hashlib.sha256(archive).hexdigest()
        if not message['ok']:
            with self.db:self.db.execute('INSERT INTO failures VALUES(?,?,?,?,?,?,?,?,?,?,?,?)',(
                message['attempt_id'],task['match_id'],task['ordinal'],canonical(task),message['error_type'],
                message['error_message'],message['traceback'],message['runtime_seconds'],message['completed_at'],
                message['worker_pid'],archive,archive_hash))
            return
        r=message['record']
        for k in ('trainer_a','trainer_b','seed','max_frames'):
            if r[k]!=task[k]:raise ValueError('Worker result identity mismatch: '+k)
        if r.get('validation_overrides') or r['provenance']!=self.plan['provenance']:raise ValueError('Worker provenance/intervention mismatch')
        if r['outcome']=='timeout':
            if r['terminal_from_engine'] or r['rng_final'] is not None or r['frames']!=r['max_frames']:raise ValueError('Invalid timeout')
        elif r['outcome'] not in ('a_win','b_win','draw') or not r['terminal_from_engine'] or r['rng_final'] is None:
            raise ValueError('Missing valid engine terminal result')
        if not r['initial_party_sha256'] or not r['trace_event_count']:raise ValueError('Incomplete capture')
        compact={k:v for k,v in r.items() if k!='provenance'}
        encoded=canonical(compact)
        with self.db:self.db.execute('INSERT INTO results VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)',(
            task['match_id'],task['ordinal'],task['trainer_a'],task['trainer_b'],task['repetition'],task['orientation'],task['seed'],
            r['outcome'],r['turns'],r['frames'],message['runtime_seconds'],message['completed_at'],message['worker_pid'],
            encoded,hashlib.sha256(encoded.encode()).hexdigest(),archive,archive_hash))

    def close(self):
        # WAL + FULL already makes each commit durable; checkpoint is housekeeping.
        try:
            if self.db.in_transaction:self.db.rollback()
            try:self.db.execute('PRAGMA wal_checkpoint(PASSIVE)')
            except sqlite3.OperationalError:pass  # Committed WAL remains durable if checkpoint is busy.
        finally:self.db.close()

def status(path):
    db=sqlite3.connect(f'{path.resolve().as_uri()}?mode=ro',uri=True)
    try:
        plan=json.loads(db.execute('SELECT plan FROM metadata WHERE id=1').fetchone()[0])
        proxy=object.__new__(Store);proxy.db=db;proxy.plan=plan
        return dict(plan_id=plan['plan_id'],total=plan['total_battles'],**proxy.counts())
    finally:db.close()
