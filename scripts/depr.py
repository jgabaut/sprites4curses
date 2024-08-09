#!/bin/python3

import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def print_depr_warn():
    eprint("[WARN]    This bridge script to s4c module is deprecated since 0.4.3, and will be removed in the 0.5 release of the library.")
    eprint("[WARN]    To prepare for it, you should either:")
    eprint("[WARN]    - Use the s4c module:    \'python -m s4c-scripts.s4c\'")
    eprint("[WARN]    - Use a single script directly:    \'python -m s4c-scripts.s4c.core.SCRIPT_NAME\'\n")
