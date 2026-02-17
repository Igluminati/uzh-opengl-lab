## OpengGL - Exercise 0

The aim of this first exercise is to set up OpenGL on your computer and to compile and run a simple application. Further, we try to understand how a typical OpenGL application works.


### Tasks:

- Get the project up and running on your desktop/laptop (see 'Additional Information' below).

- Get an overview of the code and understand as much as you can (see 'Learning Targets' below).

- Find the position in the source code where the background color is set and then change the color according to the first 6 digits or your legi number (e.g. 20-789-5XX).


### How to Submit:

Once your are done, create a .zip file with the source code (please include only the source files, not the build folder) and upload it to OLAT together with a screenshot of the rendering window working in your computer.


### Learning Targets:

The coding part in this exercise is small because we want you to spend the time in checking the different parts of this program and read the above mentioned tutorials. To prepare for the rest of the course you should have understood:

...that GLFW is the windowing library of this program and it does a lot of magic for you

...that GLEW is a wrapper libary to load OpenGL extensions (we use this instead of glad which is often used in the tutorials)

...where the sourcecode in a shader is defined and how it is loaded

...where the information of the cube is defined

...where the "render loop" is running

...where the drawing of the cube in the "render loop" is happening.

...how you change the background color in an OpenGL app.


### Additional Information: 

What you need to get it running:

IDE & C++ compiler: Visual Studio with C++ installed (Win), Xcode (macOS) or some IDE with gcc (Linux) installed, for example QT Creator. We use Windows or macOS for these example, so it might be additional effort in case you want to use a Linux system. However, most of the things should compile under Linux as well.  

CMake: you can use the most recent version of cmake.

Libaries GLFW & GLEW:

Independently of the operation system we use vcpkg to manage the dependencies. 

- Win: Under Windows make sure to have Visual Studio 2013 or newer and git installed

- macOS: Make sure to have Xcode (or at least the Xcode command line utilities) installed. Also make sure to have brew installed as it is required to install some additional dependencies of the libraries managed by vcpkg. The output of vcpkg will conveniently tell which packages are required and the command to install them via brew. 

- Linux: Vcpkg should work under Linux as well. You might have to install additional dependencies using your package manager as with macOS.

To get the program running you can run the setup.sh (Mac & Linux) or the setup.bat (Windows) script. The script will clone vcpkg from their git repository and install the required libraries. Then, to get the program running you have to first configure the example with CMake and then generate a project file ("Configure" and "Generate" buttons in the CMake GUI). The source path is the folder where the CMakeLists.txt lays, the build path is the source path plus "/build". Now you should find a project file in the build directory which you can open and compile.

### Documentation & resources:

- [GLFW Documentation](http://www.glfw.org/docs/latest/index.html)
- [Glad Documentation on GitHub](https://github.com/Dav1dde/glad)
- [OpenGL - Getting started - FAQ](https://www.khronos.org/opengl/wiki/Getting_Started)
- [OpenGL-tutorial.org](http://www.opengl-tutorial.org)
- [Learn OpenGL tutorials [learnopengl.com]](https://learnopengl.com)
