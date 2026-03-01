#include "Torus.h"
#include <math.h>       // for M_PI
#include <glm/glm.hpp>  // for glm::vec3, etc.
#include <glm/gtc/constants.hpp>

namespace cgCourse
{
    Torus::Torus(float majorRadius, float minorRadius,
                 int majorSeg, int minorSeg,
                 float off,
                 float twist)
        : R(majorRadius),
          r(minorRadius),
          numSegments(majorSeg),
          numTubeSegments(minorSeg),
          offset(off),
          twistFactor(twist)
    {
        // 1) Generate torus geometry
        generateMesh();

        // 2) Offset vertices along normal
        applyOffset();
    }

    void Torus::generateMesh()
    {
        // Clear old data
        positions.clear();
        normals.clear();
        colors.clear();
        faces.clear();

        // **TODO**: Implement parametric torus with a warp
        // Use angles: theta in [0..2π), phi in [0..2π).
        // Example of warping:
        // float thetaWarp = theta + twistFactor * sin(phi);

        // Loop over i in [0..numSegments)
        //   float theta = ...
        // Loop over j in [0..numTubeSegments)
        //   float phi = ...
        // Then compute (x, y, z)

        // Also store normals and a color. Example color:
        // glm::vec3 color = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
        
        // **TODO**: Build triangle faces
        // Each cell has two triangles:
        //   (i, j), (i+1, j), (i, j+1)
        //   (i, j+1), (i+1, j), (i+1, j+1)
    }

    void Torus::applyOffset()
    {
        // **TODO**: For each vertex, add: positions[i] += offset * normals[i];
    }

    void Torus::draw()
    {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

        // Each face is a uvec3 => 3 indices per face
        glDrawElements(GL_TRIANGLES,
                       GLsizei(faces.size() * 3),
                       GL_UNSIGNED_INT,
                       nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
