# Installing cmocka

## Use a package manger (also on Windows)

If you're using a BSD or Linux distribution, cmocka is already packaged and
you should find it in your package manager.

    <your package manager> install cmocka-devel
    or
    <your package manager> install libcmocka-devel

For Windows it is recommended to use: https://vcpkg.io/

    vcpkg install cmocka

## Building from source

### Requirements

#### Common requirements

In order to build cmocka, you need to install several components:

- A C compiler
- [CMake](http://www.cmake.org) >= 3.5.0.

Note that these version numbers are version we know works correctly. If you
build and run cmocka successfully with an older version, please let us know.

### Building
First, you need to configure the compilation, using CMake. Go inside the
`build` dir. Create it if it doesn't exist.

GNU/Linux, MacOS X, MSYS/MinGW:

    cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ..
    make

On Windows you should choose a makefile gernerator with -G, for example:

   cmake -G "Visual Studio 12 2013" -DCMAKE_BUILD_TYPE=Debug /path/to/source

You can also use the CMake GUI which is shipped with CMake. It will list all
available generators for MSVC on Windows. We only support Visual Studio 2013
or newer which supports C99.

#### CMake standard options
Here is a list of the most interesting options provided out of the box by
CMake.

- CMAKE_BUILD_TYPE:     The type of build (can be Debug Release MinSizeRel
                        RelWithDebInfo)
- CMAKE_INSTALL_PREFIX: The prefix to use when running make install (Default
                        to /usr/local on GNU/Linux and MacOS X)
- CMAKE_C_COMPILER:     The path to the C compiler
- CMAKE_CXX_COMPILER:   The path to the C++ compiler

#### CMake options defined for cmocka

Options are defined in the following files:

- DefineOptions.cmake

They can be changed with the -D option:

`cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug -DUNIT_TESTING=ON ..`

#### Browsing/editing CMake options

In addition to passing options on the command line, you can browse and edit
CMake options using `cmake-gui.exe` (Windows) or `ccmake` (GNU/Linux
and MacOS X).

- Go to the build dir
- On Windows: run `cmakesetup`
- On GNU/Linux and MacOS X: run `ccmake ..`

More at https://cmake.org/runningcmake/

### Installing

If you want to install cmocka after compilation run:

    make install

### Running

The cmocka library can be found in the `build/src` directory.
You can run the binaries in `build/examples/*` which is a
are example tests.

### Testing

As mention above you can turn on the unit tests and make it possible to easily
execute them:

`cmake -DCMAKE_BUILD_TYPE=Debug -DUNIT_TESTING=ON ..`

After that you can simply call `make test` in the build directory or if you
want more output simply call `ctest -V`.

If you want to enable the generation of coverage files you can do this by
using the following options:

`cmake -DCMAKE_BUILD_TYPE=Profiling -DUNIT_TESTING=ON ..`

After building it you will see that you have several coverage options in

`make help`

You should have `make ExperimentalCoverage` and running it will create
coverage files. The result is stored in Testing directory.

## About this document

This document is written using [Markdown][] syntax, making it possible to
provide usable information in both plain text and HTML format. Whenever
modifying this document please use [Markdown][] syntax.

[markdown]: http://www.daringfireball.net/projects/markdown
