## Geometry - Exercise 1 (3 + 1 points)

### Goals:

- Generate a parametric torus using the standard equations.
- Add a small warp or twist to the torus shape.
- Offset vertices along their normals.
- Support wireframe rendering mode (and optionally face culling).

### Tasks:

1. Generate Torus Geometry

    - Use R and r as the major and minor radius.
    - Discretize the angles into numSegments (around the major radius) and numTubeSegments (around the tube).
    - Add a twist factor that modifies the angle or radius (so the torus is slightly warped).
    - Calculate vertex positions, vertex normals, and store them in arrays.
    - Build the triangle faces (faces vector) using indices of those vertices.

2. Offset Along Normals
    - Each vertex should be shifted by offset * normal.

3. Rendering Modes

    - Wireframe: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE).
    - Filled: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL).
    - Optionally enable face culling with glEnable(GL_CULL_FACE).

### Where to Implement Your Code:

- You’ll edit (or complete) three key files:

    1. Torus.h / Torus.cpp

        - Implement the parametric torus and warp (twist factor).
        - Implement offset along normals.

    2. GLExample.cpp

        - Set up wireframe/fill toggles.
        - Create and render the Torus object.

- We’ve placed TODO comments where you must fill in logic. You can also modify or add any other code you need.

Important: Similar to the first exercise this project includes a setup script and a CMake config file to generate the building scripts for different build systems. You do this the same way as for exercise 0, so it should be straightforward to build the project using the setup script and CMake. 

Exercise 0 is a complete, ready-to-run code, but Exercise 1 is not. if you have successfully run Exercise 0, then your environment is already set up for Exercise 1. For Exercise 1, it is not a complete, ready-to-run code. You need to implement certain functions as required, fill in some missing code, and turn it into a fully functional program.


### How to Submit:

- Once your code compiles and works, create a **.zip** file with

    - the source code (please include only the source files, the **src/** folder)
    - and the screenshots of the rendering window working on your computer (Example screenshots of the result can be found in the doc folder).

        - (i): The warped torus in filled mode. (Parameter settings: wireframeMode = false, R=5.0f, r=1.0f, numSegments=32, numTubeSegments=16, offset=0.0, twistFactor=0.0)
        - (ii): The warped torus in wireframe mode. (Parameter settings: wireframeMode = true, R=5.0f, r=1.0f, numSegments=32, numTubeSegments=16, offset=0.0, twistFactor=0.0)
        - (iii): (ii) + offset. (Parameter settings: wireframeMode = true, R=5.0f, r=1.0f, numSegments=32, numTubeSegments=16, offset=0.5, twistFactor=0.0)
        - (iv): (iii) + slightly warped. (Parameter settings: wireframeMode = true, R=5.0f, r=1.0f, numSegments=32, numTubeSegments=16, offset=0.5, twistFactor=0.2)
            - Submit the resource code and screenshots (i) ~ (iv) to earn 3 points.
        - (Optionally)(v): (iv) + face culling.
            - (Optionally) Submit screenshot (v) to earn 1 additional point.

- Upload the zip-file to OLAT.






