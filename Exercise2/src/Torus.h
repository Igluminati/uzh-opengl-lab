#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

namespace cgCourse
{
	class Torus : public Shape
	{
	public:
		Torus();

		void addTwoFaces(unsigned int idx1, unsigned int idx2, unsigned int idx3, unsigned int idx4);
	};
}

#endif // TORUS_H

