"""Repository-local entry point; equivalent to python -m emerald_tournament.emu_battle."""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "src"))
from emerald_tournament.emu_battle import main
if __name__ == "__main__":
    main()
