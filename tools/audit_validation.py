"""Generate lexical address inventory and local toolchain evidence. No engine patches."""
from pathlib import Path
import json
import re
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
UPSTREAM = ROOT / "pokeemerald"


def run(args):
    p = subprocess.run(list(map(str, args)), text=True, capture_output=True)
    return dict(command=list(map(str, args)), returncode=p.returncode, stdout=p.stdout, stderr=p.stderr)


def main():
    operands = []
    for path in [UPSTREAM / "asm/macros/battle_script.inc", UPSTREAM / "asm/macros/battle_ai_script.inc"]:
        macro = None
        for lineno, line in enumerate(path.read_text().splitlines(), 1):
            if line.strip().startswith(".macro "):
                macro = line.strip()[7:]
            if ".4byte" in line:
                operands.append(dict(source=str(path.relative_to(UPSTREAM)), line=lineno, macro=macro, operand=line.split(".4byte", 1)[1].strip(), semantic_status="requires interpreter review; width alone does not establish pointer semantics"))
    reads = []
    for path in sorted((UPSTREAM / "src").glob("battle*.c")):
        for lineno, line in enumerate(path.read_text().splitlines(), 1):
            if re.search(r"T[12]_READ_(PTR|32)|\(u32\).*([Pp]tr|[Ss]cript)", line):
                reads.append(dict(source=str(path.relative_to(UPSTREAM)), line=lineno, code=line.strip()))
    inventory = dict(scope="All .4byte operands in the two battle macro files, plus candidate address/numeric reads in src/battle*.c; lexical coverage, not a complete semantic proof", operands=operands, interpreter_candidates=reads)
    (ROOT / "docs/script_address_inventory.json").write_text(json.dumps(inventory, indent=2) + "\n")
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        (work / "width.c").write_text('#include <stdint.h>\n#include <stdio.h>\nstatic unsigned char script[8];\nint main(void) { uintptr_t p=(uintptr_t)script; printf("%zu %llu\\n",sizeof(void*),(unsigned long long)p); return p>UINT32_MAX; }\n')
        reports = []
        for flag in [[], ["-m32"], ["-arch", "i386"]]:
            result = run(["cc", *flag, work / "width.c", "-o", work / "probe"])
            if result["returncode"] == 0:
                result["execution"] = run([work / "probe"])
            reports.append(result)
        output = dict(compiler=run(["cc", "--version"]), tools={tool: shutil.which(tool) for tool in ["arm-none-eabi-gcc", "mgba", "qemu-system-arm"]}, probes=reports)
        # Avoid retaining ephemeral paths; execution addresses intentionally vary with ASLR.
        text = json.dumps(output, indent=2).replace(str(work), "<temporary>")
        (ROOT / "docs/address_toolchain_probe.json").write_text(text + "\n")
    print(f"Inventoried {len(operands)} four-byte operands and {len(reads)} interpreter candidates")
    for report in reports:
        print(report["command"][1:-3], report["returncode"], report["stderr"][:250], report.get("execution", {}).get("stdout", ""))


if __name__ == "__main__":
    main()
