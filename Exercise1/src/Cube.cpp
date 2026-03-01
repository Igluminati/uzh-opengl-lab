#include "Cube.h"

namespace cgCourse
{
	Cube::Cube() : Shape()
	{
		// set geometry with respect to local origin
		positions = {
			{ -1.0f, -1.0f, -1.0f },	// index 0
			{ -1.0f, -1.0f, 1.0f },
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, 1.0f, -1.0f },

			{ 1.0f, 1.0f, 1.0f },		// index 4
			{ 1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },

			{ -1.0f, -1.0f, -1.0f },	// index 8
			{ 1.0f, -1.0f, -1.0f },
			{ 1.0f, -1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },

			{ 1.0f, 1.0f, 1.0f },		// index 12
			{ 1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, -1.0f },
			{ -1.0f, 1.0f, 1.0f },

			{ -1.0f, -1.0f, -1.0f },	// index 16
			{ -1.0f, 1.0f, -1.0f },
			{ 1.0f, 1.0f, -1.0f },
			{ 1.0f, -1.0f, -1.0f },

			{ 1.0f, 1.0f, 1.0f },		// index 20
			{ -1.0f, 1.0f, 1.0f },
			{ -1.0f, -1.0f, 1.0f },
			{ 1.0f, -1.0f, 1.0f }
		};

		colors = {
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },
			{ 0.8f, 0.8f, 0.0f },

			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },
			{ 0.8f, 0.0f, 0.0f },

			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },
			{ 0.0f, 0.8f, 0.0f },

			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },
			{ 0.0f, 0.0f, 0.8f },

			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },
			{ 0.0f, 0.8f, 0.8f },

			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f },
			{ 0.8f, 0.0f, 0.8f }
		};

		normals = {
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },
			{ -1.0f, 0.0f, 0.0f },

			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f },

			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f },

			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },

			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, -1.0f },

			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f },
			{ 0.0f, 0.0f, 1.0f }
		};

		faces = {
			{ 0, 1, 2 }, { 2, 3, 0 },
			{ 4, 5, 6 }, { 6, 7, 4 },
			{ 8, 9, 10 }, { 10, 11, 8 },
			{ 12, 13, 14 }, { 14, 15, 12 },
			{ 16, 17, 18 }, { 18, 19, 16 },
			{ 20, 21, 22 }, { 22, 23, 20 }
		};

		faceNormals = {
			{ -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
			{ 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f },
			{ 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }
		};
	}

	void Cube::draw()
	{
		// bind the Vertex Array Object of the cube and draw the triangles
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
		glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

