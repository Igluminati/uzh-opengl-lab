#include "UnitCube.h"

#include <iostream>
#include <cmath>

namespace cgCourse
{
	UnitCube::UnitCube() : Shape()
	{
                positions.push_back({0.0, 0.0, 0.0});
                positions.push_back({10.0, 0.0, 0.0});
                colors.push_back({1, 0, 0});
                colors.push_back({1, 0, 0});
                normals.push_back({1.0, 0.0, 0.0});
                normals.push_back({1.0, 0.0, 0.0});
                positions.push_back({0.0, 0.0, 0.0});
                positions.push_back({0.0, 10.0, 0.0});
                colors.push_back({0, 1, 0});
                colors.push_back({0, 1, 0});
                normals.push_back({0.0, 1.0, 0.0});
                normals.push_back({0.0, 1.0, 0.0});
                positions.push_back({0.0, 0.0, 0.0});
                positions.push_back({0.0, 0.0, 10.0});
                colors.push_back({0, 0, 1});
                colors.push_back({0, 0, 1});
                normals.push_back({0.0, 0.0, 1.0});
                normals.push_back({0.0, 0.0, 1.0});

	}

	void UnitCube::draw() const
	{
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, posBufferID);
		glDrawArrays(GL_LINES, 0, positions.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

