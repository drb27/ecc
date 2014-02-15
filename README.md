ecc
===

The Enum Compile Command (ecc) is a simple utility which takes enum definitions written in pseudo-c++ and spits out
c++ files containing the type definition, and a set of constants and functions which allow the runtime conversion
of an enum value into a string. These files can then be included/compiled into your program. 

This utility is of little practical use. It was written mainly as a way for me to learn a little bit about scanning
and parsing with the quintessential gnu utilities _flex_ and _bison_.

Building
--------

A makefile is provided. The only dependencies are g++, flex, and bison. Ensure these are installed, then type 'make'. 

Running
-------

The simplest command line format is:

linux:~/$ ecc -c <inputfile>

Try it out with the example file provided, ex.def
