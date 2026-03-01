#ifndef SHAPE_H
#define SHAPE_H

#include "GLIncludes.h"
#include <vector>
#include <glm/mat4x4.hpp>

namespace cgCourse
{
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape();

		bool createVertexArray(GLuint posAttribLoc, GLuint colAttribLoc, GLuint normAttribLoc);

		virtual void draw() = 0;

		std::vector<glm::vec3> & getPositions();
		std::vector<glm::vec3> & getNormals();
		std::vector<glm::uvec3> & getFaces();
		std::vector<glm::vec3> & getFaceNormals();

		glm::mat4 getModelMatrix() const;

		void setShapePosition(glm::vec3);

	protected:
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec3> normals;
		std::vector<glm::uvec3> faces;
		std::vector<glm::vec3> faceNormals;

		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 modelMatrix = glm::mat4(1);

		GLuint vaoID = 0;
		GLuint posBufferID = 0;
		GLuint colorBufferID = 0;
		GLuint normalBufferID = 0;
		GLuint indexBufferID = 0;
	};
}

#endif //  SHAPE_H

