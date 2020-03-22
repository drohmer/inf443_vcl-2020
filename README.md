# VCL



## Introduction


VCL - Visual Computing Library - is a simple lightweight library on top of OpenGL provided to ease learning of 3D programming while avoiding re-coding everything from scratch (matrices, mesh structures, etc.). The library provides several helper structure and functions to set up 3D scene with interactive and/or animated elements.


The objective of the library is to be simple as simple as possible to read and use.
The majority of VCL structures and functions are aimed to be minimalistic without hidden states. The code remains fully compatible with direct raw OpenGL calls and user-defined shaders. The animation loop itself is entirely defined by the user.


The code contains two main parts:
* The VCL library itself in `vcl/` directory - contains the helper functions and structures
* Some example 3D scenes in `scenes/` directory. Each scene is fully defined in its subdirectory, and the switch between different scene is set using a keyword defined in `scene/current_scene.hpp` file.



## Compile the library



The compilation can be done either using the provided
* **Makefile**: Linux/MacOS only 
* **CMakeLists.txt** using CMake (Linux/MacOS/Windows)


The library has one external dependency: [GLFW](https://www.glfw.org/) which can be installed through standard packages in Linux/MacOS (see the provided detailed tutorials).



* [Command lines to compile in Linux/MacOS](doc/compilation.md#command_line)
* **Detailed tutorials** to set up your system and compile on
  * [Linux/Ubuntu](doc/compilation.md#Ubuntu)
  * [MacOS](doc/compilation.md#MacOS)
  * [Windows](doc/visual_studio.md)



You may edit the code using
* QtCreator on Linux/MacOS: [Setting up and using QtCreator](doc/qtcreator.md)
* Visual Studio on Windows



## Basic usage of VCL

<!-- Basic structure and functions associated to 2/3/4D vectors and matrices are provided. -->



Coming soon ...


<!-- ### Doxygen Documentation -->




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