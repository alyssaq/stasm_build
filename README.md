# STASM 4 build scripts

This is a fork from <https://github.com/juan-cardelino/stasm> to include a command utility and a straightforward set of build instructions for mac/linux.

[Stasm](<http://www.milbo.users.sonic.net/stasm>) is a C++ library for finding key facial features (BSD licensed). [OpenCV](http://opencv.org/) is required.

Build scripts to compile the STASM library (version 4 and later):

* CMakeLists.txt: cmake build script to compile the STASM library and its examples
* STASMConfig.cmake.in: template to generate a STASMConfig.cmake which could be useful to use STASM as a library from another project
* *.cpp.diff: patches to correct some compilation errors in unix.


## Build Instructions

1. Download STASM source code from: <http://www.milbo.users.sonic.net/stasm>
2. Extract zip file to a folder referred to as `STASM_DIR`
3. Now run these steps in order:

```
$ cd STASM_DIR
$ git clone STASM_BUILD
$ patch apps/appmisc.cpp < stasm_build/patches/appmisc.cpp.20140201.diff
$ patch apps/shapefile/shapefile.cpp < stasm_build/patches/shapefile.cpp.20140201.diff
$ mkdir build && cd build
$ cmake ../
$ make
```

## Test stasm command utility
If all the build steps went well, there will be an executable called `stasm_util` in the `build` folder.

To run:

	$ ./build/stasm_util -f data data/testface.jpg

## License
MIT