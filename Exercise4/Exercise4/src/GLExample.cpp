#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title): GLApp(_windowSize, _title, false) {}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
					glm::vec3(3, 3, -3),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
					);

        programForTexturedShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/TexturedShape");
        programForTexturedNormals = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/TexturedNormals");
		programForLightBox = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");
        programForBasicShape = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/BasicShape");
        programForBasicNormal = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/BasicNormals");

		// create box for light position
		lightbox = std::make_shared<Cube>();
		if(!lightbox->createVertexArray(0, 1, 2, 3, 4))
			return false;

		lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
		lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));

		// Init models

        // create textured cube
		cube = std::make_shared<Cube>();
		if(!cube->createVertexArray(0, 1, 2, 3, 4))
			return false;

        cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
        cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

        // create torus
		torus = std::make_shared<Torus>();
		if(!torus->createVertexArray(0, 1, 2, 3, 4))
			return false;

		torus->setPosition(glm::vec3(1.5, 0.0, 0.0));

		// Init multiline field for normals of objects
		normalsTorus = std::make_shared<MultiLine>(torus->positions,
                                                   torus->normals,
                                                   torus->tangents,
                                                   torus->texCoords
													);
		if(!normalsTorus->createVertexArray(0, 1, 2, 3, 4))
			return false;


        /* TODO: load the following textures here:
		 *       - cubetex - the diffuse texture
		 *       - cubetexSpec - the specular map
		 *       - cubetexNormal - the normal map
		 *       - torustex - the diffuse texture for the torus
		 *       - torustexSpec - the specular map for the torus
		 *       - torustexSpec - the specular map for the torus
		 *       - torustexNormal - the normal map for the torus
		 *      The easist thing will be if you start with the diffuse
		 *      texture for the cube. Don't forget to initialize the shared pointers existing
		 *      already in this class for this purpose.
		 */
		cubetex = std::make_shared<Texture>();
		cubetex->loadFromFile(std::string(RES_DIR) + "/container.png");
        // ...

        // TODO END
		return true;
	}

	bool GLExample::update()
	{
		if (stopAnimation)
            return true;

		torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if(animation > 1.5)
				animationDir = Backward;
			else
				animation += 0.01;
		}
		else
		{
			if(animation < -4.0)
				animationDir = Forward;
			else
				animation -= 0.01;
		}

		lightbox->setPosition(glm::vec3(animation, 0.5, -0.5));

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

        addLightVariables(programForTexturedShape);
        addLightVariables(programForBasicShape);

        if (renderMode == GOURAUD_SHADING || renderMode == PHONG_SHADING) {
            renderBasicCube();
            renderBasicTorus();
        } else if (renderMode == TEXTURED_SHADING){
            renderTexturedCube();
            renderTexturedTorus();
        } else {
            // TODO: Bonus Task

            // END TODO
        }
		return true;
	}

	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram> & program)
	{
		program->bind();
		glUniform3fv(program->getUniformLocation("camPos"), 1, &cam.getPosition()[0]);
		glUniform3fv(program->getUniformLocation("light.position"), 1, &lightbox->getPosition()[0]);
		glUniform3fv(program->getUniformLocation("light.ambient"), 1, &lightColor[0]);
		glUniform3fv(program->getUniformLocation("light.diffuse"), 1, &lightColor[0]);
		glUniform3fv(program->getUniformLocation("light.specular"), 1, &lightColor[0]);
		program->unbind();
	}

    void GLExample::renderBasicCube() {
        programForBasicShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
        glUniformMatrix4fv(programForBasicShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForBasicShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
        glUniform1i(programForBasicShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        cube->draw();
        programForBasicShape->unbind();
    }

    void GLExample::renderBasicTorus() {
        programForBasicShape->bind();
        mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
        glUniformMatrix4fv(programForBasicShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        glUniformMatrix4fv(programForBasicShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
        glUniform1i(programForBasicShape->getUniformLocation("gouraudShading"), renderMode == GOURAUD_SHADING);
        torus->draw();
        programForBasicShape->unbind();

        if(drawTorusNormals) {
            programForBasicNormal->bind();
            mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
            glUniformMatrix4fv(programForBasicNormal->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorus->draw();
            programForBasicNormal->unbind();
        }
    }

	void GLExample::renderTexturedCube()
	{
		programForTexturedShape->bind();

        /* TODO: bind textures for shaders with glBindTexture and glActiveTexture.
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform
		 *       variable in the shader is meant to be which texture layer when
		 *       used with glActiveTexture.
		 */

        // End TODO

        mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
		glUniformMatrix4fv(programForTexturedShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTexturedShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		cube->draw();

        /* TODO: unbind textures by setting all glBindTextures for all active texture layers
		 *       to zero.
		 */

        // TODO END

		programForTexturedShape->unbind();
	}

	void GLExample::renderTexturedTorus()
	{
		programForTexturedShape->bind();

        /* TODO: bind textures for shaders with glBindTexture and glActiveTexture.
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform
		 *       variable in the shader is meant to be which texture layer when
		 *       used with glActiveTexture.
		 */

        // TODO END

		mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
		glUniformMatrix4fv(programForTexturedShape->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTexturedShape->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		torus->draw();

        /* TODO: unbind textures by setting all glBindTextures for all active texture layers
		*       to zero.
		*/

        // End TODO

		programForTexturedShape->unbind();


		if(drawTorusNormals) {
            programForTexturedNormals->bind();
            /* TODO: Activate and bind the normal texture*/

            // TODO END

            mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
            glUniformMatrix4fv(programForTexturedNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
            normalsTorus->draw();

            /* TODO: unbind normal texture by setting glBindTexture for the active texture layer
            *       to zero.
            */

            // TODO END

            programForTexturedNormals->unbind();
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
		programForTexturedShape->deleteShaderProgramFromGPU();
		programForTexturedNormals->deleteShaderProgramFromGPU();
		return true;
	}

    void GLExample::imgui()
    {
        // Create a window called "My First Tool", with a menu bar.
        bool open = true;
        ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

        // Light Color
        ImGui::ColorEdit3("Light Color", lightColor);
		ImGui::Checkbox("Pause Animation", &stopAnimation);
        ImGui::Separator();
        ImGui::RadioButton("Gouraud Shading", &renderMode, GOURAUD_SHADING);
        ImGui::RadioButton("Phong Shading", &renderMode, PHONG_SHADING);
        ImGui::RadioButton("Textured Shading", &renderMode, TEXTURED_SHADING);
        ImGui::RadioButton("Bonus Task", &renderMode, BONUS_SHADING);
        ImGui::Separator();
        ImGui::Checkbox("Render Torus Normals", &drawTorusNormals);
        ImGui::End();
    }
}

