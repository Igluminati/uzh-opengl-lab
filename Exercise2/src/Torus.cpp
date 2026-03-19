#include "Torus.h"

#include <iostream>
#include <cmath>

namespace cgCourse
{
	// a simple 2D circle
	struct Circle
	{
		Circle(const float _radius, const int segments)
		{
			radius = _radius;

			for(int j = 0; j < segments; j++)
			{
				float angle = (float) j * (360.0 / segments);
				float radians = Circle::toRadians(angle);
				vertices.push_back({radius * std::sin(radians), radius * std::cos(radians)});
			}
		}

		float getRadius() const
		{
			return radius;
		}

		// Converting from degrees to radians
		// radians = (degrees * pi) / 180;
		static float toRadians(float _angle)
		{
			return _angle * M_PI / 180.0;
		}

		float radius;
		std::vector<glm::vec2> vertices;
	};


	Torus::Torus(): Shape()
	{
		const float radiusX = 1.0;	// radius in xz-plane (main radius)
		const float radiusY = 0.3;	// radius in xy-plane (radius of the ring segments)
		const int segmentsXZ = 50;	// subdivision in xz-plane (amount of ring segments)
		const int segmentsXY = 30;	// subdivision in xy-plane

		std::vector<glm::vec3> midPoints;
		std::vector<float> midPointsLenght;

		Circle circleXZ(radiusX, segmentsXZ);
		Circle circleXY(radiusY, segmentsXY);


		for(const glm::vec2 & u: circleXZ.vertices)
		for(const glm::vec2 & v: circleXY.vertices)
		{
			glm::vec3 currentPoint(u.x, 0.0, u.y);
			glm::vec3 dirExtension = glm::normalize(currentPoint) * v.x;
			currentPoint.y = v.y;
			positions.push_back(currentPoint + dirExtension);
		}


		auto idx = [&](int i, int j) -> int
		{
			return (j % segmentsXZ) * segmentsXY + i % segmentsXY;
		};

		for(int j = 0; j < segmentsXZ; ++j)
		for(int i = 0; i < segmentsXY; ++i)
			addTwoFaces(idx(i, j), idx(i, j + 1), idx(i + 1, j), idx(i + 1, j + 1));

		colors.assign(positions.size(), {0.06, 0.55, 0.31});

		computeNormals();
	}

	void Torus::addTwoFaces(unsigned int idx0, unsigned int idx1, unsigned int idx2, unsigned int idx3)
	{
		faces.push_back({idx0, idx2, idx1});
		faces.push_back({idx2, idx3, idx1});
	}
}


