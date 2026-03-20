#include "MultiLine.h"

#include <iostream>
#include <cmath>

namespace cgCourse
{
	MultiLine::MultiLine(const std::vector<glm::vec3> & vertices,
						 const std::vector<glm::vec3> & normals
						 ) : Shape()
	{
		// initialises positions, colors, and normals
		for(size_t i = 0; i < vertices.size(); i++) {

			// appends two positions of a line from start to end
			positions.push_back(vertices[i]);
			positions.push_back(vertices[i] + normals[i] * 0.2f);

			// appends colour of both endpoints
			colors.push_back(glm::vec3(1,1,1));
			colors.push_back(glm::vec3(1,1,1));
		}
	}

	void MultiLine::draw() const
	{
		// draws the normals as lines
		glBindVertexArray(vaoID);
		glDrawArrays(GL_LINES, 0, positions.size());
		glBindVertexArray(0);
	}
}

