#include "GLExercise.h"

#include "Cube.h"

#include <iostream>
#include <cmath>

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

		// setup some initial transformation for the cube and toruses, use the implemented methods from Shape.
		/*
		glm::vec3 offsets[] = {
			glm::vec3( 2.0f, 0, 0),
			glm::vec3( -2.0f, 0, 0),
			glm::vec3( 0, 0, 2.0f),
			glm::vec3( 0, 0 ,-2.0f)
		};
		for(glm::vec3 & offset : offsets) {
			Torus t;
			t.setPosition(offset);
			t.calculateModelMatrix();
			toruses.push_back(t);
			torusModelMats.push_back(toruses.back().modelMatrix);
			toruses.back().createVertexArray(0, 1, 2);
			torusInitialPositions.push_back(offset);
		}
		*/
		float radius = 2.0f;
		for(int i = 0; i < numberOfTorus; i++)
		{
			float angle = (2.0f * M_PI / numberOfTorus) * i;
			glm::vec3 offset = glm::vec3(radius * cos(angle), 0, radius * sin(angle));

			Torus t;
			t.setPosition(offset);
			t.calculateModelMatrix();
			toruses.push_back(t);
			torusModelMats.push_back(toruses.back().modelMatrix);
			toruses.back().createVertexArray(0, 1, 2);
			torusInitialPositions.push_back(offset);
		}

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

		// CUBE
		// as time goes on, increase the angle of rotation in the y-axis
		float t = glfwGetTime();
		cube.setRotation(t, glm::vec3(0,1,0));
		// pulsing animation (co-efficient ensures value isn't negative which causes cube to turn inside out and mess with the normals)
		float s = 0.6f + 0.25f * std::sin(t);
		cube.setScaling(glm::vec3(s, s, s));
		cube.calculateModelMatrix();

		// TORUSES
		for(size_t i = 0; i < toruses.size(); i++) {
			// returns torus position vector then normalises it to a unit vector of length 1 (e.g. (1,0,0))
			glm::vec3 axis = glm::normalize(toruses[i].getPosition());
			glm::mat4 orbit = glm::rotate(glm::mat4(1.0f), t, glm::vec3(0, 1, 0));
			glm::vec3 newPos = glm::vec3(orbit * glm::vec4(torusInitialPositions[i], 1.0f));

			toruses[i].setRotation(t, axis);
			toruses[i].setPosition(newPos);
			float s = 0.6f + 0.25f * std::sin(t);
			toruses[i].setScaling(glm::vec3(s, s, s));
			toruses[i].calculateModelMatrix();
			torusModelMats[i] = toruses[i].modelMatrix;
		}

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
		// normalMatrix = inverse and transpose of model matrix
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(cube.modelMatrix)));
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

		// iterates by index so we have both the torus object and its model matrix
		for(size_t i = 0; i < toruses.size(); i++)
		{
			mvpMatrix = cam.getViewProjectionMatrix() * torusModelMats[i];
			normalMatrix = glm::transpose(glm::inverse(glm::mat3(toruses[i].modelMatrix)));
			glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
			glUniformMatrix3fv(programForShape->getUniformLocation("normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
			toruses[i].draw();
		}

		programForShape->unbind();


		if(!drawTorusNormals) return;

		programForTorusNormals->bind();

		// draws the torus normals using the multiline object
		for(size_t i = 0; i < toruses.size(); i++)
		{
			mvpMatrix = cam.getViewProjectionMatrix() * torusModelMats[i];
			// normalMatrix = TODO: compute the normal matrix
			glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
			normalsTorus.draw();
		}
		programForTorusNormals->unbind();
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

