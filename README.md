# sprites4curses

  A library of scripts and C functions to deal with sprites in ncurses.

  It also offers a seamless transition into raylib API, by providing wrapper functions to reuse assets on both graphic modes. Link to raylib repo: [link](https://github.com/raysan5/raylib)

## Table of Contents

+ [Scripts](#scripts)
+ [animate.h](#animate)
  + [Prerequisites](#prerequisites_animate)
  + [Raylib extension](#raylib_ext)
  + [Terminal capabilities](#terminal_capabilities)
  + [demo.c](#demo_c)
+ [palette.gpl](#palette_gpl)

# Scripts <a name = "scripts"></a>

  From version 0.5, all python scripts have been moved to a separate repo ([s4c-scripts](https://github.com/jgabaut/s4c-scripts)), included as a submodule.

  To maintain backwards compatibility:
  - New stub scripts have been put at the old path in the repo.
  - An `init` target was added to the `Makefile.am`, so that you remember to initialise the submodule before trying to run any script.
  This will be removed in an upcoming minor version, so you should update your scripts to use the new path.

## animate.c and animate.h <a name = "animate"></a>

  This is a C library offering some functions to display an animation read from a formatted text file. It's rather small.

  ```
  -------------------------------------------------------------------------------
  Language                     files          blank        comment           code
  -------------------------------------------------------------------------------
  C                                2            114            380            644
  C/C++ Header                     2             47             50            167
  -------------------------------------------------------------------------------
  SUM:                             4            161            430            811
  -------------------------------------------------------------------------------
  ```

  `s4c_animate\_sprites()` is useful in a initialised WINDOW, it boxes the window and displays the animation snugly.

  `s4c_animate\_sprites\_at\_coords()` does the same, but has 2 more parameters to start displaying at any coord in a window big enough to fit the animation.

  You can look at the `demo.c` program to see how you can request the animation after setup.
The file format expected is compatible with `s4c-file` specs, see `sprites.py` or `sheet_converter.py` for info about the basic file format.

### Prerequisites <a name = "prerequisites_animate"></a>

  To use the python scripts you need to install Pillow, using `pip`:

#### `pip install Pillow`

  To produce the `Makefile` needed to compile `./demo`, you will need:

  - `automake`
  - `autoconf`
  - `make`
  - `python`, to generate `./s4c-animate/palette.h` and `./s4c-animate/palette.c` from `./palette.gpl`

  To use the Raylib extension, you need to have installed `raylib`. Refer to lib docs for help: [link](https://github.com/raysan5/raylib#build-and-installation).
  - More info at [this section](#raylib_ext).

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

    `make; ./demo <( python sprites.py <directory> )

## palette.gpl <a name = "palette_gpl"></a>

This is a GIMP palette file.
It's used by the library to initialise the color pairs for curses to display the sprites.
It's also useful in the first place for exporting PNG with the correct color alignment.
You can also use it to generate a C implementation file for you color palette.
Info on how to use it are in the [palette-README.md](./palette-README.md) file.
