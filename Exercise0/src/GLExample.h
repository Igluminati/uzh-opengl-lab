#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "GLApp.h"
#include "Model.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>
//#include <cmath>

namespace cgCourse
{
	class GLExample : public GLApp
	{
	public:
		enum MotionMode
		{
			NoMotionMode = 0, RotateMode = 1, TranslateMode = 2, ZoomMode = 3
		};

		GLExample(glm::uvec2 _windowSize, std::string _title);

		virtual bool init() override;
		virtual bool render() override;
		virtual bool end() override;

	private:
		bool loadAndCompileShaderToGPU(GLuint _program, const std::string & _source);
		void computeMvpMatrix();
		bool checkLinkStatusOfProgram(GLuint _program);

		GLuint program = 0;
		GLuint mvpUniformLocation = 0;
		glm::mat4 mvpMatrix;
		std::shared_ptr<Model> cube = nullptr;
	};
}

#endif // GLEXAMPLE_H
