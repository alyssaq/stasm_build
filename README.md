# STASM 4 build scripts

This is a fork from <https://github.com/juan-cardelino/stasm> to include a command line utility and a straightforward set of build instructions for mac/unix.

[Stasm](<http://www.milbo.users.sonic.net/stasm>) is a C++ library for finding key facial features (BSD licensed). 

[OpenCV](http://opencv.org/) 2.X or 3.X is required.

Build scripts to compile the STASM library (version 4 and later):

* CMakeLists.txt: cmake build script to compile the STASM library and its examples
* STASMConfig.cmake.in: template to generate a STASMConfig.cmake which could be useful to use STASM as a library from another project
* *.cpp.diff: patches to correct some compilation errors in unix.


## Build Instructions

1. Download STASM source code from: <http://www.milbo.users.sonic.net/stasm/download.html> (Tested on Version 4.1.0)
2. Extract zip file to the folder `stasm4.1.0`
3. Now run these steps in order:

```
$ cd stasm4.1.0
$ git clone https://github.com/alyssaq/stasm_build.git
$ ./stasm_build/build.sh
```

## Test stasm command utility
If all the build steps went well, there will be an executable called `stasm_util` in the `build` folder.

To run:

    $ ./stasm_util -f ../data ../data/testface.jpg

To show face points on image:

    $ ./stasm_util -s -f ../data ../data/testface.jpg


## License
BSD-2