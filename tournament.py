"""Portable concurrent CLI. Run from this repository or install the Python package."""
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parent/'src'))
from emerald_tournament.parallel_cli import main
if __name__=='__main__':
    import multiprocessing
    multiprocessing.freeze_support()
    raise SystemExit(main())
