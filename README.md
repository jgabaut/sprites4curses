# sprites4curses

A library of scripts and C functions to deal with sprites in ncurses.

## Table of Contents

+ [Scripts](#scripts)
  + [Prerequisites](#prerequisites_scripts)
  + [sprites.py](#sprites_py)
  + [sheet_converter.py](#sheet_converter_py)
  + [cut_sheet_.py](#cut_sheet_py)
  + [png_resize.py](#png_resize_py)
+ [animate.h](#animate)
  + [Prerequisites](#prerequisites_animate)
  + [Terminal capabilities](#terminal_capabilities)
  + [demo.c](#demo_c)
+ [Scripts usage](#scripts_usage)
+ [palette.gpl](#palette_gpl)

## Scripts <a name = "scripts"></a>

## Prerequisites <a name = "prerequisites_scripts"></a>

To use the python scripts you need to install Pillow, using `pip`:

#### `pip install Pillow`

### sprites.py <a name = "sprites_py"></a>

This is a python script that converts PNG's to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments a directory with the images to convert.

### sheet_converter.py <a name = "sheet_converter_py"></a>

This is a python script that converts a single PNG spritesheet to a char representation.
The output text should be a valid C declaration for a 3D char array.

It expects as arguments the spritesheet file name, the sprite width, the sprite height, the thickness of the separator between sprites, and the start coordinate or the first sprite's left corner.

### cut_sheet.py <a name = "cut_sheet_py"></a>

This is a python script that cuts a single PNG spritesheet to a number of sprites, and puts them in the passed directory.

It expects as arguments the spritesheet file name, the output directory name, the sprite width, the sprite height, the thickness of the separator between sprites, and the start coordinate or the first sprite's left corner.

### png_resize.py <a name = "png_resize_py"></a>

This is a python script that resizess PNG's to a desired size.

It expects as arguments a directory with the images to resize, and two ints for width and height of the resulting PNGs.

## animate.c and animate.h <a name = "animate"></a>

This is a C library offering some functions to display an animation read from a formatted text file. It's rather small.

```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C                                1             49            153            233
C/C++ Header                     1             20              5             68
-------------------------------------------------------------------------------
SUM:                             2             69            158            301
-------------------------------------------------------------------------------
```

`animate\_sprites()` is useful in a initialised WINDOW, it boxes the window and displays the animation snugly.

`animate\_sprites\_at\_coords()` does the same, but has 2 more parameters to start displaying at any coord in a window big enough to fit the animation.

You can look at the demo.c program to see how you can request the animation after setup.
The file format expected is compatible with sprites.py specs.

### Prerequisites <a name = "prerequisites_animate"></a>

### Terminal capabilities <a name = "terminal_capabilities"></a>

Since it needs support from terminal capabilities, it may return some errors if your terminal doesn't offer the needed options.

At the moment your solution is to change terminal or help investigate your issues by forcing the check to pass, I may add an unsafe option to do this in a later version.

You can find a doxyfile to generate documentation in `documentation`.

### demo.c <a name = "demo_c"></a>

This is a demo program showing how to use the animate library functions. Check out its source code after running it!

- To run the C demo program, do:
  #### The demo is meant to run with the provided file.
  #### `make; ./demo demofile.txt`

- To be fancy you can use process substitution in bash to give the python output directly as an argument:

  #### `make; ./demo <( python sprites.py <directory> )`

# Scripts usage <a name = "scripts_usage"></a>

- To run the sprites script and redirect output on "file.txt", give a directory to get the png's from:

  #### File names in the directory should follow a imageX.png, imageX+1.png pattern.
  #### `python sprites.py <directory>   > file.txt`

- To run the sheet converter script and redirect output on "file.txt", give all required arguments:

  #### `python sheet_converter.py <sheet file> <sprite width> <sprite height> <separator thickness> <first sprite left corner X> <first sprite LC Y>   > file.txt`

- To run the sheet cutter script, give the sheet png file and the output directory:

  #### `python cut_sheet.py <sheet file> <output dir> <sprite width> <sprite height> <separator thickness> <first sprite left corner X> <first sprite LC Y>`

- To run the png resize script, give all required arguments:

  #### `python png_resize.py <sprites directory> <sprite width> <sprite height>`
  ### This overwrites the source pngs, so be careful.

Possible animation glitches if the frame rate is too high, add in-between frames and longer frametime as needed.

## palette.gpl <a name = "palette_gpl"></a>

This is a GIMP palette file.
It's used by the library to initialise the color pairs for curses to display the sprites.
It's also useful in the first place for exporting PNG with the correct color alignment.
Info on how to use it are in the palette-README.md file.
