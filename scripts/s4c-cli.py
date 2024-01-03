#!/usr/bin/python3
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
    """! Run s4c scripts as subcommands."""
    print("Wrong arguments.");
    print("\nUsage:\tpython {} <subcommand>".format(os.path.basename(__file__)))
    print_subcommands()

def main(argv):
    """! Main program entry."""
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
            sub_args.append(argv[2:])
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
