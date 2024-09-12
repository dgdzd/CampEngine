# CampEngine++

## Table of contents
- [Introduction](#introduction)
- [Using it](#using-it)
  - [Compiling](#compiling)
    - [CMake](#cmake)
  - [Using a pre-compiled library](#using-a-pre-compiled-library)

## Introduction
CampEngine++ is a minimalist 2D game engine based on the language C++.
This game engine makes heavy use of GLFW and Freetype. It is currently under 
developement.

## Using it
There is currently no user-friendly way to use CampEngine. However,
you can try [compiling it](#compiling) or [using a pre-compiled
library](#using-a-pre-compiled-library).

### Compiling
The first thing to do is clone this repository. Choose the directory
you want to work in then execute the following command on your terminal:
``` commandline
git clone https://github.com/dgdzd/CampEngine.git
```
Now, go to the root directory of the repository:
``` commandline
cd CampEngine
```
You can now compile the project using [CMake](#cmake).

#### CMake
First thing to do is [download and install CMake](https://cmake.org/download/) 
if it wasn't already done. Now, use any C++ IDE which support CMake 
(CLion, Visual Studio), select lib_CampEngine++ as the target to compile
and hit Build. Next, type in the following command to install the
library:
``` commandline
cmake --build cmake-build-release --target install
```

### Using a pre-compiled library
Documentation coming soon.