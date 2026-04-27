#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "GLApp.h"
#include "Cube.h"
#include "Torus.h"
#include "ShaderProgram.h"
#include "MultiLine.h"
#include "Camera.h"
#include "Texture.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>
#include <memory>

namespace cgCourse
{
	class GLExample : public GLApp
	{
	public:
		enum LightMotionMode
		{
			Forward = 0, Backward = 1
		};

		GLExample(glm::uvec2 _windowSize, std::string _title);

		bool init() override;
		bool update() override;
		bool render() override;
		bool end() override;

    protected:
        void imgui() override;

    private:
		void addLightVariables(const std::shared_ptr<ShaderProgram>& _program);
		void renderLightBox();
		void renderTexturedCube();
		void renderTexturedTorus();
        void renderBasicCube();
        void renderBasicTorus();

        std::shared_ptr<ShaderProgram> programForTexturedShape;
		std::shared_ptr<ShaderProgram> programForTexturedNormals;
		std::shared_ptr<ShaderProgram> programForLightBox;
		std::shared_ptr<ShaderProgram> programForBasicShape;
        std::shared_ptr<ShaderProgram> programForBasicNormal;

        std::shared_ptr<Cube> cube;
		std::shared_ptr<Cube> lightbox;
		std::shared_ptr<Torus> torus;
		std::shared_ptr<MultiLine> normalsTorus;

		std::shared_ptr<Texture> cubetex;
		std::shared_ptr<Texture> cubetexSpec;
        std::shared_ptr<Texture> cubetexNormal;
		std::shared_ptr<Texture> torustex;
		std::shared_ptr<Texture> torustexSpec;
        std::shared_ptr<Texture> torustexNormal;

        // Bonus Task
        std::shared_ptr<Texture> bonustex;
		std::shared_ptr<Texture> bonustexSpec;
        std::shared_ptr<Texture> bonustexNormal;
        // End Bonus Task

        const int GOURAUD_SHADING = 0;
        const int PHONG_SHADING = 1;
        const int TEXTURED_SHADING = 2;
        const int BONUS_SHADING =3;

		float animation = 0;
		LightMotionMode animationDir = Forward;

		glm::mat4 mvpMatrix = glm::mat4(1);

		Camera cam;
		bool drawTorusNormals = false;
		bool stopAnimation = false;
        float lightColor[3] = {1.0,1.0,1.0};
        int renderMode = GOURAUD_SHADING;
    };
}

#endif // GLEXAMPLE_H

