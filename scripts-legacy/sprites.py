#!/usr/bin/python3
"""! @brief Program that parses pngs from a passed directory, to encode their color to a char per pixel."""

##
# @file sprites.py
#
# @brief Program that parses pngs from a passed directory, to encode their color to a char per pixel.
#
# @section description_sprites Description
# The png parsing uses Pillow, and the mapping is done against a preset color list.
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
# @section notes_sprites Notes
# - Color map should have the same order as the palette used to index the sprites.
#
# @section todo_sprites TODO
# - Check if the encoded value is exceeding latin literals.
#
# @section author_sprites Author(s)
# - Created by jgabaut on 24/02/2023.
# - Modified by jgabaut on 03/01/2024.

# Imports
from PIL import Image
import sys
import glob
import re
import os
import math

## The file format version.
FILE_VERSION = "0.2.2"

# Expects the sprite directory name as first argument.
# File names format inside the directory should be "imageNUM.png".

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments. Needed: mode, sprites directory")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <mode> <sprites_directory>")
    print("\n  mode:  \n\ts4c-file\n\tC-header\n\tC-impl")
    exit(1)


def color_distance(c1, c2):
    """! Calculates the distance in color between two rgb tuples.
    @param c1   The first input color to measure.
    @param c2   The second input color to measure.
    @return  The color distance between the two.
    """
    r1, g1, b1 = c1
    r2, g2, b2 = c2
    red_distance = r1 - r2
    green_distance = g1 - g2
    blue_distance = b1 - b2
    distance = math.sqrt(red_distance ** 2 + green_distance ** 2 + blue_distnce ** 2)
    return distance

def convert_sprite(file):
    """! Takes a image file and converts each pixel to a char representation of its color (closest match to CHAR_MAP).

    @param file   The image file to convert.

    @return  The converted sprite as a char matrix.
    """
    img = Image.open(file)

    # Convert the image to an RGB mode image with 256 colors
    img = img.convert('P', palette=Image.ADAPTIVE, colors=256)

    # Get the color palette
    palette = img.getpalette()

    # Map the color indices to their RGB values in the palette
    rgb_palette = [(palette[i], palette[i+1], palette[i+2]) for i in range(0, len(palette), 3)]

    # Create the CHAR_MAP dictionary based on the color values
    CHAR_MAP = {}
    char_index = 0
    for color in rgb_palette:
        if color not in CHAR_MAP:
            if chr(ord('1') + char_index) == '?':
                CHAR_MAP[color] = '\\?'
            else:
                CHAR_MAP[color] = chr(ord('1') + char_index)
            char_index += 1

    # Convert each pixel to its corresponding character representation
    chars = []
    for y in range(img.size[1]):
        line = ""
        for x in range(img.size[0]):
            color_index = img.getpixel((x, y))
            r, g, b = rgb_palette[color_index]
            if (r, g, b) in CHAR_MAP:
                line += CHAR_MAP[(r, g, b)]
            else:
                # Get the closest color in the CHAR_MAP
                closest_color = min(CHAR_MAP,
                                    key=lambda c:
                                    color_distance(c, (r, g, b)))
                line += CHAR_MAP[closest_color]
        chars.append(line)

    return chars

def print_converted_sprites(mode, direc):
    """! Takes a mode between (s4c, header, cfile) and a directory containing image file and calls convert_sprite on each one.
    Then it outputs all the converted sprites to stdout, including the necessary brackets to have a valid C array declaration.
    According to the passed mode, the C header, the C file, or the version-tagged s4c-file may be generated.
    @param direc   The directory of image files to convert and print.
    """
    if mode != "s4c" and mode != "header" and mode != "cfile" :
        print("Unexpected mode value in print_converted_sprites: {}".format(mode))
        usage()
    # We start the count from one so we account for one more cell for array declaration
    frames = 1
    target_name = os.path.basename(os.path.normpath(direc)).replace("-","_")

    for file in sorted(glob.glob('{}/*.png'.format(direc)),
                       key=lambda f:
                       int(re.search(r'\d+', f).group())):
           if frames == 1 :
               ref_img = Image.open(file) #Open reference file to get output dimension. WIP
               xsize = ref_img.size[0]+1
               ysize = ref_img.size[1]+1
           frames += 1

    # Start file output, beginning with version number

    if mode == "s4c" :
        print("{}".format(FILE_VERSION))
    elif mode == "header":
        print("#ifndef {}_S4C_H_".format(target_name.upper()))
        print("#define {}_S4C_H_".format(target_name.upper()))
        print("#define {}_S4C_H_VERSION \"{}\"".format(target_name.upper(),FILE_VERSION))
        print("")
        print("/**")
        print(" * Declares animation matrix vector for {}.".format(target_name))
        print(" */")
        print("extern char {}[{}][{}][{}];".format(target_name,frames,ysize,xsize))
        print("\n#endif")
        return 0
    elif mode == "cfile":
        print("#include \"{}.h\"\n".format(target_name))

    print("char {}[{}][{}][{}] = ".format(target_name,frames,ysize,xsize) + "{\n")
    idx = 1
    for file in sorted(glob.glob('{}/*.png'.format(direc)),
                      key=lambda f:
                      int(re.search(r'\d+', f).group())):
           # convert a sprite and print the result
           sprite = convert_sprite(file)
           print("\t//Frame {}".format(idx))
           print("\t{")
           for row in sprite:
               print("\t\t\""+row+"\",")
           print("\t},"+ "\n")
           idx += 1
    print("};")


def main(argv):
    """! Main program entry."""
    if (len(argv) -1) != 2:
        print("Wrong number of arguments. Expected 2, got {}.".format(len(argv)-1))
        print("--> {}\n".format(argv[1:]))
        usage()
    else:
        mode = argv[1]
        if mode == "s4c-file":
            mode = "s4c"
        elif mode == "C-header":
            mode = "header"
        elif mode == "C-impl":
            mode = "cfile"
        else :
            print("Error: wrong mode request")
            print("--> Found: {}".format(mode))
            print("--> Expected: \'C-impl\' | \'C-header\' | \'s4c-file\'\n")
            usage()
        directory = argv[2]
        print_converted_sprites(mode, directory)

if __name__ == '__main__':
    main(sys.argv)
