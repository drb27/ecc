ecc
===

This is __ecc v0.3*beta*__. The Enum Compile Command (ecc) is a simple linux utility which takes enum definitions written in pseudo-c++ and 
spits out c++ files containing the type definition, and a set of constants and functions which allow the runtime conversion of an enum value into a string. These files can then be included/compiled into your program. 

This utility is of little practical use. It was written mainly as a way for me to learn a little bit about scanning
and parsing with the quintessential gnu utilities _flex_ and _bison_.

Building
--------

A makefile is provided. The only dependencies are g++, flex, and bison. Ensure these are installed, then type `make`. 
If you are unsure how to install flex or bison, check the package manager for your linux distribution. On Ubuntu/mint, commands such as `apt-get install flex` and `apt-get install bison` will probably do it for you. 

Running
-------

The simplest command line format is:

`linux:~/$ ecc -c <inputfile>`

Try it out with the example file provided, _ex.def_. The output will be written to _ex.c_ and _ex.h_ by default. 

Contributions
-------------

You are encouraged to contribute improvements to this code. The official repository is at http://github.com/drb27/ecc. You can check out the issues, some of these are labelled __`helpwanted`__.

License
-------

This software is made available under the MIT license. This is a simple, permissive license which places very few restrictions on your free use of this code. Please see the LICENSE file in the root of the repository for the full text. 

New in this release
-------------------

Here are the issues which have been addressed since the previous release. You can see more details in the issue log at github. 

|Issue # | Description |
|--------|-------------|
|5	 | Generator includes timestamp in output|
|6 	 | Refactoring of generator/defgen|
|9 	 | Automatic dependencies for build system|
|10	 | Compiler warnings added|
|11	 | longstring support added|
|12	 | Member order is now preserved|
|13	 | Default code output file has .cpp extension|
|14	 | Namespace support added|
|15	 | Fixed indentation bug in generated output|

Release Log
-----------

|Release|Date|Description|
|-------|----|-----------|
|v0.2beta|16th February, 2014|Initial baseline release|
|v0.3beta|26th February, 2014|Added support for namespaces,longstrings, and warnings|



