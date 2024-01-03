# sprites4curses

  A library of scripts and C functions to deal with sprites in ncurses.

  It also offers a seamless transition into raylib API, by providing wrapper functions to reuse assets on both graphic modes. Link to raylib repo: [link](https://github.com/raysan5/raylib)

## Table of Contents

+ [Scripts](#scripts)
  + [Prerequisites](#prerequisites_scripts)
  + [sprites.py](#sprites_py)
  + [sheet_converter.py](#sheet_converter_py)
  + [cut_sheet_.py](#cut_sheet_py)
  + [png_resize.py](#png_resize_py)
  + [palette.py](#palette_py)
+ [animate.h](#animate)
  + [Prerequisites](#prerequisites_animate)
  + [Raylib extension](#raylib_ext)
  + [Terminal capabilities](#terminal_capabilities)
  + [demo.c](#demo_c)
+ [Scripts usage](#scripts_usage)
+ [palette.gpl](#palette_gpl)

# Scripts <a name = "scripts"></a>

## Prerequisites <a name = "prerequisites_scripts"></a>

  To use the python scripts you need to install Pillow, using `pip`:

#### `pip install Pillow`

  To produce the `Makefile` needed to compile `./demo`, you will need:

  - `automake`
  - `autoconf`
  - `make`
  - `python`, to generate `./s4c-animate/palette.h` and `./s4c-animate/palette.c` from `./palette.gpl`

  To use the Raylib extension, you need to have installed `raylib`. Refer to lib docs for help: [link](https://github.com/raysan5/raylib#build-and-installation).
  - More info at [this section](#raylib_ext).

### sprites.py <a name = "sprites_py"></a>

  This is a python script that converts PNG's to a char representation.
  The output text should be a valid C declaration for a 3D char array.

  It expects as arguments:

  - A mode of operation: `s4c-file`, `C-impl` , `C-header`.
  - A directory with the images to convert.

### sheet_converter.py <a name = "sheet_converter_py"></a>

  This is a python script that converts a single PNG spritesheet to a char representation.
  The output text should be a valid C declaration for a 3D char array.

  It expects as arguments:

  - A mode of operation: `s4c-file`, `C-impl` , `C-header`.
  - The spritesheet file name
  - The sprite width
  - The sprite height
  - The thickness of the separator between sprites
  - The start coordinate (aka, the first sprite's left corner).

### cut_sheet.py <a name = "cut_sheet_py"></a>

  This is a python script that cuts a single PNG spritesheet to a number of sprites, and puts them in the passed directory.

  It expects as arguments:

  - The spritesheet file name
  - The output directory name
  - The sprite width
  - The sprite height
  - The thickness of the separator between sprites
  - The start coordinate (aka, the first sprite's left corner).

### png_resize.py <a name = "png_resize_py"></a>

  This is a python script that resizess PNG's to a desired size.

  It expects as arguments:

  - A directory with the images to resize
  - Two ints for width and height of the resulting PNGs.


### palette.py <a name = "palette_py"></a>

  This is a python script that generates C files from a `palette.gpl` file.

  It expects as arguments:

  - A mode of operation: `C-impl` , `C-header`.
  - The palette file
  - The relative path to the `s4c` directory, so that the generated header can correctly include `animate.h`

## animate.c and animate.h <a name = "animate"></a>

  This is a C library offering some functions to display an animation read from a formatted text file. It's rather small.

  ```
  -------------------------------------------------------------------------------
  Language                     files          blank        comment           code
  -------------------------------------------------------------------------------
  C                                2             95            304            523
  C/C++ Header                     2             41             43            142
  -------------------------------------------------------------------------------
  SUM:                             4            136            347            665
  -------------------------------------------------------------------------------
  ```

  `s4c_animate\_sprites()` is useful in a initialised WINDOW, it boxes the window and displays the animation snugly.

  `s4c_animate\_sprites\_at\_coords()` does the same, but has 2 more parameters to start displaying at any coord in a window big enough to fit the animation.

  You can look at the `demo.c` program to see how you can request the animation after setup.
The file format expected is compatible with `s4c-file` specs, see `sprites.py` or `sheet_converter.py` for info about the basic file format.

### Prerequisites <a name = "prerequisites_animate"></a>

### Raylib extension <a name = "raylib_ext"></a>

  To produce the Raylib `./demo`, run:

  - `./configure --enable-raylib=yes && make rebuild`

  In case you want to include `animate.h` as Raylib extension in a C file, you should define this macro to make sure the included declarations work as expected:

  - `S4C_RAYLIB_EXTENSION`

### Terminal capabilities <a name = "terminal_capabilities"></a>

  Since it needs support from terminal capabilities, it may return some errors if your terminal doesn't offer the needed options.

  At the moment your solution is to change terminal or help investigate your issues by forcing the check to pass, I may add an unsafe option to do this in a later version.

  You can find a doxyfile to generate documentation in `documentation`.

### demo.c <a name = "demo_c"></a>

  This is a demo program showing how to use the animate library functions. Check out its source code after running it!

  - To run the C demo program, do:

    **The demo is meant to run with the provided file, since a different-sized animation would require little tweaks to the code.**

    `autoreconf; automake --add-missing; autoreconf; automake --add-missing`
    `autoreconf; ./configure`
    `make; ./demo demofile.txt`

  - To be fancy you can use process substitution in bash to give the python output (`demofile.txt`, from `sprites.py` and `sample-sprits`) directly as an argument:

    `make; ./demo <( python sprites.py <directory> )`

# Scripts usage <a name = "scripts_usage"></a>

  - To run the sprites script and redirect output on "file.txt", give a directory to get the png's from:

    **File names in the directory should follow a imageX.png, imageX+1.png pattern.**

    `python sprites.py <mode> <directory>   > file.txt`

  - To run the sheet converter script and redirect output on "file.txt", give all required arguments:

    `python sheet_converter.py <mode> <sheet file> <sprite width> <sprite height> <separator thickness> <first sprite left corner X> <first sprite LC Y>   > file.txt`

  - To run the sheet cutter script, give the sheet png file and the output directory:

    `python cut_sheet.py <sheet file> <output dir> <sprite width> <sprite height> <separator thickness> <first sprite left corner X> <first sprite LC Y>`

  - To run the png resize script, give all required arguments:

    **This overwrites the source pngs, so be careful.**

    `python png_resize.py <sprites directory> <sprite width> <sprite height>`

  Possible animation glitches if the frame rate is too high, add in-between frames and longer frametime as needed.

## palette.gpl <a name = "palette_gpl"></a>

This is a GIMP palette file.
It's used by the library to initialise the color pairs for curses to display the sprites.
It's also useful in the first place for exporting PNG with the correct color alignment.
You can also use it to generate a C implementation file for you color palette.
Info on how to use it are in the [palette-README.md](./palette-README.md) file.
