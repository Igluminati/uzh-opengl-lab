#include "GLExample.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title): GLApp(_windowSize, _title, false) {}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
					glm::vec3(5, 5, -5),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
					);

		programForLightBox = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");
        programForShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Shape");
        programForNormal = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");

		// create box for light position
		lightbox = std::make_shared<Cube>();
		if(!lightbox->createVertexArray(0, 1, 2))
			return false;

		lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
		lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));

		// Init models

        // create textured cube
		cube = std::make_shared<Cube>();
		if(!cube->createVertexArray(0, 1, 2))
			return false;

        cube->setPosition(glm::vec3(-1.5, 0.5, 3.5));
        cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

        // create torus
		torus = std::make_shared<Torus>();
		if(!torus->createVertexArray(0, 1, 2))
			return false;

		torus->setPosition(glm::vec3(3.0, 0.0, 1));
		torus->setScaling(glm::vec3(1.5, 1.5, 1.5));

        // create torus knot
        torusKnot = std::make_shared<TorusKnot>();
        if(!torusKnot->createVertexArray(0, 1, 2))
            return false;
        torusKnot->setRotation(90.0, glm::vec3(1.0, 0.0, 0.0));
        torusKnot->setPosition(glm::vec3(-1.0, -1, -3.0));
        torusKnot->setScaling(glm::vec3(2.0, 2.0, 2.0));

		// Init multiline field for normals of objects
        normalsTorus = std::make_shared<MultiLine>(torus->positions,
                                                   torus->normals);
        if(!normalsTorus->createVertexArray(0, 1, 2))
            return false;

		normalsTorusKnot = std::make_shared<MultiLine>(torusKnot->positions,
                                                   torusKnot->normals);
		if(!normalsTorusKnot->createVertexArray(0, 1, 2))
			return false;

		normalsCube = std::make_shared<MultiLine>(cube->positions,
                                                   cube->normals);
		if(!normalsCube->createVertexArray(0, 1, 2))
			return false;

		return true;
	}

	bool GLExample::update()
	{
        if (stopAnimation)
            return true;

		torusKnot->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if(animation > 4.0) {
                animationDir = Backward;
            } else {
                animation += 0.01;
            }
		}
		else
		{
			if(animation < -5.0) {
                animationDir = Forward;
            } else {
                animation -= 0.01;
            }
		}

		lightbox->setPosition(glm::vec3(animation, 1.5, -0.0));

		// Animate spotlight direction (circular motion)
		spotlightAngle += 0.02f;

		return true;
	}

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);

		// Clear the color and depth buffers
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		update();

		renderLightBox();

        addLightVariables(programForShape);

        if (drawCube) renderCube();
        if (drawTorus) renderTorus();
        if (drawTorusKnot) renderTorusKnot();

		return true;
	}

    /* TODO update this function to set the light information for the
	 * shaders. Don't forget that shader have to be bound before shader uniform can be set..
	 */
	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram> & program)
	{
        program->bind();
      
        // light properties
        glm::vec3 lightPos = lightbox->getPosition();
        glUniform3fv(program->getUniformLocation("lightPos"), 1, &lightPos[0]);
        glUniform3fv(program->getUniformLocation("lightColor"), 1, &lightColor[0]);
        
        // position of camera for specular
        glm::vec3 viewPos = cam.getPosition();
        glUniform3fv(program->getUniformLocation("viewPos"), 1, &viewPos[0]);
        
        // lighting component toggles
        glUniform1i(program->getUniformLocation("showAmbient"), showAmbient);
        glUniform1i(program->getUniformLocation("showDiffuse"), showDiffuse);
        glUniform1i(program->getUniformLocation("showSpecular"), showSpecular);
        
        // spotlight uniforms
        glUniform1i(program->getUniformLocation("useSpotlight"), bonusTask);
        
        // spotlight direction - animated to sweep across scene
        glm::vec3 spotDir = glm::normalize(glm::vec3(sin(spotlightAngle), -0.5f, cos(spotlightAngle)));
        glUniform3fv(program->getUniformLocation("spotlightDir"), 1, &spotDir[0]);
        
        // cutoff angles (in cosine space for efficiency)
        float cutOff = glm::cos(glm::radians(15.0f));       // inner cone
        float outerCutOff = glm::cos(glm::radians(25.0f));  // outer cone (soft edge)
        glUniform1f(program->getUniformLocation("spotlightCutOff"), cutOff);
        glUniform1f(program->getUniformLocation("spotlightOuterCutOff"), outerCutOff);
	}
    // END TODO

    void GLExample::renderCube() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        cube->draw();
        programForShape->unbind();

        if(drawCubeNormals) {
            programForNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
            glUniformMatrix4fv(programForNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsCube->draw();
            programForNormal->unbind();
        }
    }

    void GLExample::renderTorus() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        torus->draw();
        programForShape->unbind();

        if(drawTorusNormals) {
            programForNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
            glUniformMatrix4fv(programForNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorus->draw();
            programForNormal->unbind();
        }
    }

    void GLExample::renderTorusKnot() {
        programForShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * torusKnot->getModelMatrix();
        glUniformMatrix4fv(programForShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torusKnot->getModelMatrix()[0][0]);
        glUniform1i(programForShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        torusKnot->draw();
        programForShape->unbind();

        if(drawTorusKnotNormals) {
            programForNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * torusKnot->getModelMatrix();
            glUniformMatrix4fv(programForNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorusKnot->draw();
            programForNormal->unbind();
        }
    }

	void GLExample::renderLightBox()
	{
		programForLightBox->bind();
		mvpMatrix = cam.getViewProjectionMatrix() * lightbox->getModelMatrix();
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1, &lightColor[0]);
		glUniformMatrix4fv(programForLightBox->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		lightbox->draw();
		programForLightBox->unbind();
	}

	bool GLExample::end()
	{
		programForShape->deleteShaderProgramFromGPU();
		programForNormal->deleteShaderProgramFromGPU();
        programForLightBox->deleteShaderProgramFromGPU();
        return true;
	}

    void GLExample::imgui()
    {
        bool open = true;
        ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

        // GUI TOGGLES
        ImGui::ColorEdit3("Light Color", lightColor);
        ImGui::Checkbox("Pause Animation", &stopAnimation);
        ImGui::Separator();
        ImGui::RadioButton("Gouraud Shading", &renderMode, GOURAUD_SHADING);
        ImGui::RadioButton("Phong Shading", &renderMode, PHONG_SHADING);
        ImGui::Separator();
        ImGui::Checkbox("Render Cube", &drawCube);
        ImGui::Checkbox("Render Torus", &drawTorus);
        ImGui::Checkbox("Render Torus Knot", &drawTorusKnot);
        ImGui::Separator();
        ImGui::Checkbox("Render Cube Normals", &drawCubeNormals);
        ImGui::Checkbox("Render Torus Normals", &drawTorusNormals);
        ImGui::Checkbox("Render Torus Knot Normals", &drawTorusKnotNormals);
        ImGui::Separator();
        ImGui::Text("Lighting Components:");
        ImGui::Checkbox("Ambient", &showAmbient);
        ImGui::Checkbox("Diffuse", &showDiffuse);
        ImGui::Checkbox("Specular", &showSpecular);
        ImGui::Separator();
        ImGui::Checkbox("Bonus Task", &bonusTask);
        ImGui::End();
    }
}

