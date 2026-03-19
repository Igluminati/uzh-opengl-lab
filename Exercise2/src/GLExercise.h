#ifndef GLEXERCISE_H
#define GLEXERCISE_H

#include "GLApp.h"
#include "Cube.h"
#include "Torus.h"
#include "ShaderProgram.h"
#include "MultiLine.h"
#include "Camera.h"
#include "UnitCube.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>

namespace cgCourse
{
	class GLExercise : public GLApp
	{
	public:
		GLExercise(const glm::uvec2 & windowSize, const std::string & title);

		bool init() override;
		bool update() override;
		bool render() override;
		bool end() override;
		void imgui() override;

	private:
		void renderCubes();
		void renderTorus();
		void renderUnitCube();

		std::shared_ptr<ShaderProgram> programForShape;
		std::shared_ptr<ShaderProgram> programForTorusNormals;
		std::shared_ptr<ShaderProgram> programForUnitCube;

		Cube cube;
		Torus torus;
		MultiLine normalsTorus;
		UnitCube unitCube;

		std::vector<glm::mat4> torusModelMats;

		glm::mat4 mvpMatrix = glm::mat4(1);
		glm::mat3 normalMatrix = glm::mat3(1);

		Camera cam;
		bool drawTorusNormals = true;
		bool useNormalMatrix = true;
		bool normalsAsColor = true;
		bool animation = true;
		bool drawUnitCube = true;
	};
}

#endif // GLEXERCISE_H

