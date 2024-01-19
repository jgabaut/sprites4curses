#!/usr/bin/python3
"""! @brief Program that handle s4c scripts as subcommands. WIP."""

##
# @file s4c_cli.py
#
# @brief Program that handle s4c scripts as subcommands. WIP.
#
# @section description_s4c_cli Description
# The png parsing scripts use Pillow, and the mapping is done against a preset color list.
# The list is described in palette.gpl to aid in exporting images with the correct color indexing.
#
# @section libraries_main Libraries/Modules
# - Pillow (https://pillow.readthedocs.io/en/stable/)
#   - Access to image manipulation functions.
# - sys standard library (https://docs.python.org/3/library/sys.html)
#   - Access to command line arguments.
# - glob standard library (https://docs.python.org/3/library/glob.html)
#   - Access to pattern expansion.
# - re standard library (https://docs.python.org/3/library/re.html)
#   - Access to regular expressions.
# - os standard library (https://docs.python.org/3/library/os.html)
#   - Access to program name.
# - math standard library (https://docs.python.org/3/library/math.html)
#   - Access to sqrt.
#
# @section notes_s4c_cli Notes
# - Color map should have the same order as the palette used to index the sprites.
#
# @section todo_s4c_cli TODO
# - Check if the encoded value is exceeding latin literals.
#
# @section author_s4c_cli Author(s)
# - Created by jgabaut on 02/01/2024.
# - Modified by jgabaut on 03/01/2024.

import sys
import os
from cut_sheet import main as cut_sheet_main
from palette import main as palette_main
from sprites import main as sprites_main
from sheet_converter import main as sheet_converter_main
from png_resize import main as png_resize_main

s4c_cli_version = "0.1.0"

subcommands = ["cut_sheet", "palette", "sprites", "sheet_converter", "png_resize", "help", "version"]

def print_subcommands():
    print("Subcommands:\n")
    print("\t{}".format('\n\t'.join(subcommands)))

def usage():
    """! Prints correct invocation."""
    print("Wrong arguments.");
    print("\nUsage:\tpython {} <subcommand>".format(os.path.basename(__file__)))
    print_subcommands()

def main(argv):
    """! Main program entry. Run s4c scripts as subcommands."""
    if len(argv) < 2:
        usage()
    else:
        subcommand = argv[1]
        sub_args = []
        if subcommand.lower() == "version":
            print("s4c-cli {}".format(s4c_cli_version))
        elif subcommand.lower() == "help" or subcommand.lower() == "-h" or subcommand.lower() == "help":
            print("Running subcommand: \"{}\"".format(subcommand))
            print_subcommands()
            exit(0)
        elif subcommand.lower() == "cut_sheet" or subcommand.lower() == "palette" or subcommand.lower() == "sprites" or subcommand.lower() == "sheet_converter" or subcommand.lower() == "png_resize":
            print("Running subcommand: \"{}\"".format(subcommand))
            sub_args.append(subcommand)
            for arg in argv[2:]:
                sub_args.append(arg)
            query = subcommand.lower()
            if query == "cut_sheet":
                cut_sheet_main(sub_args)
            elif query == "palette":
                palette_main(sub_args)
            elif query == "sprites":
                sprites_main(sub_args)
            elif query == "sheet_converter":
                sheet_converter_main(sub_args)
            elif query == "png_resize":
                png_resize_main(sub_args)
            else:
                assert(false and print("Unreachable!"))
                usage()
                exit(1)
        else:
            print("Unknown subcommand: {}".format(subcommand))
            usage()
            exit(1)

if __name__ == "__main__":
    main(sys.argv)
