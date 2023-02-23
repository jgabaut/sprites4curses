# sprites4curses

A library of scripts to deal with sprites in ncurses.

## sprites.py

This is a python script that converts png's to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments a directory with the images to convert. 
There's a dependency on Pillow to do the image conversion.

## sheet-converter.py

This is a python script that converts a single png spritesheet to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments the spritesheet file name, the sprite width, the sprite height, the thickness of the separator between sprites, and the start coordinate or the first sprite's left corner. 
There's a dependency on Pillow to do the image conversion.

## png-resize.py

This is a python script that resizess png's to a desired size.

It expects as arguments a directory with the images to resize, and two ints for width and height of the resulting pngs.
There's a dependency on Pillow to do the image conversion.

## palette.gpl

This is a GIMP palette file, useful for exporting PNG with the correct color alignment.
Info on how to use it are in the palette-Readme.md file.

## animate.c and animate.h

This is a C program to display an animation read from a formatted text file.
The format expected is compatible with sprites.py specs.

## demo.c

This is a demo program that calls directly in its main, the demo() function from the animate library.

## animate.c

This is a program that offers the demo() function to display an animation encoded in text format.

# Usage

To use the python scripts you need to install Pillow:

#### `pip install Pillow`

+ To run the sprites script and redirect output on "file.txt", give a directory to get the png's from:

  #### File names in the directory should follow a imageX.png, imageX+1.png pattern.
  #### `python sprites.py <directory>   > file.txt`

+ To run the sheet converter script and redirect output on "file.txt", give all required arguments:

  #### `python sheet_converter.py <sheet file> <sprite width> <sprite height> <separator thickness> <starting coordinates>   > file.txt`

+ To run the png resize script, give all required arguments:

  #### `python png-resize.py <sprites directory> <sprite width> <sprite height>`
  ### This overwrites the source pngs, so be careful. 

+ To run the C demo program, you do:
  #### File format should be a valid char array declaration, or one sprite row per line.
  #### `make; ./demo file.txt`

+ To be fancy you can use process substitution in bash to give the python output directly as an argument:

  #### `make; ./demo <( python sprites.py <directory> )`
  #### Possible animation glitches if the frame rate is too high, add in-betweeners as needed.
