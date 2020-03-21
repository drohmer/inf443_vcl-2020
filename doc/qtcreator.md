# Setting up QtCreator

- [1. Load project in QtCreator](#load)
- [2. Compiling the code](#compiling)
- [3. Executing the code](#executing)
- [4. Automatic completion](#completion)
- [5. File Navigation](#navigation)
- [Common Issues](#issue)

<br>

QtCreator is an IDE (Integrated Development Environment) for C++. It provides natively 

* color encoding
* code completion: automatic proposition of possible variable names, class methods, and show expected function arguments
* allows to quickly navigate through hierarchy of files: Use CTRL + left click on a variable or function to go to its declaration, or on include file to go to navigate to the corresponding one. Pressing F4 navigates between header (.hpp) and source (.cpp) files.
* integrate debuger (visualizing lines by lines the status of all your variables), as well as profiler.

QtCreator is able to load a complete project only from the generic CMakeLists.txt configuration file which is already provided. Editing a project with QtCreator doesn't impact the sources files.


<a name="load"></a>
## 1. Load project in QtCreator

Open a command line on the root directory (the directory that contains the file CMakeLists.txt)

```shell
qtcreator CmakeLists.txt &
```

![](assets/qtcreator/01_load_qtcreator.gif)


QtCreator should propose to configure the project. Once it is done, you will have access to the hierarchy of files from the left pannel.

Alternatively, you may also open QtCreator from you application startup and then open the CMakeLists.txt from it: File -> Open File or Projects -> then look for your CMakeLists.txt file.

Check here if you experiment problem to load the project: [Common Issues](#issue).

<a name="compiling"></a>
## 2. Compiling the code

The code can be compiled using the small hammer icon on the bottom left, or using the key shortcut: **CTRL+b**

![](assets/qtcreator/02_compile.gif)


<a name="executing"></a>
## 3. Executing the code

The code can be executed using the green arrow icon on the bottom left, or using the key shortcut: **CTRL+r** 

* the shortcut CTRL+r also run the compilation if needed.

<br>

The path of the run directory should be set to the root directory otherwise will stop with an error message will indicate that the shader or data file cannot be read (shown in the following image).

To this end

* Go to Projects (left panel)
* On the panel (Build & Run) select Run
* Observe the `Working Directory` entry and set it to the root path of the library

![](assets/qtcreator/03_set_path.gif)

_Explanations_

* The code expect to read some external files (shaders files, textures, etc.) in the scenes/ directory. The relative path of these files are within the code.
* The excutable should be run from a directory able to access these asset files from the same relative path.
* By default, the executable is run from the temporary parent directory in QtCreator where the executable binary is generated. So the program cannot access to the asset files.
* Either the `working directory` is changed, or, alternatively, you can also copy (only once) the `scene/` directory at the location of the binary file.

<a name="completion"></a>
## 4. Automatic completion

Once the project is loaded, automatic completion will appear automatically and help you write code and use the library.

![](assets/qtcreator/04_automatic_completion.gif)


<a name="navigation"></a>
## 5. Files navigation

In addition to the file hierarchy from the left panel, you can use `CTRL+left click` on element of code to naviguate through the code.

* `CTRL+left click` on a type goes to the type definition (usefull to understand the library).
* `CTRL+left click` on a function goes to its definition.
* `F4` switch between the header (.hpp) and implementation (.cpp) file. (usefull to switch between public signature of a function/class and its implementation).
* `CTRL+left click` on a variable goes to its declaration.
* `CTRL+left click` on a `#include [path]` navigate to this header file.

![](assets/qtcreator/05_naviguation.gif)


<a name="issue"></a>
## Common issue to load a project with QtCreator

When QtCreator fails to load your project it is often caused by conflicting temporary files.

* Everytime QtCreator load a project, it generates temporary files
  * CMakeListst.txt.user (in the current directory)
  * An entire temporary directory: build-`XX`-Desktop-Default in the parent directory.
* If you have failed previous attempt to open QtCreator, or if you moved your project directory to another place (or to another computer), these temporary files are not anymore coherent.
* You can safely delete this temporary files (CMakeListst.txt.user and the entire directory build-`XX`-Desktop-Default), and restart the process to open QtCreator.
