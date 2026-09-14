"""Build a separate modern ARM copy and retain provenance/logs; never patch upstream."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "pokeemerald"
DEST = ROOT / "build/pokeemerald"
REPORTS = ROOT / "build/reports"


def main():
    REPORTS.mkdir(parents=True, exist_ok=True)
    if not DEST.exists():
        shutil.copytree(SOURCE, DEST, ignore=shutil.ignore_patterns(".git", "build", "__pycache__"))
    env = os.environ.copy()
    env["DEVKITPRO"] = "/opt/devkitpro"
    env["DEVKITARM"] = "/opt/devkitpro/devkitARM"
    # Host tools must discover host libpng; devkitPro's pkg-config targets its SDK.
    env["PATH"] = "/opt/devkitpro/devkitARM/bin:/opt/homebrew/bin:/opt/devkitpro/tools/bin:" + env["PATH"]
    args = ["make", "modern", "DINFO=1", "-j4"]
    metadata = dict(command=args, cwd=str(DEST), compiler=subprocess.check_output(["arm-none-eabi-gcc", "--version"], env=env, text=True),
                    source_commit=subprocess.check_output(["git", "-C", str(SOURCE), "rev-parse", "HEAD"], text=True).strip(),
                    path=env["PATH"], variant="modern DINFO=1; not retail-matching")
    with (REPORTS / "build-modern.log").open("w") as log:
        result = subprocess.run(args, cwd=DEST, env=env, stdout=log, stderr=subprocess.STDOUT)
    metadata["returncode"] = result.returncode
    metadata["source_changes"] = {str(p.relative_to(DEST)): hashlib.sha256(p.read_bytes()).hexdigest() for p in (DEST/"src").glob("*.c") if not (SOURCE/p.relative_to(DEST)).exists() or p.read_bytes() != (SOURCE/p.relative_to(DEST)).read_bytes()}
    metadata["config_sha256"] = hashlib.sha256((DEST/"include/config.h").read_bytes()).hexdigest()
    if result.returncode == 0:
        metadata["artifacts"] = {name: dict(path=str(DEST/name), sha256=hashlib.sha256((DEST/name).read_bytes()).hexdigest()) for name in ("pokeemerald_modern.gba", "pokeemerald_modern.elf")}
    (REPORTS / "build-modern.json").write_text(json.dumps(metadata, indent=2) + "\n")
    print("Build return code:", result.returncode)
    print((REPORTS / "build-modern.log").read_text()[-3000:])
    raise SystemExit(result.returncode)


if __name__ == "__main__":
    main()
