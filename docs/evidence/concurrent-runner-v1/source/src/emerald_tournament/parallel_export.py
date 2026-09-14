"""Export a digest-verified capture from the compact SQLite archive."""
import hashlib,io,json,sqlite3,zipfile
from pathlib import Path

def export_capture(output,prefix,destination):
    db=sqlite3.connect(f'{(output/"results.sqlite").as_uri()}?mode=ro',uri=True)
    try:
        # Prefix interpreted literally, not as an SQL LIKE pattern.
        rows=db.execute('SELECT match_id,artifact,artifact_sha256,record,record_sha256 FROM results WHERE substr(match_id,1,?)=? LIMIT 2',(len(prefix),prefix)).fetchall()
        if len(rows)!=1:raise ValueError('Match prefix must resolve uniquely')
        mid,data,hash_,record,rhash=rows[0]
        if hashlib.sha256(data).hexdigest()!=hash_ or hashlib.sha256(record.encode()).hexdigest()!=rhash:raise ValueError('Stored capture integrity failure')
        plan=json.loads(db.execute('SELECT plan FROM metadata').fetchone()[0])
    finally:db.close()
    destination.mkdir(parents=True,exist_ok=False)
    with zipfile.ZipFile(io.BytesIO(data)) as archive:
        for member in archive.infolist():
            if Path(member.filename).name!=member.filename or '\\' in member.filename:raise ValueError('Unexpected archive path')
            (destination/member.filename).write_bytes(archive.read(member))
    result=json.loads(record);result['provenance']=plan['provenance']
    if json.loads((destination/'battle_result.json').read_text())!=result:raise ValueError('Archive/compact result mismatch')
    (destination/'lookup.json').write_text(json.dumps({'match_id':mid,'plan_id':plan['plan_id']},indent=2)+'\n')
    return destination
