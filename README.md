# sprites4curses

A library of scripts to deal with sprites in ncurses.

## sprites.py

This is a python script that converts PNG's to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments a directory with the images to convert.
There's a dependency on Pillow to do the image conversion.

### sheet_converter.py

This is a python script that converts a single PNG spritesheet to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments the spritesheet file name, the sprite width, the sprite height, the thickness of the separator between sprites, and the start coordinate or the first sprite's left corner.
There's a dependency on Pillow to do the image conversion.

### png_resize.py

This is a python script that resizess PNG's to a desired size.

It expects as arguments a directory with the images to resize, and two ints for width and height of the resulting PNGs.
There's a dependency on Pillow to do the image conversion.

## palette.gpl

This is a GIMP palette file.
It's used by the library to initialise the color pairs for curses to display the sprites.
It's also useful in the first place for exporting PNG with the correct color alignment.
Info on how to use it are in the palette-Readme.md file.

## animate.c and animate.h

This is a C library offering some functions to display an animation read from a formatted text file.
`animate\_file()` is useful to animate in a initialised WINDOW.

You can look at the demo.c program to see how you can request the animation after setup.
The file format expected is compatible with sprites.py specs.

Since it needs support from terminal capabilities, it may return some errors if your terminal doesn't offer the needed options.
At the moment your solution is to change terminal or help investigate your issues by forcing the check to pass, I may add an unsafe option to do this in a later version.

### demo.c

This is a demo program showing how to use the animate library functions.


# Usage

To use the python scripts you need to install Pillow:

#### `pip install Pillow`

- To run the sprites script and redirect output on "file.txt", give a directory to get the png's from:

  #### File names in the directory should follow a imageX.png, imageX+1.png pattern.
  #### `python sprites.py <directory>   > file.txt`

- To run the sheet converter script and redirect output on "file.txt", give all required arguments:

  #### `python sheet_converter.py <sheet file> <sprite width> <sprite height> <separator thickness> <first sprite left corner X> <first sprite LC Y>   > file.txt`

- To run the png resize script, give all required arguments:

  #### `python png_resize.py <sprites directory> <sprite width> <sprite height>`
  ### This overwrites the source pngs, so be careful.

  ## The demo program is meant to show how to correctly call animate_file() from animate.h.

- To run the C demo program, you do:
  #### The demo is meant to run with the provided file.
  ####
  #### `make; ./demo demofile.txt`

- To be fancy you can use process substitution in bash to give the python output directly as an argument:

  #### `make; ./demo <( python sprites.py <directory> )`
  #### Possible animation glitches if the frame rate is too high, add in-between frames as needed.
