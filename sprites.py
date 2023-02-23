from PIL import Image
import sys
import glob
import re
import os
# Expects the sprite directory name as first argument.
# File names format inside the directory should be "imageNUM.png".

def usage():
    print("Wrong arguments. Needed: sprites directory")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sprites_directory>")


def color_distance(c1, c2):
    r1, g1, b1 = map(int, c1)
    r2, g2, b2 = map(int, c2)
    return sum([(r1 - r2)**2, (g1 - g2)**2, (b1 - b2)**2]) ** 0.5

def create_palette(colors):
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
    
def print_converted_sprites(direc) :

    frames = 1 # We start the count from one so we account for one more cell for array declaration
    for file in sorted(glob.glob('{}/*.png'.format(direc)), key=lambda f: int(re.search(r'\d+', f).group())):
           frames += 1
    print("\nchar sprites[{}][18][18] =".format(frames) + "{\n")
    idx = 1           
    for file in sorted(glob.glob('{}/*.png'.format(direc)), key=lambda f: int(re.search(r'\d+', f).group())):
            # example usage: convert a sprite and print the result
            sprite = convert_sprite(file)
            print("\t//Frame {}, file {}".format(idx,file))
            print("\t{")
            for row in sprite:
                comma = -1;
                print("\t\""+row+"\",")
            print("\t},"+ "\n")
            idx += 1
    print("};")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        usage()
    else:
        directory = sys.argv[1]
        print_converted_sprites(directory)

