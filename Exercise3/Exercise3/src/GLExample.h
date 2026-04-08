#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "GLApp.h"
#include "Cube.h"
#include "Torus.h"
#include "TorusKnot.h"
#include "ShaderProgram.h"
#include "MultiLine.h"
#include "Camera.h"

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
        void renderCube();
        void renderTorus();
        void renderTorusKnot();

		std::shared_ptr<ShaderProgram> programForLightBox;
		std::shared_ptr<ShaderProgram> programForShape;
        std::shared_ptr<ShaderProgram> programForNormal;

        std::shared_ptr<Cube> cube;
		std::shared_ptr<Cube> lightbox;
		std::shared_ptr<Torus> torus;
		std::shared_ptr<TorusKnot> torusKnot;
		std::shared_ptr<MultiLine> normalsCube;
		std::shared_ptr<MultiLine> normalsTorus;
		std::shared_ptr<MultiLine> normalsTorusKnot;

        const int GOURAUD_SHADING = 0;
        const int PHONG_SHADING = 1;

		float animation = 0;
		LightMotionMode animationDir = Forward;

		glm::mat4 mvpMatrix = glm::mat4(1);

		Camera cam;
		bool drawCube = true;
		bool drawTorus = true;
        bool stopAnimation = false;
        bool drawTorusKnot = true;
		bool drawCubeNormals = false;
		bool drawTorusNormals = false;
		bool drawTorusKnotNormals = false;
        bool bonusTask = false;
        float lightColor[3] = {1.0,1.0,1.0};
        int renderMode = GOURAUD_SHADING;
        
        bool showAmbient = true;
        bool showDiffuse = true;
        bool showSpecular = true;
        
        float spotlightAngle = 0.0f;
    };
}

#endif // GLEXAMPLE_H

