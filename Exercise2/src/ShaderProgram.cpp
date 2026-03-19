#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <iostream>
#include <fstream>

namespace cgCourse
{
	ShaderProgram::ShaderProgram(const std::string & name)
	{
		program = 0;

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		loadAndCompileShaderToGPU(vertShader, loadFile(name + ".vert"));
		loadAndCompileShaderToGPU(fragShader, loadFile(name + ".frag"));

		program = glCreateProgram();
		assert(program);

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

		glLinkProgram(program);
		checkLinkStatusOfProgram(program);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}

	ShaderProgram::operator GLuint () const
	{
		return program;
	}

	std::string ShaderProgram::loadFile(const std::string & filename)
	{
		std::string result;
		std::ifstream stream(filename.c_str());

		if(!stream.is_open())
			return result;

		stream.seekg(0, std::ios::end);
		result.reserve(stream.tellg());
		stream.seekg(0, std::ios::beg);

		result.assign(	std::istreambuf_iterator<char>(stream),
						std::istreambuf_iterator<char>()
						);

		return result;
	}

	bool ShaderProgram::loadAndCompileShaderToGPU(GLuint program, const std::string & source)
	{
		GLint status;
		GLchar errorMessage[512];

		const char * shadersource = source.c_str();
		int shaderstringlength = source.length();

		glShaderSource(program, 1, (const GLchar **) &shadersource, &shaderstringlength);
		glCompileShader(program);
		glGetShaderiv(program, GL_COMPILE_STATUS, &status);

		if(!status)
		{
			glGetShaderInfoLog(program, 512, 0, errorMessage);
			std::cerr << "Fragment Shader compilation error:" << std::endl;
			std::cerr << errorMessage << std::endl;
			return false;
		}

		return true;
	}

	bool ShaderProgram::checkLinkStatusOfProgram(GLuint program)
	{
		GLint status;
		GLchar errorMessage[512];
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if(!status)
		{
			glGetProgramInfoLog(program, 512, 0, errorMessage);
			std::cerr << "Linking error:" << std::endl;
			std::cerr << errorMessage << std::endl;
			return false;
		}
		return true;
	}

	GLuint ShaderProgram::getUniformLocation(const std::string & uniformName)
	{
		return glGetUniformLocation(program, uniformName.c_str());
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(program);
	}

	void ShaderProgram::unbind() const
	{
		glUseProgram(0);
	}
}

