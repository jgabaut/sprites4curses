import os
import sys
from PIL import Image

# Expects the spritesheet filename as first argument, 
#   the sprite width as second arg,
#   the sprite heigth as third arg.

def usage():
    print("Wrong arguments. Needed: directory, desired sprite width, desired sprite height.")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sprites_directory> <sprite_width> <sprite_height>")

def resize_sprites(directory, targetSizeX, targetSizeY):
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

if __name__ == "__main__":
    if len(sys.argv) != 4:
        usage()
    else:
        direc = sys.argv[1]
        spriteSizeX = int(sys.argv[2])
        spriteSizeY = int(sys.argv[3])
        resize_sprites(direc,spriteSizeX, spriteSizeY)
