import sys
from pathlib import Path

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def print_depr_warn(script_name_full):
    script_name = Path(script_name_full).stem
    eprint(f"[WARN]    This bridge script to s4c module {{{script_name}}} is deprecated since 0.4.3, and will be removed in the 0.5 release of the library.")
    eprint("[WARN]    To prepare for it, you should either:")
    eprint("[WARN]    - Use the s4c module:    `python -m s4c-scripts.s4c`")
    eprint(f"[WARN]    - Use a single script directly:    `python -m s4c-scripts.s4c.core.{script_name}`\n")
