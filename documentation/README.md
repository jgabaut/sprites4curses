# Documentation

This folder contains a doxyfile, used by `doxygen` to generate documentation from source.

Prerequisites for building docs are:

`doxygen` is needed to get the html and latex versions.
`doxygen-latex` or `texlive` are needed to compile the latex to a pdf version of the documentation.

You can use the doxyfile by running, from the root dir of the repo:

`make doc`

Afterwards you will find a `docs.pdf` file in this directory.
