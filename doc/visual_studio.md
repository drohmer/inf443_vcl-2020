# Tutorials to compile VCL on Windows

* [Software installation](#Software)
* [Load the project](#Project)
* [Compiling](#Compiling)
* [Executing the program](#Execution)
* [Note on language](#Language)
* [Possible issues](#Issue)

<br>

<a name="Software"></a>
## Software installation


Download and install
* [CMake](https://cmake.org/)

<br>

Then download and install (if it is not installed yet)
*  [Visual Studio](https://visualstudio.microsoft.com/vs/)
  * Make sure you select the options **Desktop development with C++** (to get C++ compiler) and to check **C++ CMake tools for Windows** during the installation procedure (see the image below).
  * _Note that it is a large software, so it can take some time_

![](assets/visual_studio/00_visual_studio_c++.jpg)

<br>



The tutorial expect that you have Visual Studio 2019 (community edition - free for students and open source project). <br>
Note that Visual Studio is the complete Microsoft IDE + compiler - do not confound it with _Visual Studio Code_ aimed at being a lighter text editor (no embedded compiler).


<a name="Project"></a>
## Load the project


* Start Visual Studio, and use the option **continue without code**
* Once the interface is available, follow 
  * **File** -> **Open** -> **CMake**
  * Look for the file **CMakeLists.txt** in the VCL directory where you download the code.


The project should load in Visual Studio. The hierarchy of files should be available through the _Solution Explorer_.


![](assets/visual_studio/01_load_cmake.gif)

<a name="Compiling"></a>
## Compiling

The compilation can be run from the Build menu (or F7).

Check that the compilation ends successfully before trying to execute the program.


![](assets/visual_studio/02_compile.gif)



<a name="Execution"></a>
## Executing the program


You can execute the program using the green arrow from the panel. (You may need to select `pgm` in the proposed choices)


For the first run, the program should end with an error indicating that some file (usually the shader) cannot be found (see the example in the following animation).


![](assets/visual_studio/03_error_path.gif)


### Explanation of the error


- Once executed, the program tries to read external files (shaders, images, etc).
- These files are expected to be accessible from the executable at the relative path `scenes/...`
- By default, Visual Studio generates the executable in a temporary directory that doesn't follow this expected relative path.





### Solution to apply

- Check the directory where Visual Studio generates  `pgm.exe`
  - This directory can be found in the execution log (see the highlighted path in the video) -> _in this case it is in the `out/` directory placed at the root of the VCL library (may depend on your version of Visual Studio)._
- Copy the entire `scene/` directory of the library in the directory where `pgm.exe` is generated.
  - Note that you only have to copy `scene/` once for all. Even if you change the code, only the data are needed.
  - However, if you want to add new assets (texture, mesh files, etc) or change the shaders, don't forget to do update this copied directory.


![](assets/visual_studio/04_copy_execute.gif)

<br>

<a name="Language"></a>
## Note on language


It is recommended that you install the English version of Visual Studio (instead of the French one for instance) - or change the language once Visual Studio has been installed ([see these steps for instance](https://agirlamonggeeks.com/2019/03/10/how-to-change-language-in-visual-studio-2019-after-installation/)).
* First the terminology will be more standard, especially for debug purposes.
* But more importantly, the compiler output will be much clean and only indicate warning or errors - the french version of the compiler displays every included header file, for every source file, which create huge amount of noise in the compilation output.

![](assets/visual_studio/05_language.jpg)
_Example on a small projects with four source files_ <br>
_Left - English version: The five steps of the compilation are visible and any warning or error can be seen easily.<br> Right - French version: The output is obfuscated by the notification of file inclusion; finding a warning or an error is much harder._

<br>

<a name="Issue"></a>
## Possible issues

* If the last step of the compilation fails (called linker) on glfw.lib, it means that the pre-compiled version of GLFW included with VLC isn't compatible with your version of Visual Studio or System. You may download the correct version of [precompiled GLFW library](https://www.glfw.org/download.html) for your case (32 bits/64 bits, VS version) and replace the provided lib in `lib_windows/glfw3_win`.

<br>

* If you have a persitent error after adding a new variable in a class (or change something in a header file), force the option **Rebuild All** at the compilation options (instead of "Build All").
 * Sometimes Visual Studio doesn't handle correctly the modifications in the header files, which are not propagated to the newly compiled filed, which leads at the end to some memory error. Forcing a "Rebuild" ensure that all files are fully recompiled (but it is slower). This step is not needed if you only change the .cpp files.