#include "GLExercise.h"

#include "Cube.h"

#include <iostream>

namespace cgCourse
{
	GLExercise::GLExercise(const glm::uvec2 & windowSize, const std::string & title): GLApp(windowSize, title, false)
	{
		normalsTorus = MultiLine(torus.positions, torus.normals);
	}

	bool GLExercise::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
					glm::vec3(3, 3, -3),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
					);

		programForShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Shape");
		programForTorusNormals = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");
		programForUnitCube = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/UnitCube");

		// Init models VAO
		if(!cube.createVertexArray(0, 1, 2))
			return false;

		if(!torus.createVertexArray(0, 1, 2))
			return false;

		// TODO: setup some initial transformation for the cube and toruses, use the implemented methods from Shape.
		// the initial state of the exercise only create one torus, you need to do modifications maybe in Shape.h to create the 4 torus.
		torusModelMats.push_back(glm::mat4(1));

		// Init multiline field for normals of objects
		if(!normalsTorus.createVertexArray(0, 1, 2))
			return false;

		if (!unitCube.createVertexArray(0, 1, 2)) 
			return false;

		return true;
	}

	bool GLExercise::update()
	{
		if(!animation) return true;

		// TODO: implement the animation of the cube and toruses

		return true;
	}

	bool GLExercise::render()
	{
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		update();

		glProgramUniform1i(*programForTorusNormals, programForTorusNormals->getUniformLocation("useNormalMatrix"), useNormalMatrix);
		glProgramUniform1i(*programForShape, programForShape->getUniformLocation("useNormalMatrix"), useNormalMatrix);
		glProgramUniform1i(*programForShape, programForShape->getUniformLocation("normalsAsColor"), normalsAsColor);

		renderCubes();
		renderTorus();
		if (drawUnitCube)
			renderUnitCube();

		return true;
	}

	void GLExercise::renderCubes()
	{
		programForShape->bind();

		mvpMatrix = cam.getViewProjectionMatrix() * cube.modelMatrix;
		// normalMatrix = TODO: compute the normal matrix
		glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		glUniformMatrix3fv(programForShape->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
		cube.draw();

		programForShape->unbind();
	}

	void GLExercise::renderUnitCube()
	{
		programForUnitCube->bind();
		mvpMatrix = cam.getViewProjectionMatrix() * unitCube.modelMatrix;
		glUniformMatrix4fv(programForUnitCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		unitCube.draw();
		programForUnitCube->unbind();
	}

	void GLExercise::renderTorus()
	{
		programForShape->bind();

		for(auto & modelMat: torusModelMats)
		{
			mvpMatrix = cam.getViewProjectionMatrix() * modelMat;
			// normalMatrix = TODO: compute the normal matrix
			glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
			glUniformMatrix3fv(programForShape->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
			torus.draw();
		}

		programForShape->unbind();


		if(!drawTorusNormals) return;

		// TODO: draw the torus normals using the multiline object
	}

	bool GLExercise::end()
	{
		return true;
	}

	void GLExercise::imgui()
	{
		ImGui::SetNextWindowSize(ImVec2(200, -1));
		ImGui::Begin("status", nullptr, ImGuiWindowFlags_NoTitleBar);
		ImGui::Checkbox("drawTorusNormals", &drawTorusNormals);
		ImGui::Checkbox("drawUnitCube", &drawUnitCube);
		ImGui::Checkbox("useNormalMatrix", &useNormalMatrix);
		ImGui::Checkbox("normalsAsColor", &normalsAsColor);
		ImGui::Checkbox("animation", &animation);
		ImGui::End();
	}
}

