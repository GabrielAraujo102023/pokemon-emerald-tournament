"""Read-only upstream host-compilation feasibility probe; this does not build a backend."""
from pathlib import Path
import json
import subprocess
import tempfile

PROJECT = Path(__file__).resolve().parents[1]
ROOT = PROJECT / "pokeemerald"


def run(args):
    return subprocess.run(list(map(str, args)), text=True, capture_output=True)


def main():
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        result = run(["c++", "-std=c++11", "-O2", ROOT / "tools/mapjson/json11.cpp", ROOT / "tools/mapjson/mapjson.cpp", "-o", work / "mapjson"])
        if result.returncode:
            raise RuntimeError(result.stderr)
        for mode, src in [("groups", "data/maps/map_groups.json"), ("layouts", "data/layouts/layouts.json")]:
            result = run([work / "mapjson", mode, "emerald", ROOT / src, work, work])
            if result.returncode:
                raise RuntimeError(result.stderr)
        reports = []
        for unit in ["battle_main.c", "battle_script_commands.c", "battle_ai_script_commands.c", "battle_ai_switch_items.c"]:
            result = run(["cc", "-fsyntax-only", "-ferror-limit=8", "-I", ROOT / "include", "-I", work, ROOT / "src" / unit])
            reports.append(dict(unit=unit, returncode=result.returncode, diagnostics=result.stderr.replace(str(ROOT), "pokeemerald").replace(str(work), "<temporary-generated-headers>")))
        output = dict(probe="host-syntax-v1", compiler=run(["cc", "--version"]).stdout, upstream_commit=run(["git", "-C", ROOT, "rev-parse", "HEAD"]).stdout.strip(), results=reports)
        (PROJECT / "docs/host_probe.json").write_text(json.dumps(output, indent=2) + "\n")
        for report in reports:
            print(report["unit"], report["returncode"])
            print(report["diagnostics"][:1200])


if __name__ == "__main__":
    main()
