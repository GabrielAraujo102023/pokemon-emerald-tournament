"""Append-only SQLite outcomes and failures, with deterministic match identities."""
import hashlib,json,sqlite3
from pathlib import Path

def canonical(value):return json.dumps(value,sort_keys=True,separators=(',',':'))
def identity(value):return hashlib.sha256(canonical(value).encode()).hexdigest()

def connect(path,preflight):
    db=sqlite3.connect(path)
    db.execute('PRAGMA foreign_keys=ON')
    db.executescript('''
    CREATE TABLE IF NOT EXISTS metadata (id INTEGER PRIMARY KEY CHECK(id=1), preflight TEXT NOT NULL);
    CREATE TABLE IF NOT EXISTS results (
      match_id TEXT PRIMARY KEY, ordinal INTEGER NOT NULL UNIQUE,
      trainer_a INTEGER NOT NULL, trainer_b INTEGER NOT NULL, repetition INTEGER NOT NULL,
      orientation INTEGER NOT NULL CHECK(orientation IN (0,1)), seed INTEGER NOT NULL,
      outcome TEXT NOT NULL CHECK(outcome IN ('a_win','b_win','draw','timeout')),
      record TEXT NOT NULL, record_sha256 TEXT NOT NULL, artifact TEXT NOT NULL UNIQUE,
      UNIQUE(trainer_a,trainer_b,repetition));
    CREATE TABLE IF NOT EXISTS failures (attempt TEXT PRIMARY KEY, match_id TEXT NOT NULL, error TEXT NOT NULL, artifact TEXT NOT NULL);
    CREATE TRIGGER IF NOT EXISTS results_no_update BEFORE UPDATE ON results BEGIN SELECT RAISE(ABORT,'immutable results'); END;
    CREATE TRIGGER IF NOT EXISTS results_no_delete BEFORE DELETE ON results BEGIN SELECT RAISE(ABORT,'immutable results'); END;
    CREATE TRIGGER IF NOT EXISTS metadata_no_update BEFORE UPDATE ON metadata BEGIN SELECT RAISE(ABORT,'immutable metadata'); END;
    CREATE TRIGGER IF NOT EXISTS metadata_no_delete BEFORE DELETE ON metadata BEGIN SELECT RAISE(ABORT,'immutable metadata'); END;
    CREATE TRIGGER IF NOT EXISTS failures_no_update BEFORE UPDATE ON failures BEGIN SELECT RAISE(ABORT,'immutable failures'); END;
    CREATE TRIGGER IF NOT EXISTS failures_no_delete BEFORE DELETE ON failures BEGIN SELECT RAISE(ABORT,'immutable failures'); END;
    ''')
    pinned=canonical(preflight);row=db.execute('SELECT preflight FROM metadata WHERE id=1').fetchone()
    if row and row[0]!=pinned:
        db.close();raise ValueError('Resume provenance/configuration mismatch')
    if not row:
        with db:db.execute('INSERT INTO metadata VALUES (1,?)',(pinned,))
    return db

def append_result(db,match,record,artifact):
    if record.get('validation_overrides'):raise ValueError('Validation intervention rejected')
    for k in ('trainer_a','trainer_b','seed'):
        if record[k]!=match[k]:raise ValueError('Match/result identity mismatch: '+k)
    outcome=record['outcome']
    if outcome not in ('a_win','b_win','draw','timeout'):raise ValueError('Unsupported outcome')
    if outcome=='timeout':
        if record['terminal_from_engine'] or record['rng_final'] is not None or record['frames']!=record['max_frames']:raise ValueError('Invalid timeout result')
    elif not record['terminal_from_engine'] or record['rng_final'] is None:raise ValueError('Missing engine terminal evidence')
    if not record['initial_party_sha256'] or not record['trace_event_count']:raise ValueError('Incomplete battle capture')
    encoded=canonical(record)
    with db:db.execute('INSERT INTO results VALUES (?,?,?,?,?,?,?,?,?,?,?)',(match['match_id'],match['ordinal'],match['trainer_a'],match['trainer_b'],match['repetition'],match['orientation'],match['seed'],outcome,encoded,hashlib.sha256(encoded.encode()).hexdigest(),str(artifact)))

def rows(db):
    found=[]
    for mid,ordinal,text,hash_,artifact in db.execute('SELECT match_id,ordinal,record,record_sha256,artifact FROM results ORDER BY ordinal'):
        if hashlib.sha256(text.encode()).hexdigest()!=hash_:raise ValueError('Corrupt immutable result')
        found.append({'match_id':mid,'ordinal':ordinal,'record':json.loads(text),'artifact':artifact})
    return found
