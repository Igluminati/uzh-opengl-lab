#include "Model.h"

#include <iostream>

namespace cgCourse
{
	// ---- Model ----
	const GLuint Model::InvalidAttribLoc = GLuint(-1);


	// ---- Cube ----
	namespace
	{
		namespace CubeData
		{
			static const float Vertices[] =
			{
				-1.0f, -1.0f, -1.0f,   // index 0
				-1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, -1.0f,

				1.0f, 1.0f, 1.0f,	  // index 4
				1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,   // index 8
				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f,

				1.0f, 1.0f, 1.0f,	  // index 12
				1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f,
				-1.0f, 1.0f, 1.0f,

				-1.0f, -1.0f, -1.0f,   // index 16
				-1.0f, 1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,

				1.0f, 1.0f, 1.0f,	  // index 20
				-1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f,
				1.0f, -1.0f, 1.0f
			};

			static const float Colors[] =
			{
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,
				0.8f, 0.8f, 0.0f,

				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,
				0.8f, 0.0f, 0.0f,

				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,
				0.0f, 0.8f, 0.0f,

				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,
				0.0f, 0.0f, 0.8f,

				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,
				0.0f, 0.8f, 0.8f,

				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f,
				0.8f, 0.0f, 0.8f
			};

			static const float Normals[] =
			{
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,
				-1.0f, 0.0f, 0.0f,

				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,

				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,
				0.0f, -1.0f, 0.0f,

				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,

				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, -1.0f,

				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f
			};

			static const GLuint Triangles[] =
			{
				0, 1, 2, 2, 3, 0,
				4, 5, 6, 6, 7, 4,
				8, 9, 10, 10, 11, 8,
				12, 13, 14, 14, 15, 12,
				16, 17, 18, 18, 19, 16,
				20, 21, 22, 22, 23, 20
			};
		} // namespace CubeData
	} // namespace


	Cube::~Cube()
	{
		glDeleteBuffers(1, &posBO_);
		glDeleteBuffers(1, &colBO_);
		glDeleteBuffers(1, &normBO_);
		glDeleteBuffers(1, &idxBO_);
		glDeleteVertexArrays(1, &modelVAO_);
	}

	bool Cube::createVertexArray(GLuint posAttribLoc, GLuint colAttribLoc, GLuint normAttribLoc)
	{
		// Initialize buffer objects with geometry data
		glGenBuffers(1, &posBO_);
		glBindBuffer(GL_ARRAY_BUFFER, posBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Vertices), CubeData::Vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &colBO_);
		glBindBuffer(GL_ARRAY_BUFFER, colBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Colors), CubeData::Colors, GL_STATIC_DRAW);

		glGenBuffers(1, &normBO_);
		glBindBuffer(GL_ARRAY_BUFFER, normBO_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeData::Normals), CubeData::Normals, GL_STATIC_DRAW);

		// Initialize buffer objects with index data
		glGenBuffers(1, &idxBO_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBO_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeData::Triangles), CubeData::Triangles, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		// initialize cube's vertex array object
		glGenVertexArrays(1, &modelVAO_);
		glBindVertexArray(modelVAO_);

		if(posAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, posBO_);
			glEnableVertexAttribArray(posAttribLoc);
			glVertexAttribPointer(posAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if(colAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, colBO_);
			glEnableVertexAttribArray(colAttribLoc);
			glVertexAttribPointer(colAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if(normAttribLoc != Model::InvalidAttribLoc)
		{
			glBindBuffer(GL_ARRAY_BUFFER, normBO_);
			glEnableVertexAttribArray(normAttribLoc);
			glVertexAttribPointer(normAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}

	void Cube::draw()
	{
		glBindVertexArray(modelVAO_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBO_);
		glDrawElements(GL_TRIANGLES, sizeof(CubeData::Triangles) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

