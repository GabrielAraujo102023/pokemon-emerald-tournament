"""Read-only readiness report using the configured devkitARM and emulator paths."""
from __future__ import annotations
import os
import shutil
import subprocess
from pathlib import Path


def diagnose(project: Path) -> dict:
    env = os.environ.copy()
    devkitpro = Path(env.get("DEVKITPRO", "/opt/devkitpro"))
    devkitarm = Path(env.get("DEVKITARM", str(devkitpro / "devkitARM")))
    mgba = Path(env.get("MGBA_BIN", "/Applications/mGBA.app/Contents/MacOS/mGBA"))
    env["PATH"] = os.pathsep.join([str(project / ".venv/bin"), str(devkitarm / "bin"), str(devkitpro / "tools/bin"), env.get("PATH", "")])
    checks = []
    for name in ("arm-none-eabi-gcc", "arm-none-eabi-as", "arm-none-eabi-ld", "arm-none-eabi-objcopy", "make", "python", "pytest", str(mgba)):
        path = shutil.which(name, path=env["PATH"])
        check = {"command": [name, "--version"], "path": path, "ok": False}
        if path:
            try:
                result = subprocess.run([path, "--version"], env=env, capture_output=True, text=True, timeout=20)
                check.update(ok=result.returncode == 0, returncode=result.returncode, output=(result.stdout + result.stderr).strip())
            except (OSError, subprocess.TimeoutExpired) as error:
                check["error"] = str(error)
        checks.append(check)
    ready = devkitarm.is_dir() and all(c["ok"] for c in checks)
    return dict(devkitpro=str(devkitpro), devkitarm=str(devkitarm), mgba_bin=str(mgba), checks=checks,
                build_prerequisites_ready=ready,
                bridge_exists=(project / "build/emulator/emerald-mgba-bridge").is_file(),
                battle_validation_passed=None,
                note="This command checks prerequisites only; see docs/evidence/battle-entry-validation.json for the pinned minimal battle validation.")
