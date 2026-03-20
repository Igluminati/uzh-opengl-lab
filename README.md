# UZH OpenGL Lab

Exercises for the Computer Graphics course at UZH, Spring 2026.

## Contents

- [Exercises](#exercises)
- [Build](#build-per-exercise)
- [GLM: Core Types](#glm-core-types)
- [GLM: Transforms](#glm-transforms)
- [GLM: Useful Functions](#glm-useful-functions)
- [Transform Matrices](#transform-matrices-reference)
- [OpenGL: Core Concepts](#opengl-core-concepts)
- [OpenGL: Setup Pattern](#opengl-setup-pattern)
- [OpenGL: Draw Pattern](#opengl-draw-pattern)
- [GLFW](#glfw)
- [Animation Patterns](#animation-patterns)
- [Shader Uniforms](#shader-uniforms-sending-data-from-cpu)
- [MultiLine: Drawing Normal Vectors](#multiline-drawing-normal-vectors)
- [Normal Matrix](#normal-matrix-when-and-why)
- [normalsAsColor](#normalsascolor-colouring-by-normal-direction)
- [MVP Matrix](#mvp-matrix)
- [Coordinate Spaces](#coordinate-spaces)
- [Shaders](#shaders)
- [Normals](#normals)
- [Face Culling and Depth Test](#face-culling-and-depth-test)

## Exercises

| Exercise | Topic |
|----------|-------|
| Exercise 0 | Setup |
| Exercise 1 | Introduction |
| Exercise 2 | Transformations |

## Build (per exercise)

```bash
cd ExerciseN
bash setup.sh          # installs vcpkg deps (glfw3, glew, glm), skip if already done
cmake -B build -S .
cmake --build build
./build/exercise
```

## GLM: Core Types

| Type | Description |
|------|-------------|
| `glm::vec2/3/4` | 2/3/4-component float vector |
| `glm::mat3` | 3x3 float matrix |
| `glm::mat4` | 4x4 float matrix |
| `glm::uvec3` | 3-component unsigned int vector |

## GLM: Transforms

`#include <glm/gtc/matrix_transform.hpp>`

All functions take an input matrix as first argument and return a new matrix. Pass `glm::mat4(1.0f)` (identity) to get a pure transform.

```cpp
glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
glm::mat4 R = glm::rotate(glm::mat4(1.0f), angle_radians, glm::vec3(ax, ay, az));
glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
```

Model matrix composition, standard order:
```cpp
modelMatrix = T * R * S;   // scale first, then rotate, then translate
```

Normal matrix (corrects normals under non-uniform scale):
```cpp
glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
```

## GLM: Useful Functions

```cpp
glm::normalize(v)          // unit vector
glm::cross(a, b)           // cross product
glm::dot(a, b)             // dot product
glm::length(v)             // vector magnitude
glm::radians(degrees)      // degrees -> radians
glm::degrees(radians)      // radians -> degrees
```

## Transform Matrices (reference)

**Translation:**
```
⎡ 1  0  0  tx ⎤
⎢ 0  1  0  ty ⎥
⎢ 0  0  1  tz ⎥
⎣ 0  0  0   1 ⎦
```

**Scale:**
```
⎡ sx  0   0   0 ⎤
⎢  0  sy  0   0 ⎥
⎢  0   0  sz  0 ⎥
⎣  0   0   0  1 ⎦
```

**Rotation around X:**
```
⎡ 1     0       0     0 ⎤
⎢ 0   cos θ  -sin θ   0 ⎥
⎢ 0   sin θ   cos θ   0 ⎥
⎣ 0     0       0     1 ⎦
```

**Rotation around Y:**
```
⎡  cos θ   0   sin θ   0 ⎤
⎢    0     1     0     0 ⎥
⎢ -sin θ   0   cos θ   0 ⎥
⎣    0     0     0     1 ⎦
```

**Rotation around Z:**
```
⎡ cos θ  -sin θ   0   0 ⎤
⎢ sin θ   cos θ   0   0 ⎥
⎢   0       0     1   0 ⎥
⎣   0       0     0   1 ⎦
```

Shear skews an object along one axis proportional to its displacement along another. No built-in GLM function; construct the matrix manually and multiply it into the model matrix. Off-diagonal entries in the top-left 3x3 introduce shear between the corresponding axes.

**Shear X by Y** (x moves as y increases):
```
⎡ 1  shy  0  0 ⎤
⎢ 0   1   0  0 ⎥
⎢ 0   0   1  0 ⎥
⎣ 0   0   0  1 ⎦
```

**Shear X by Z** (x moves as z increases):
```
⎡ 1   0  shz  0 ⎤
⎢ 0   1   0   0 ⎥
⎢ 0   0   1   0 ⎥
⎣ 0   0   0   1 ⎦
```

**Shear Y by X** (y moves as x increases):
```
⎡  1   0  0  0 ⎤
⎢ shx  1  0  0 ⎥
⎢  0   0  1  0 ⎥
⎣  0   0  0  1 ⎦
```

**Shear Y by Z** (y moves as z increases):
```
⎡ 1   0   0  0 ⎤
⎢ 0   1  shz  0 ⎥
⎢ 0   0   1  0 ⎥
⎣ 0   0   0  1 ⎦
```

**Shear Z by X** (z moves as x increases):
```
⎡  1   0  0  0 ⎤
⎢  0   1  0  0 ⎥
⎢ shx  0  1  0 ⎥
⎣  0   0  0  1 ⎦
```

**Shear Z by Y** (z moves as y increases):
```
⎡ 1   0   0  0 ⎤
⎢ 0   1   0  0 ⎥
⎢ 0  shy   1  0 ⎥
⎣ 0   0   0  1 ⎦
```

**Shear X by Y and Z** (x moves as both y and z increase):
```
⎡ 1  shy  shz  0 ⎤
⎢ 0   1    0   0 ⎥
⎢ 0   0    1   0 ⎥
⎣ 0   0    0   1 ⎦
```

**Shear Y by X and Z** (y moves as both x and z increase):
```
⎡  1   0   0  0 ⎤
⎢ shx  1  shz  0 ⎥
⎢  0   0   1  0 ⎥
⎣  0   0   0  1 ⎦
```

**Shear Z by X and Y** (z moves as both x and y increase):
```
⎡  1   0   0  0 ⎤
⎢  0   1   0  0 ⎥
⎢ shx shy  1  0 ⎥
⎣  0   0   0  1 ⎦
```

Multiple shear values can be combined in one matrix by filling in several off-diagonal entries simultaneously.

## OpenGL: Core Concepts

**Buffer object:** chunk of GPU memory holding an array (positions, colours, normals, indices). Uploaded once with `glBufferData`, read every frame by the GPU.

**Attribute location:** integer slot index (0, 1, 2...) wiring a buffer to a shader input. Must match `layout(location = N)` in the vertex shader.

**VAO (Vertex Array Object):** records which buffers are bound to which attribute slots. Bind once in setup; one `glBindVertexArray` call restores all bindings at draw time.

**Index buffer:** array of `uvec3` face indices telling the GPU which vertices form each triangle. Avoids duplicating vertex data.

## OpenGL: Setup Pattern

```cpp
// 1. Generate and bind VAO
glGenVertexArrays(1, &vaoID);
glBindVertexArray(vaoID);

// 2. Upload buffer, wire to slot
glGenBuffers(1, &bufID);
glBindBuffer(GL_ARRAY_BUFFER, bufID);
glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
glEnableVertexAttribArray(location);

// 3. Unbind
glBindVertexArray(0);
```

## OpenGL: Draw Pattern

```cpp
glBindVertexArray(vaoID);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
```

## GLFW

```cpp
glfwGetTime()    // seconds since app start (double), use for animation
```

## Animation Patterns

**Continuous rotation:**
```cpp
float t = glfwGetTime();
shape.setRotation(t, glm::vec3(0, 1, 0));   // angle grows with time
```

**Pulsing scale (stays positive):**
```cpp
float s = 1.0f + 0.5f * std::sin(t);
shape.setScaling(glm::vec3(s, s, s));
```

**Orbit around origin:**
```cpp
glm::mat4 orbit = glm::rotate(glm::mat4(1.0f), t, glm::vec3(0, 1, 0));
glm::vec3 newPos = glm::vec3(orbit * glm::vec4(initialPosition, 1.0f));
shape.setPosition(newPos);
```

**N objects evenly distributed in a circle:**
```cpp
for(int i = 0; i < N; i++) {
    float angle = (2.0f * M_PI / N) * i;
    glm::vec3 pos = glm::vec3(radius * cos(angle), 0, radius * sin(angle));
}
```

## Shader Uniforms: Sending Data from CPU

```cpp
// mat4
glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);

// mat3
glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);

// int / bool
glProgramUniform1i(program, location, value);

// get location
program->getUniformLocation("name");
```

## MultiLine: Drawing Normal Vectors

`MultiLine` is a `Shape` subclass that renders line segments using `GL_LINES` instead of `GL_TRIANGLES`. Used to visualise normals.

`GL_LINES` pairs vertices: vertex 0+1 form line 1, vertex 2+3 form line 2, etc. For each normal, push two vertices: the base point and the tip.

**Constructor, build the line segments:**
```cpp
MultiLine::MultiLine(const std::vector<glm::vec3> & vertices,
                     const std::vector<glm::vec3> & normals)
{
    float scale = 0.1f;
    for(size_t i = 0; i < vertices.size(); i++)
    {
        positions.push_back(vertices[i]);
        positions.push_back(vertices[i] + normals[i] * scale);

        colors.push_back(glm::vec3(1, 1, 0));
        colors.push_back(glm::vec3(1, 1, 0));

        uint32_t base = 2 * i;
        faces.push_back(glm::uvec3(base, base + 1, base + 1));
    }
}
```

**`draw()`, use `GL_LINES`:**
```cpp
void MultiLine::draw() const
{
    glBindVertexArray(vaoID);
    glDrawArrays(GL_LINES, 0, positions.size());
    glBindVertexArray(0);
}
```

**Usage:**
```cpp
MultiLine normalsViz(mesh.positions, mesh.normals);
normalsViz.createVertexArray(0, 1, 2);

// each frame
normalsViz.draw();
```

**Normal visualisation lines must follow the geometry.**
The `MultiLine` is a separate object from the mesh. It does not automatically inherit the mesh's transform. You must send it the same MVP matrix as the mesh it belongs to, otherwise the lines stay at the origin while the mesh moves.

```cpp
// after drawing the mesh with mvpMatrix already computed:
programForNormals->bind();
glUniformMatrix4fv(programForNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
normalsViz.draw();
programForNormals->unbind();
```

If the mesh has multiple instances (e.g. 4 toruses), draw the normals inside the same loop, reusing the same `mvpMatrix` computed for that instance.

## Normal Matrix: When and Why

Without it: normals are transformed by the model matrix, which breaks under non-uniform scaling (normals no longer perpendicular to surface).

With it: normals are transformed by the inverse transpose of the upper-left 3x3 of the model matrix, correct regardless of scaling.

**Compute and send from CPU:**
```cpp
glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
glUniformMatrix3fv(program->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
```

**Apply in vertex shader:**
```glsl
uniform mat3 normalMatrix;
uniform bool useNormalMatrix;

vec3 transformedNormal = useNormalMatrix
    ? normalize(normalMatrix * vNormal)
    : normalize(vNormal);
```

## normalsAsColor: Colouring by Normal Direction

Maps the normal vector directly to RGB. Since normals range from -1 to 1, remap to 0-1 for colour display.

**In vertex shader:**
```glsl
uniform bool normalsAsColor;

vec3 n = normalize(normalMatrix * vNormal);

objectColor = normalsAsColor
    ? n * 0.5 + 0.5   // remap [-1,1] -> [0,1]
    : vColor;
```

The `* 0.5 + 0.5` remapping is standard. Without it, negative normal components clamp to black and lose information.

## MVP Matrix

The full transform chain sent to the vertex shader:

```cpp
mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
```

| Matrix | Purpose |
|--------|---------|
| Model | object space -> world space (position, rotation, scale of the object) |
| View | world space -> camera space (where the camera is and where it looks) |
| Projection | camera space -> clip space (perspective / field of view) |

After projection: GPU divides by w (perspective divide) -> NDC -> screen pixels.

## Coordinate Spaces

```
object space
    x modelMatrix
world space
    x viewMatrix
camera/view space
    x projectionMatrix
clip space
    / w  (perspective divide, done by GPU)
NDC (normalised device coordinates, -1 to 1)
    viewport transform (done by GPU)
screen space (pixels)
```

## Shaders

**Vertex shader:** runs once per vertex. Minimum job: output `gl_Position = mvpMatrix * vec4(position, 1.0)`.

**Fragment shader:** runs once per pixel fragment. Outputs the final colour.

**Uniform:** variable set from CPU, constant across all vertices/fragments in one draw call:

```glsl
// in shader
uniform mat4 mvpMatrix;
uniform int useNormalMatrix;
```

```cpp
// from CPU
glUniformMatrix4fv(location, 1, GL_FALSE, &mvpMatrix[0][0]);
glProgramUniform1i(program, location, value);
```

## Normals

- Vectors perpendicular to a surface, used for lighting.
- Stored per vertex, interpolated across the triangle in the fragment shader.
- Must be re-transformed when the model matrix changes; use the normal matrix, not the model matrix directly.
- Visualised by rendering line segments from each vertex in the normal direction (see `MultiLine`).

## Face Culling and Depth Test

**Winding order:** vertices listed counter-clockwise (CCW) when viewed from outside define the front face. The GPU uses this to discard back faces.

```cpp
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
```

**Depth test:** ensures closer fragments overwrite farther ones. Without it, draw order determines visibility.

```cpp
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear both each frame
```
