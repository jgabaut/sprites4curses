#!/usr/bin/python3
"""! @brief Program that parses pngs from a passed directory, to encode their color to a char per pixel."""

##
# @file sprites.py
#
# @brief Program that parses pngs from a passed directory, to encode their color to a char per pixel.
#
# @section description_sprites Description
# The program supports 8 colors at the moment. The png parsing uses Pillow, and the mapping is done against a preset color list.
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
#
# @section notes_sprites Notes
# - Color map should have the same order as the palette used to index the sprites.
#
# @section todo_sprites TODO
# - The limitation to 8 colors will be overcome soon.
#
# @section author_sprites Author(s)
# - Created by jgabaut on 24/02/2022.
# - Modified by jgabaut on 24/02/2022.

# Imports
from PIL import Image
import sys
import glob
import re
import os
# Expects the sprite directory name as first argument.
# File names format inside the directory should be "imageNUM.png".

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments. Needed: sprites directory")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sprites_directory>")


def color_distance(c1, c2):
    """! Calculates the distance in color between two rgb tuples.
    @param c1   The first input color to measure.
    @param c2   The second input color to measure.
    @return  The color distance between the two.
    """
    r1, g1, b1 = map(int, c1)
    r2, g2, b2 = map(int, c2)
    return sum([(r1 - r2)**2, (g1 - g2)**2, (b1 - b2)**2]) ** 0.5

def create_palette(colors):
    """! Creates a palette by adding the colors passed as an array, then pads the palette.
    @param colors   The colors to put in the palette.
    @return  The filled and padded palette.
    """
    # create a new palette with the given colors
    palette = []
    for color in colors:
        palette += color

    # pad the palette with zeros to make it a multiple of 3 bytes
    if len(palette) % 3 != 0:
        pad_size = 3 - (len(palette) % 3)
        palette += [0] * pad_size

    return palette

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

    # Map the RGB values to their corresponding characters
    CHAR_MAP = {
        (0, 0, 0): 'k',  # black
        (255, 0, 0): 'r',  # red
        (0, 255, 0): 'g',  # green
        (255, 255, 0): 'y',  # yellow
        (0, 0, 255): 'b',  # blue
        (255, 0, 255): 'm',  # magenta
        (0, 255, 255): 'c',  # cyan
        (255, 255, 255): 'w',  # white
    }

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
                closest_color = min(CHAR_MAP, key=lambda c: color_distance(c, (r, g, b)))
                line += CHAR_MAP[closest_color]
        chars.append(line)

    return chars
    
def print_converted_sprites(direc):
    """! Takes a directory containing image file and calls convert_sprite on each one. Then it outputs all the converted sprites to stdout, including the necessary brackets to have a valid C array declaration.
    @param direc   The directory of image files to convert and print.
    """

    frames = 1 # We start the count from one so we account for one more cell for array declaration
    for file in sorted(glob.glob('{}/*.png'.format(direc)), key=lambda f: int(re.search(r'\d+', f).group())):
           frames += 1
    print("\nchar sprites[{}][18][18] =".format(frames) + "{\n")
    idx = 1           
    for file in sorted(glob.glob('{}/*.png'.format(direc)), key=lambda f: int(re.search(r'\d+', f).group())):
            # convert a sprite and print the result
            sprite = convert_sprite(file)
            print("\t//Frame {}, file {}".format(idx,file))
            print("\t{")
            for row in sprite:
                print("\t\""+row+"\",")
            print("\t},"+ "\n")
            idx += 1
    print("};")

def main(argv):
    """! Main program entry."""
    if len(argv) != 2:
        usage()
    else:
        directory = argv[1]
        print_converted_sprites(directory)

if __name__ == '__main__':
    main(sys.argv)

