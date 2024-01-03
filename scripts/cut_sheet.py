#!/usr/bin/python3
"""! @brief Program that cut a passed png spritesheet, and saves the sprites to a passed directory."""

##
# @file cut_sheet.py
#
# @brief Program that cut a passed png spritesheet, and saves the sprites to a passed directory.
#
# @section description_cut_spritesheet Description
# The png parsing uses Pillow, and the mapping is done against a preset color list.
# The list is described in palette.gpl to aid in exporting images with the correct color indexing.
#
# Program expects the spritesheet filename as first argument, then
#   the output directory,
#   the sprite width,
#   the sprite height,
#   separator size (thickness),
#   X coord of left corner of the first sprite (0 if sheet has no edge separator),
#   Y coord of left corner of the first sprite (0 if sheet has no edge separator).
#
# @section libraries_main Libraries/Moodules
# - Pillow (https://pillow.readthedocs.io/en/stable/)
#   - Access to image manipulation functions.
# - sys standard library (https://docs.python.org/3/library/sys.html)
#   - Access to command line arguments.
# - os standard library (https://docs.python.org/3/library/os.html)
#   - Access to program name.
# - math standard library (https://docs.python.org/3/library/math.html)
#   - Access to sqrt.
#
# @section notes_cut_spritesheet Notes
# - Color map should have the same order as the palette used to index the sprites.
#
# @section todo_cut_spritesheet TODO
# - Check if the encoded value is exceeding latin literals.
#
# @section author_cut_spritesheet Author(s)
# - Created by jgabaut on 04/03/2023.
# - Modified by jgabaut on 03/01/2024.

# Imports
# Imports
from PIL import Image
import sys
import os
import math

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments.");
    print("\nUsage:\tpython {} <sheet_file> <output_directory> <sprite_width> <sprite_heigth> <separator_size> <startX> <startY>".format(os.path.basename(__file__)))

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
    distance = math.sqrt(red_distance ** 2 + green_distance ** 2 + blue_distance ** 2)
    return distance

def cut_spritesheet(filename, output_directory, spriteSizeX, spriteSizeY, separatorSize, startX, startY):
    """! Converts a spritesheet to a set of individual sprite images.
    @param filename   The input spritesheet file.
    @param output_directory  The directory where output images will be saved.
    @param spriteSizeX   The sprite width.
    @param spriteSizeY   The sprite height.
    @param separatorSize   Thickess of separator pixels.
    @param startX    X coord of left corner of first sprite.
    @param startY    Y coord of left corner of first sprite.
    """
    sprite_size = (spriteSizeX, spriteSizeY)  # size of each sprite
    separator_size = separatorSize  # size of separator between sprites
    start_x, start_y = startX, startY  # starting coordinates of the first sprite

    img = Image.open(filename)
    width, height = img.size
    sprites_per_row = (width - start_x + separator_size) // (sprite_size[0] + separator_size)
    sprites_per_column = (height - start_y + separator_size) // (sprite_size[1] + separator_size)

    img = img.convert('P', palette=Image.ADAPTIVE, colors=256)

    sprite_index = 1
    for i in range(sprites_per_row):
        for j in range(sprites_per_column):
            sprite_x = start_x + j * (sprite_size[0] + separator_size)
            sprite_y = start_y + i * (sprite_size[1] + separator_size)
            sprite = img.crop((sprite_x, sprite_y, sprite_x + sprite_size[0], sprite_y + sprite_size[1]))
            output_file = os.path.join(output_directory, f"image{i * sprites_per_column + j + 1}.png")
            sprite.save(output_file)

def main(argv):
    """! Main program entry."""
    if (len(argv)-1) != 7:
        print("Wrong number of arguments. Expected 7, got {}.".format(len(argv) -1))
        print("--> {}\n".format(argv[1:]))
        usage()
    else:
        filename = argv[1]
        outdir = argv[2]
        spriteSizeX = int(argv[3])
        spriteSizeY = int(argv[4])
        separatorSize = int(argv[5])
        startX = int(argv[6])
        startY = int(argv[7])
        cut_spritesheet(filename,outdir,spriteSizeX,spriteSizeY,separatorSize,startX,startY)

if __name__ == "__main__":
    main(sys.argv)


