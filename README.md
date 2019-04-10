scg3
====

An extensible OpenGL 3 / C++11 scene graph library for teaching computer graphics along the programmable pipeline.

Copyright 2014-2019 Volker Ahlers

#### Documentation and example code

* header file [scg3/scg3.h](https://github.com/vahlers/scg3/blob/master/scg3/scg3.h) (cf. 3rd comment)
* folder [scg3/doc](https://github.com/vahlers/scg3/tree/master/scg3/doc) (incl. example code)
* webpage http://vahlers.github.io/scg3/ (incl. Doxygen API documentation) 

#### Source code

Git repository https://github.com/vahlers/scg3

#### Download

`git clone https://github.com/vahlers/scg3.git`

#### Building

Use Eclipse or Visual Studio, cf. documentation in [scg3/scg3.h](https://github.com/vahlers/scg3/blob/master/scg3/scg3.h).

Projects:

* **scg3**: scene graph library (static library)
* **scg3_example**: example application

Prerequisites:

* C++11 compiler, e.g., GCC 4.6, LLVM/Clang 3.1, Visual C++ 11.0/Visual Studio 2012 (or higher)
* OpenGL 3.2 graphics driver (or higher)
* GLFW 3.2.0 (or higher), cf. http://www.glfw.org/

#### Building using CMake on Linux

This project contains CMake files to build the project from the command line or import it into IDEs like CLion. (Only tested on Linux)

After navigating to the root directory of the project, you can build the library and example code using these commands:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../build-output ..
make install -j8   # replace 8 with CPU core count
```

In case you want to install the scg3 library globally into your system, use `cmake -DCMAKE_INSTALL_PREFIX=/usr ..` and `sudo make install -jX` instead.
Uninstallation can be done using `sudo make uninstall`.
