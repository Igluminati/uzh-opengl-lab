## Transformations - Exercise 2 (3 + 1 points)

### Goals:

- Understand and apply geometric transformations to 3D objects.
- Implement and animate transformations such as rotation, translation, and scaling.
- Understand and experiment with normals.
- Visualize normals using line-based geometry.
- Understand the role of the normal matrix and observe its effect on normal transformations.

### Tasks (3 points):

1. Object Transformations

    The starting point of this exercise is two objects (torus and cube) located at the same position.

    - Apply rotation, translation, and scaling to a shape object by implementing the transformation functions provided in the `Shape` class.

2. Cube Animation

    To check the implementation of the previous transformations, animate the cube so that it

    - rotate around the axis (0, 1, 0).
    - scale over time, increasing and decreasing its size.

    The animation logic should be implemented in the `update()` function.

3. Multiple Objects Animation

    Create 4 torus objects positioned around the cube.

    - each torus should be placed on one side of the cube with a small offset.
    - Animate the toruses so that:
        - they maintain their positions and size relative to the cube
        - each torus rotates around the axis connecting its center to the cube center.

    This creates the effect of the toruses orbiting around the cube.

4. Visualizing Normals

    - Display the normals of the torus objects using a `MultiLine` object.
    - Modify the shader to enable the torus to be optionally rendered using colors derived from its normals when `normalsAsColor` is enabled.

5. Normal Matrix

    - Compute the normal matrix and apply it to the normals.
    - Use `useNormalMatrix` to enable and disable this function.

    - Compare the visual difference between with and without the normal matrix. 
    
        Which of these two methods gives the correct result? What causes the difference?

    - Apply the correct transformation to the normal visualization lines so that they correctly follow the torus geometry.

The video "task_possible_solution.mp4" shows one possible solution for these tasks. Note that your solution can differ depending on the scaling and offset between toruses and cube that you chose.

### Bonus Task (+1 point):

Currently, 4 toruses are arranged around the cube. 
Modify the code so that the number of toruses arranged circling around the cube can be changed using a variable `numberOfTorus`. The video "bonus_task_possible_solution.mp4" shows how such a solution would look like for 10 toruses. The toruses should automatically be distributed evenly around the cube in a circular pattern.

### Where to Implement Your Code:

- You will need to implement the missing functions in the following files:

    1. Shape.cpp
        - Implement the transformation functions.
        - Calculate the model matrix.

    2. GLExercise.cpp
        - Placement of the cube and toruses.
        - Animation logic.
    
    3. MultiLine.cpp
        - Create the line segments representing normals
        - draw the normals using `GL_LINES`

    4. Shaders

- We’ve placed TODO comments where you must fill in logic. You can also modify or add any other code you need.

### How to Build
Similar to Exercise 1, this project includes a setup script and a CMake configuration to generate the build files.

If you successfully ran Exercise 1, your environment is already set up correctly.

To build the project:
1. Run the setup script.
2. Use CMake to generate the build files.
3. Compile the project using your preferred build system.

### How to Submit:

Create a **.zip** file containing:

- the source code (please include only the source files, the **src/** and **shader/** folders)
- a screenshot or a short screenshot video of the rendering window of the result working on your computer.

Upload the zip file to **OLAT** before the deadline.

### Additional Information:

Some screenshots and videos of the initial state and as references to the exercise tasks are in the **doc/** folder.
