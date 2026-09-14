"""Build the project-local pinned mGBA library and bridge from an existing checkout."""
from pathlib import Path
import json,subprocess
ROOT=Path(__file__).resolve().parents[1]

def main():
    cmake=ROOT/'.venv/bin/cmake';source=ROOT/'build/mgba-source';prefix=ROOT/'build/mgba-prefix'
    revision=subprocess.check_output(['git','-C',str(source),'rev-parse','HEAD'],text=True).strip()
    if revision!='26b7884bc25a5933960f3cdcd98bac1ae14d42e2':raise RuntimeError('Expected pinned mGBA 0.10.5 source')
    commands=[
        [str(cmake),'-S',str(source),'-B','build/mgba-library','-DCMAKE_BUILD_TYPE=Release','-DCMAKE_POLICY_VERSION_MINIMUM=3.5','-DBUILD_QT=OFF','-DBUILD_SDL=OFF','-DBUILD_SHARED=ON','-DBUILD_STATIC=OFF','-DUSE_FFMPEG=OFF','-DUSE_LIBZIP=OFF','-DUSE_SQLITE3=OFF','-DUSE_DISCORD_RPC=OFF','-DUSE_MINIZIP=OFF','-DBUILD_TEST=OFF'],
        [str(cmake),'--build','build/mgba-library','-j4'],
        [str(cmake),'--install','build/mgba-library','--prefix',str(prefix)],
        [str(cmake),'-S','tools/emulator','-B','build/emulator','-DCMAKE_PREFIX_PATH='+str(prefix)],
        [str(cmake),'--build','build/emulator','-j4']]
    with (ROOT/'build/reports/emulator-build.log').open('w') as log:
        for command in commands:subprocess.run(command,cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,check=True)
    (ROOT/'build/reports/emulator-build.json').write_text(json.dumps({'commit':revision,'commands':commands},indent=2)+'\n')

if __name__=='__main__':main()
