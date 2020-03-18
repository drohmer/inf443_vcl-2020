# VCL

## Introduction

VCL - Visual Computing Library - is a simple lightweight library on top of OpenGL provided to ease learning of 3D programming while avoiding re-coding everything from scratch (matrices, mesh structures, etc.). The library provides several helper structure and functions to set up 3D scene with interactive and/or animated elements.

The objective of the library is to be simple as simple as possible to read and use.
Majority of VCL structures and functions are aimed to be minimalistic without hidden states. The code remains fully compatible with direct raw OpenGL calls and user defined shaders. The animation loop itself be entirely defined by the user.

The code contains two main parts:
* The VCL library itself in `vcl/` directory - contains the helper functions and structures
* Some example 3D scenes in `scenes/` directory. Each scene is fully defined in its subdirectory, and the switch between different scene is set using a keyword defined in `scene/current_scene.hpp` file.


## Compiling and executing the library on Linux/MacOS

The only external dependency of VCL is [GLFW](https://www.glfw.org/).

The compilation can be done either using the provided Makefile or CMakeLists.txt (CMake).


In Linux/MacOS, the following commands should compile and execute the code (assuming your command line is opened in the root directory of the library).


__Using Make__
```shell
make
./pgm
```

__Using CMake__
```shell
mkdir build
cd build
cmake ..
make
cd ..
build/pgm
```

Note that the executable should be run from the root directory. 

_More precisely, the data (shaders and assets) defined in the scenes/ directory should be accessible from the running directory as files are read from this relative path._



### Setting up a computer running on Ubuntu

In the case you need to set up a personnal computer on Linux/Ubuntu from scratch, you may follow these steps

```shell
# Basic development tools (g++, make, etc)
sudo apt-get install build-essential

# CMake 
sudo apt-get install cmake 

# GLFW
sudo apt-get install glfw3-dev

# [Optionnal] QtCreator to edit files
sudo apt-get install qtcreator
```



### Setting up a computer running on MacOS

In the case you need to set up a personnal computer on MacOS from scratch, you may follow these steps

Check first that g++/clang++ is installed in typing in command line

```shell
g++ -v
```

(Follow the installation instruction if the OS propose to install it).

For the other dependencies, the easiest way is to use the package manager [Homebrew](https://brew.sh/). Follow the instructions of the website to install it.

Then install the necessary software and libraries

```shell
# The Library GLFW
brew install glfw

# CMake tool to compile
brew install cmake

# [Optionnal] QtCreator to edit files
brew cask install qt-creator
```


## Setting up QtCreator to compile and execute the code on Linux or MacOS



TBD

## Compiling and executing the code on Windows

TBD


## Basic usage of VCL

TBD




<!-- 
### Note on Compilation / Execution 

When editing the source code (without adding/removing files), you don't need to run CMake every time, but only call Makefile. The following command can be used from the vcl/ directory:

$ make -C build/

$ build/pgm


## Using QTCreator with CMake (Linux/MacOs)

Call qtcreator from vcl/ directory

$ qtcreator CMakeLists.txt &

Then follow the configuration steps from the GUI.

By default, a temporary directory build-cmake-Desktop-Default is created (in the parent directory of CMakeLists.txt file), as well as a file CMakeLists.txt.user (same directory than CMakeLists.txt file). Both can be removed safely.





## On Windows system with Visual Studio 

- Use CMakeLists.txt with Visual Studio
- Precompiled version of GLFW3 is provided (precompiled/glfw3_win)
- You need to copy data/ and shaders/ directories in the executable directory -->