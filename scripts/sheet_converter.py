#!/bin/python3

import sys
from depr import print_depr_warn
from s4c.core.sheet_converter import main

if __name__ == "__main__":
    print_depr_warn()
    main(sys.argv)
