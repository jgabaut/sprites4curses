#!/usr/bin/python3
"""! @brief Program that parses a palette file into a C header."""

##
# @file palette.py
#
# @brief Program that parses a palette file into a C header.
#
# @section description_sprites Description
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
# @section notes_palette Notes
#
# @section todo_palette TODO
#
# @section author_palette Author(s)
# - Created by jgabaut on 01/09/2023.
# - Modified by jgabaut on 03/01/2024.

# Imports
import sys
import glob
import re
import os
import math

## The file format version.
FILE_VERSION = "0.2.2"

# Expects the palette name as first argument, output directory as second argument.

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments. Needed: mode, palette file, s4c path")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <mode> <palette> <s4c path>")
    print("\n  mode:  \n\tC-header\n\tC-impl")
    exit(1)


def convert_palette(mode, palette_path, s4c_path):
    """! Takes a mode and a palette file, plus the path to s4c directory (for includes) and outputs C code for it to stdout.
    According to the passed mode, the C header or the C file may be generated.
    @param palette_path   The path to palette file.
    """
    if mode != "header" and mode != "cfile" :
        print("Unexpected mode value in convert_palette: {}".format(mode))
        usage()
    # We start the count from one so we account for one more cell for array declaration
    target_name = os.path.splitext(os.path.basename(os.path.normpath(palette_path)))[0].replace("-","_")


    palette_fp = open(palette_path, "r")
    read_lines = 0
    read_colors = 0

    colors = []
    while True:

        # Get next line from file
        line = palette_fp.readline()
        read_lines += 1

        if read_lines == 1:
            continue #Ignore first line

        # if line is empty
        # end of file is reached
        if not line:
            #print("Read [{}] colors.".format(read_colors))
            break
        s_line = line.strip()
        #print("Line [{}]: stripped \"{}\"".format(read_lines,s_line))
        tks = s_line.split()
        h_tks = []
        if read_lines < 5:
            #print("Still parsing header")
            h_tks += tks
            #print("h_tks: \"{}\"".format(h_tks))
            if read_lines == 2:
                r_palette_name = h_tks[1]
                #print("r_palette_name: [{}]\n".format(r_palette_name))
        else:
            #print("Line [{}]: tokens \"{}\"".format(read_lines,tks))
            r_color_red = tks[0]
            r_color_green = tks[1]
            r_color_blue = tks[2]
            r_color_name_tks = tks[3].split("-")
            r_color_name = r_color_name_tks[0]
            colors.insert(read_colors,(r_color_red, r_color_green, r_color_blue, r_color_name.upper()))
            read_colors += 1
            '''
            print("r_color_red [{}]".format(r_color_red))
            print("r_color_green [{}]".format(r_color_green))
            print("r_color_blue [{}]".format(r_color_blue))
            print("r_color_name [{}]\n".format(r_color_name))
            '''


    #print("Colors: [{}]".format(colors))
    # Start file output, beginning with version number

    if mode == "header":
        print("#ifndef {}_S4C_H_".format(target_name.upper()))
        print("#define {}_S4C_H_".format(target_name.upper()))
        print("#include \"{}/sprites4curses/s4c-animate/animate.h\"\n".format(s4c_path))
        print("#define {}_S4C_H_VERSION \"{}\"".format(target_name.upper(),FILE_VERSION))
        print("#define {}_S4C_H_TOTCOLORS {}".format(target_name.upper(),read_colors))
        print("")
        print("/**")
        print(" * Declares S4C_Color array for {}.".format(target_name))
        print(" */")
        print("extern S4C_Color {}[{}];".format(target_name,read_colors+1))
        print("\n#endif")
        return 0
    if mode == "cfile":
        print("#include \"{}.h\"\n".format(target_name))
        print("S4C_Color {}[{}] = {{".format(target_name,read_colors+1))
        for color in colors:
            print("    {{ {}, {}, {}, \"{}\" }},".format(color[0],color[1],color[2],color[3]))
        print("};")


def main(argv):
    """! Main program entry."""
    if len(argv) != 4:
        print("Wrong number of arguments. Expected 4, got {}.".format(len(argv)))
        print("--> {}\n".format(argv))
        usage()
    else:
        mode = argv[1]
        if mode == "C-header":
            mode = "header"
        elif mode == "C-impl":
            mode = "cfile"
        else :
            print("Error: wrong mode request")
            usage()
        palette_path = argv[2]
        s4c_path = argv[3]
        convert_palette(mode,palette_path,s4c_path)

if __name__ == '__main__':
    main(sys.argv)

