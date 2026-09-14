"""Report real prerequisites without treating absent tools as a working backend."""
import json
import shutil
import subprocess
from pathlib import Path

root = Path(__file__).resolve().parents[1]
paths = {name: shutil.which(name) for name in ("arm-none-eabi-gcc", "arm-none-eabi-as", "cmake", "mgba", "pkg-config")}
bridge = root / "build/emulator/emerald-mgba-bridge"
report = {"tools": paths, "bridge": str(bridge) if bridge.is_file() else None, "rom_built": False, "checkpoint_exists": False, "battle_validated": False}
if bridge.is_file():
    probe = subprocess.run([str(bridge), "--version"], capture_output=True, text=True)
    report["bridge_version"] = probe.stdout.strip()
    report["bridge_probe_returncode"] = probe.returncode
print(json.dumps(report, indent=2))
