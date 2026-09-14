"""Portable process locking and conservative hardware defaults; no fork assumptions."""
import contextlib,os,platform,subprocess
from pathlib import Path

def available_memory():
    try:
        if os.name == 'nt':
            import ctypes
            class Memory(ctypes.Structure):
                _fields_ = [('length',ctypes.c_ulong),('load',ctypes.c_ulong)] + [(n,ctypes.c_ulonglong) for n in ('total','available','page_total','page_available','virtual_total','virtual_available','extended')]
            value=Memory();value.length=ctypes.sizeof(value)
            if ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(value)):return value.available
        elif platform.system() == 'Darwin':
            # Reserve most system RAM; this is a budget, not a free-memory claim.
            return int(subprocess.check_output(['sysctl','-n','hw.memsize'],text=True,stderr=subprocess.DEVNULL))//4
        else:
            return os.sysconf('SC_AVPHYS_PAGES')*os.sysconf('SC_PAGE_SIZE')
    except (OSError,ValueError,AttributeError,subprocess.SubprocessError):
        pass
    return None

def hardware():
    logical=os.cpu_count() or 1
    memory=available_memory()
    auto=min(8,max(1,logical//2))
    if memory is not None:auto=min(auto,max(1,memory//(512*1024**2)))
    return dict(logical_cpus=logical,memory_budget_bytes=memory,auto_workers=auto,
                memory_note='macOS: 25% of total RAM; Linux/Windows: available RAM; estimate only')

def worker_count(value):
    if str(value)=='auto':return hardware()['auto_workers']
    try:count=int(value)
    except (ValueError,TypeError):raise ValueError('workers must be auto or a positive integer')
    if count<1:raise ValueError('workers must be positive')
    return count

@contextlib.contextmanager
def run_lock(path):
    """OS releases the lock after crashes; the lock file is intentionally retained."""
    with Path(path).open('a+b') as handle:
        handle.seek(0,2)
        if handle.tell()==0:handle.write(b'0');handle.flush()
        handle.seek(0)
        try:
            if os.name=='nt':
                import msvcrt
                msvcrt.locking(handle.fileno(),msvcrt.LK_NBLCK,1)
            else:
                import fcntl
                fcntl.flock(handle,fcntl.LOCK_EX|fcntl.LOCK_NB)
        except OSError as e:raise RuntimeError('Another runner owns this output directory') from e
        try:yield
        finally:
            handle.seek(0)
            if os.name=='nt':msvcrt.locking(handle.fileno(),msvcrt.LK_UNLCK,1)
            else:fcntl.flock(handle,fcntl.LOCK_UN)
