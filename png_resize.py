#!/usr/bin/python3
"""! @brief Program that parses pngs from a passed spritesheet, to encode their color to a char per pixel."""

##
# @file png_resize.py
#
# @brief Program that resizes pngs to a desired size and overwrites them.
#
# @section description_png_resize Description
# The program overwrites the passed pngs with the resized version.
#
# Program expects the spritesheet filename as first argument, 
#   the sprite width as second arg,
#   the sprite heigth as third arg.
#
# @section libraries_main Libraries/Moodules
# - Pillow (https://pillow.readthedocs.io/en/stable/)
#   - Access to image manipulation functions.
# - sys standard library (https://docs.python.org/3/library/sys.html)
#   - Access to command line arguments.
# - os standard library (https://docs.python.org/3/library/os.html)
#   - Access to program name.
#
# @section notes_png_resize Notes
# - The pngs are overwritten by default.
#
# @section todo_png_resize TODO
# - Offer option to output to new files and not overwrite.
#
# @section author_spritesheet Author(s)
# - Created by jgabaut on 24/02/2022.
# - Modified by jgabaut on 24/02/2022.

# Imports
from PIL import Image
import os
import sys

# Functions
def usage():
    """! Prints correct invocation."""
    print("Wrong arguments. Needed: directory, desired sprite width, desired sprite height.")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sprites_directory> <sprite_width> <sprite_height>")

def resize_sprites(directory, targetSizeX, targetSizeY):
    """! Resizes all png files in the passed directory to the specified size.
    @param directory   The input directory with the pngs.
    @param targetSizeX   The target width.
    @param targetSizeY   The target height.
    """
    # Set the target size
    size = (targetSizeX, targetSizeY)

    # Loop through all PNG files in the current directory
    for filename in os.listdir(directory):
        if filename.endswith('.png'):
            # Open the file
            with Image.open(os.path.join(directory, filename)) as im:
                # Convert to RGB mode
                im = im.convert('RGB')
                # Get the bounding box of the non-transparent pixels
                bbox = im.getbbox()
                # Crop the image to the bounding box
                im = im.crop(bbox)
                # Resize the image to the target size
                im = im.resize(size, Image.ANTIALIAS)
                # Save the image with the same filename
                im.save(os.path.join(directory, filename))

def main(argv):
    """! Main program entry."""
    if len(argv) != 4:
        usage()
    else:
        direc = argv[1]
        spriteSizeX = int(argv[2])
        spriteSizeY = int(argv[3])
        resize_sprites(direc,spriteSizeX, spriteSizeY)


if __name__ == "__main__":
    main(sys.argv)
