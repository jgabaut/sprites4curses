#!/bin/python3

import sys
from s4c.core.cut_sheet import main

if __name__ == "__main__":
    print("[WARN]    This bridge script to s4c module is deprecated since 0.4.3, and will be removed in the 0.5 release of the library.")
    print("[WARN]    To prepare for it, you should either:")
    print("[WARN]    - Use the s4c module:    \'python -m s4c-scripts.s4c\'")
    print("[WARN]    - Use a single script directly:    \'python -m s4c-scripts.s4c.core.SCRIPT_NAME\'\n")
    main(sys.argv)
