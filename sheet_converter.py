#!/usr/bin/python3
"""! @brief Program that parses pngs from a passed spritesheet, to encode their color to a char per pixel."""

##
# @file sheet_converter.py
#
# @brief Program that parses pngs from a passed spritesheet, to encode their color to a char per pixel.
#
# @section description_spritesheet Description
# The program supports 8 colors at the moment. The png parsing uses Pillow, and the mapping is done against a preset color list.
# The list is described in palette.gpl to aid in exporting images with the correct color indexing.
#
# Program expects the spritesheet filename as first argument, 
#   the sprite width as second arg, 
#   the sprite height as third, 
#   separator size (thickness) as fourth, 
#   a 0 or 1 for starting coords of the first sprite (0 if sheet has no edge separator) as fifht argument.
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
# @section notes_spritesheet Notes
# - Color map should have the same order as the palette used to index the sprites.
#
# @section todo_spritesheet TODO
# - The limitation to 8 colors will be overcome soon.
#
# @section author_spritesheet Author(s)
# - Created by jgabaut on 24/02/2022.
# - Modified by jgabaut on 27/02/2022.

# Imports
from PIL import Image
import sys
import os
import math

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments. Needed: filename, sprite width, sprite height, separator size, 0/1 respectively if the edge (say 0,0) has separator.")
    print("0/1 is the starting position of first sprite.")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sheet_file> <sprite_width> <sprite_heigth> <separator_size> <0/1>")
    
def color_distance(c1, c2):
    """! Calculates the distance in color between two rgb tuples.
    @param c1   The first input color to measure.
    @param c2   The second input color to measure.
    @return  The color distance between the two.

    """
    r1, g1, b1 = c1
    r2, g2, b2 = c2
    distance = math.sqrt((r1 - r2) ** 2 + (g1 - g2) ** 2 + (b1 - b2) ** 2)
    return distance 

def convert_spritesheet(filename, spriteSizeX, spriteSizeY, separatorSize, startCoords):
    """! Converts a spritesheet to a 3D char array representation of pixel color and then prints it with the needed brackets and commas.
    @param filename   The input spritesheet file.
    @param spriteSizeX   The sprite width.
    @param spriteSizeY   The sprite height.
    @param separatorSize   Thickess of separator pixels.
    @param startCoords  Coords (a,a) of left corner of first sprite.
    """

    sprite_size = (spriteSizeX, spriteSizeY)  # size of each sprite
    separator_size = separatorSize  # size of separator between sprites
    start_x, start_y = startCoords, startCoords  # starting coordinates of the first sprite
    
    
    img = Image.open(filename)
    width, height = img.size
    sprites_per_row = (width - start_x + separator_size) // (sprite_size[0] + separator_size)
    sprites_per_column = (height - start_y + separator_size) // (sprite_size[1] + separator_size)
    sprites = []

    for i in range(height // (sprite_size[1] + separator_size * (sprites_per_column - 1))):
        for j in range(sprites_per_row):
            for k in range(sprites_per_column):
                sprite_x = start_x + j * (sprite_size[0] + separator_size) #+ (separator_size if j > 0 else 0)
                sprite_y = start_y + k * (sprite_size[1] + separator_size) + i * (sprite_size[1] + separator_size * (sprites_per_column - 1))# + (separator_size if k > 0 else 0)
                sprite = img.crop((sprite_x, sprite_y, sprite_x + sprite_size[0], sprite_y + sprite_size[1]))
                sprite = sprite.convert('P', palette=Image.ADAPTIVE, colors=256)
                palette = sprite.getpalette()
                rgb_palette = [(palette[n], palette[n+1], palette[n+2]) for n in range(0, len(palette), 3)]
                # Create the CHAR_MAP dictionary based on the color values
                CHAR_MAP = {}
                char_index = 1
                for color in rgb_palette:
                    if color not in CHAR_MAP:
                        CHAR_MAP[color] = chr(ord('a') + char_index)
                        char_index += 1
                chars = []
                for y in range(sprite.size[1]):
                    line = ""
                    for x in range(sprite.size[0]):
                        color_index = sprite.getpixel((x, y))
                        r, g, b = rgb_palette[color_index]
                        if (r, g, b) in CHAR_MAP:
                            line += CHAR_MAP[(r, g, b)]
                        else:
                            # Get the closest color in the CHAR_MAP
                            closest_color = min(CHAR_MAP, key=lambda c: color_distance(c, (r, g, b)))
                            line += CHAR_MAP[closest_color]
                    chars.append(line)

                sprites.append(chars)

    print("\nchar sprites[{}][{}][{}] =".format(len(sprites) +1, spriteSizeY+1, spriteSizeX+1) + "{\n")
    for i, sprite in enumerate(sprites):
        print("\t//Sprite {}, index {}".format(i + 1, i))
        print("\t{")
        for row in sprite:
            print("\t\t\"" + row + "\",")
        print("\t}," + "\n")
    print("};")

def main(argv):
    """! Main program entry."""
    if len(argv) != 6:
        usage()
    else:
        filename = argv[1]
        spriteSizeX = int(argv[2])
        spriteSizeY = int(argv[3])
        separatorSize = int(argv[4])
        startCoords = bool(int(argv[5]))
        convert_spritesheet(filename,spriteSizeX,spriteSizeY,separatorSize,startCoords)

if __name__ == "__main__":
    main(sys.argv)


