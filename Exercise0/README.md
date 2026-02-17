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

### What I've Learnt

GLFW is a library that handles the windowing functions - how to create a window, reading keyboard/mouse input, managing the OpenGL context. It gives you a canvas to draw on and tells the program when the user presses keys or moves the mouse.

GLEW is a library that loads OpenGL functions. It quires the graphics driver at runtime and gives the program access to them. Without the graphics driver, you can't call most OpenGL functions beyond the ancient ones.

The shader source code exists in separate plain-text files with GLSL code:
- ``src/Cube.vert`` - the vertex shader
- ``src/Cuve.frag`` - the fragment shader

GLSL is the OpenGL Shading Language, which looks like C. Each file starts with ``#version 410 core`` declaring the GLSL version.

The shader source code is loaded as such (in GLExample.cpp):
1. Read the files from disc into strings (lines 17-18)
2. Create shader objects on the GPU (lines 22-23)
3. Upload source and compile (lines 25-26, implemented at lines 54-72). ``glShaderSource`` sends the string to the GPU, ``glCompileShader`` compiles it
4. Link into a program (lines 29-36). A shader program bundles the vertex and fragment shaders together so the gpu can run them as a pipeline
5. Delete the individual shader objects (lines 44-45). Once linked into the program, the standalone objects are no longer needed
6. At render time, ``glUseProgram(program)`` (line 99) activates the shader program before drawing

The information of the cube is defined in ``src/Model.cpp``, inside the namespace ``CubeData`` (lines 14-124). There exists four hardcoded arrays which define the cube:
- Vertices (lines 16-47) - there are 24 vertex positions (x,y,z). There are 24 rather than 8 because each face needs it own copy of the corner vertices (so each face can have its own normal and colour)
- Colours (lines 49-80) - one RPG colour per vertex. Each group of 4 vertices (one face) share the same colour: yellow, red, green, blue, cyan, magenta.
- Normals (lines 82-113) - one normal vector per vertex. Each face's 4 vertices share the same outward-pointing normal (e.g left face =``(-1,0,0)``, right face =``(1,0,0)``)
- Triangles (lines 115-123) - 36 indices defining 12 triangles (2 per face). Each line of 6 indices forms a quad from two triangles, e.g. ``0, 1, 2, 2, 3, 0``
Then `createVertexArray` (lines 137-188) uploads all of this to the GPU via buffer objects and wired them into a VAO. ``draw()`` (lines 190-197) binds that VAO and issues ``glDrawElements`` to render the 36 indices as triangles.

The drawing of the cube in the render loop occurs in ``GLExample.cpp``. The ``render()`` method is the draw call per frame (``bool GLExample::render() {...}``). Line 105 - ``cube->draw()`` is the actual draw call. That dispatches to ``Cube::draw()`` in Model.cpp (``void Cube::draw() {...}``)

You change the background colour in an OpenGL app by modifying ``glClearColor`` which sets the background colour. In lines 95-96 of GLExample.cpp  there are four arguments (read,green,blue,alpha), where each is a float from ``0.0`` to ``1.0``. Initially, it is ``(0,0,0,1)`` - black. ``glClear`` then fills the framebuffer with that colour.

```
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

To compile the program after an edit:
- ``cd Exercise0/build``
- ``cmake --build .``
