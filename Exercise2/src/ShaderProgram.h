#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GLIncludes.h"
#include <string>

namespace cgCourse
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string & name);
		~ShaderProgram();

		operator GLuint () const;

		void bind() const;
		void unbind() const;

		GLuint getUniformLocation(const std::string & uniformName);

	private:
		static bool loadAndCompileShaderToGPU(GLuint program, const std::string & source);
		static bool checkLinkStatusOfProgram(GLuint program);
		static std::string loadFile(const std::string & filename);

	private:
		GLuint program = 0;
	};
}

#endif // SHADERPROGRAM_H

