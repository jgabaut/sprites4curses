from PIL import Image
import sys
import os

# Expects the spritesheet filename as first argument, 
#   the sprite width as second arg, 
#   the sprite height as third, 
#   separator size (thickness) as fourth, 
#   a 0 or 1 for starting coords of the first sprite (0 if sheet has no edge separator) as fifht argument.

def usage():
    print("Wrong arguments. Needed: filename, sprite width, sprite height, separator size, 0/1 respectively if the edge (say 0,0) has separator.")
    print("0/1 is the starting position of first sprite.")
    print("\nUsage:\tpython {}".format(os.path.basename(__file__)) + " <sheet_file> <sprite_width> <sprite_heigth> <separator_size> <0/1>")

def convert_spritesheet(filename, spriteSizeX, spriteSizeY, separatorSize, hasEdgeSeparator):

    sprite_size = (spriteSizeX, spriteSizeY)  # size of each sprite
    separator_size = separatorSize  # size of separator between sprites
    start_x, start_y = hasEdgeSeparator, hasEdgeSeparator  # starting coordinates of the first sprite
    
    
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
                chars = []
                for y in range(sprite.size[1]):
                    line = ""
                    for x in range(sprite.size[0]):
                        color_index = sprite.getpixel((x, y))
                        r, g, b = rgb_palette[color_index]
                        if (r, g, b) in CHAR_MAP:
                            line += CHAR_MAP[(r, g, b)]
                        else:
                            closest_color = min(CHAR_MAP, key=lambda c: sum([(r - c[0])**2, (g - c[1])**2, (b - c[2])**2])**0.5)
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
    
if __name__ == "__main__":
    if len(sys.argv) != 6:
        usage()
    else:
        filename = sys.argv[1]
        spriteSizeX = int(sys.argv[2])
        spriteSizeY = int(sys.argv[3])
        separatorSize = int(sys.argv[4])
        hasEdgeSeparator = bool(int(sys.argv[5]))
        convert_spritesheet(filename,spriteSizeX,spriteSizeY,separatorSize,hasEdgeSeparator)

