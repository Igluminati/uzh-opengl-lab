#ifndef MODELS_HPP_INCLUDED
#define MODELS_HPP_INCLUDED

#include "GLIncludes.h"

namespace cgCourse
{
	class Model
	{
	public:
		static const GLuint InvalidAttribLoc;

		Model() = default;
		virtual ~Model() = default;

		virtual bool createVertexArray( GLuint posAttribLoc,
										GLuint colAttribLoc,
										GLuint normAttribLoc) = 0;

		virtual void draw() = 0;
	};

	class Cube : public Model
	{
	public:
		Cube() = default;
		virtual ~Cube() override;

		virtual bool createVertexArray( GLuint posAttribLoc,
										GLuint colAttribLoc,
										GLuint normAttribLoc
										) override;

		virtual void draw() override;

	private:
		GLuint modelVAO_	= 0;
		GLuint posBO_		= 0;
		GLuint colBO_		= 0;
		GLuint normBO_		= 0;
		GLuint idxBO_		= 0;
	};
}

#endif // MODELS_HPP_INCLUDED

