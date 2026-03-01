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
	
	float pi = M_PI;

	for (int i = 0; i<numSegments; i++) {
		float theta = 2*pi*i/numSegments;
		for (int j = 0; j<numTubeSegments; j++) {
			float phi = 2*pi*j/numTubeSegments;
			float thetaWarp = theta + twistFactor * sin(phi);
			
			// computing torus vertex position for i,j
			float x = (R + r * cos(phi)) * cos(thetaWarp);
			float y = (R + r * cos(phi)) * sin(thetaWarp);
			float z = r * sin(phi);
			// push coords to positions
			positions.push_back({x, y, z});

			// store normal (direction from tube centre to vertex, normalised)
			glm::vec3 n = glm::normalize(glm::vec3(x, y, z) - glm::vec3(R * cos(thetaWarp), R * sin(thetaWarp), 0));
			normals.push_back(n);

			// store colour
			glm::vec3 colour = { abs(cos(thetaWarp)), abs(sin(phi)), 0.5f };
			colors.push_back(colour);

			// triangle face construction
			// make 2 triangles from each grid square; modulo (%) wraps last row/column back to 0
			int a = i * numTubeSegments + j;
  			int b = ((i + 1) % numSegments) * numTubeSegments + j;
  			int c = i * numTubeSegments + ((j + 1) % numTubeSegments);
  			int d = ((i + 1) % numSegments) * numTubeSegments + ((j + 1) % numTubeSegments);
  			faces.push_back({a, b, c});
  			faces.push_back({c, b, d});

		}
	}

        // Also store normals and a colour. Example colour:
        // glm::vec3 colour = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
        
        // **TODO**: Build triangle faces
        // Each cell has two triangles:
        //   (i, j), (i+1, j), (i, j+1)
        //   (i, j+1), (i+1, j), (i+1, j+1)
    }

    void Torus::applyOffset()
    {
        // **TODO**: For each vertex, add: positions[i] += offset * normals[i];
	for (int i = 0; i < positions.size(); i++) {
		positions[i] += offset * normals[i];
	}
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
