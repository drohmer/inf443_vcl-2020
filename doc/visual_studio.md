# Tutorials to compile VCL on Windows

## Software installation

If you don't have install it yet, download and install the two following softwares

* [CMake](https://cmake.org/)
* [Visual Studio](https://visualstudio.microsoft.com/vs/)


The tutorial expect that you have Visual Studio 2019 (community edition - free for students and open source project). <br>
Note that Visual Studio is the complete Microsoft IDE + compiler - do not confound it with _Visual Studio Code_ aimed at being a lighter text editor (no embedded compiler).

## Load the project

* Start Visual Studio, and use the option **continue without code**
* Once the interface is available, follow 
  * **File** -> **Open** -> **CMake**
  * Look for the file **CMakeLists.txt** in the VCL directory where you download the code.

The project should load in Visual Studio. The hierarchy of files should be available through the _Solution Explorer_.

![](assets/visual_studio/01_load_cmake.gif)

## Compiling

The compilation can be run from the Build menu (or F7).

Check that the compilation end succesfully before trying to execute the program.

![](assets/visual_studio/02_compile.gif)



## Executing the program

You can execute the program using the green arrow from the panel. (You may need to select `pgm` in the proposed choices)

For the first run, the program should end with an error indicating that some file (usually the shader) cannot be found (see example in the following animation).

![](assets/visual_studio/03_error_path.gif)

### Explanation of the error

- Once executed, the program try to read exernal files (shaders, images, etc).
- These files are expected to be accessible from the executable at the relative path `scenes/...`
- By default, Visual Studio generate the executable in a temporary directory that doesn't follow this expected relative path.



### Solution to apply

- Check the directory where Visual Studio generate  `pgm.exe`
  - This directory can be found in the execution log (see the highlighted path in the video) -> _in this case it is in the `out/` directory placed at the root of the VCL library (may depend on your version of Visual Studio)._
- Copy the entire `scene/` directory of the library in the directory where `pgm.exe` is generated.
  - Note that you only have to copy `scene/` once for all. Even if you change the code, only the data are needed.
  - However, if you want to add new assets (texture, mesh files, etc) or change the shaders, don't forget to do update this copied directory.


![](assets/visual_studio/04_copy_execute.gif)