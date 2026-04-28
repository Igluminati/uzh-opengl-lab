#include "Torus.h"

#include <glm/glm.hpp>

#include <cmath>
#include <iostream>
#include <vector>

namespace cgCourse
{
	namespace
	{
		void accumulateTangentsFromFaces(const std::vector<glm::vec3> & positions,
										  const std::vector<glm::vec2> & texCoords,
										  const std::vector<glm::uvec3> & faces,
										  std::vector<glm::vec3> & tangentsOut,
										  const std::vector<glm::vec3> & normals)
		{
			tangentsOut.assign(positions.size(), glm::vec3(0.0f));
			for (const auto & f : faces)
			{
				const glm::vec3 & p0 = positions[f.x];
				const glm::vec3 & p1 = positions[f.y];
				const glm::vec3 & p2 = positions[f.z];
				const glm::vec2 & uv0 = texCoords[f.x];
				const glm::vec2 & uv1 = texCoords[f.y];
				const glm::vec2 & uv2 = texCoords[f.z];

				const glm::vec3 edge1 = p1 - p0;
				const glm::vec3 edge2 = p2 - p0;
				const glm::vec2 duv1 = uv1 - uv0;
				const glm::vec2 duv2 = uv2 - uv0;

				const float denom = duv1.x * duv2.y - duv2.x * duv1.y;
				if (std::abs(denom) < 1e-8f)
					continue;
				const float fdiv = 1.0f / denom;
				const glm::vec3 t = fdiv * (duv2.y * edge1 - duv1.y * edge2);

				tangentsOut[f.x] += t;
				tangentsOut[f.y] += t;
				tangentsOut[f.z] += t;
			}
			for (size_t i = 0; i < tangentsOut.size(); ++i)
			{
				const glm::vec3 & n = normals[i];
				glm::vec3 t = tangentsOut[i];
				t = glm::normalize(t - n * glm::dot(n, t));
				tangentsOut[i] = t;
			}
		}
	} // namespace

	// a simple 2D circle
	class Circle
	{
	public:
		Circle(float _radius, int _segments)
		{
			radius = _radius;
			segments = _segments;

			// generated equally distributed segments on this circle
			for (int j = 0; j < segments; j++)
			{
				float angle = (float) j * (360.0 / segments);
				float radians = Circle::toRadians(angle);
				vertices.push_back(glm::vec2(radius * std::sin(radians), radius * std::cos(radians)));
			}
		}

		const std::vector<glm::vec2> & getVertices() const
		{
			return vertices;
		}

		float getRadius() const
		{
			return radius;
		}

		int getSegments() const
		{
			return segments;
		}

		// Converting from degrees to radians
		// radians = (degrees * pi) / 180;
		static float toRadians(float _angle)
		{
			return _angle * M_PI / 180.0;
		}

	private:
		float radius;
		int segments;

		std::vector<glm::vec2> vertices;
	};


	Torus::Torus() : Shape()
	{
		float radiusX = 1.0;		// radius in xz-plane (main radius)
		float radiusY = 0.3;		// radius in xy-plane (radius of the ring segments)
		int segmentsInXZPlane = 50;	// subdivision in xz-plane (amount of ring segments)
		int segmentsInXYPlane = 30;	// subdivision in xy-plane

		std::vector<glm::vec3> midPoints;
		std::vector<float> midPointsLenght;

		Circle circleXZ(radiusX, segmentsInXZPlane);
		Circle circleXY(radiusY, segmentsInXYPlane);

		// calculate positions
		for (int j = 0; j < circleXZ.getSegments(); j++)
		{
			for (int i = 0; i < circleXY.getVertices().size(); i++)
			{
				glm::vec3 currentPoint(circleXZ.getVertices()[j].x, 0.0, circleXZ.getVertices()[j].y);
				glm::vec3 dirExtension = glm::normalize(currentPoint) * circleXY.getVertices()[i].x;
				currentPoint.y = circleXY.getVertices()[i].y;
				positions.push_back(currentPoint + dirExtension);
			}
		}

		// calculate faces
		for(int j = 0; j < circleXZ.getSegments(); j++)
		{
			int startIdx = j * circleXY.getSegments();
			if(j + 1 == circleXZ.getSegments())
			{
				// special case for connecting the last ring segments
				for(int i = 0; i < circleXY.getSegments(); i++)
				{
					int currIdx = startIdx + i;
					int firstSegIdx = i;
					if(i + 1 == circleXY.getSegments())
					{
						addTwoFaces(currIdx, firstSegIdx, startIdx, 0);
					}
					else
					{
						addTwoFaces(currIdx, firstSegIdx, currIdx + 1, firstSegIdx + 1);
					}
				}
			}
			else
			{
				// this parts connects all ring segments
				for (int i = 0; i < circleXY.getSegments(); i++)
				{
					int currIdx = startIdx + i;
					// special case for the last two faces of a single ring segment
					if(i + 1 == circleXY.getSegments())
					{
						addTwoFaces(currIdx, currIdx + circleXY.getSegments(), startIdx, startIdx + circleXY.getSegments());
					}
					else
					{
						addTwoFaces(currIdx, currIdx + circleXY.getSegments(), currIdx + 1, currIdx + 1 + circleXY.getSegments());
					}
				}
			}
		}

		// just color the object from black to green
		for(int i = 0; i < positions.size(); i++)
		{
			colors.push_back(glm::vec3(0.06, 0.55, 0.31));
		}

		// adding normals
		normals.resize(positions.size());
		for(const auto & f: faces)
		{
			glm::vec3 v1 = positions[f.y] - positions[f.x];
			glm::vec3 v2 = positions[f.z] - positions[f.x];
			glm::vec3 n = glm::normalize(glm::cross(v1, v2));
			normals[f.x] += n;
			normals[f.y] += n;
			normals[f.z] += n;
		}

		for(auto & n: normals)
			n = glm::normalize(n);

        // TODO: set the texture coordinates for the torus
        //       first thing here is to think about how you want to map the texture
        //       on the torus. I decided that the texture should appear 4 times on the torus,
        //       but you can do that how you want. Remember that you can do the repetition of
        //       the same texture either by setting the texture coordinates between 0.0 and 1.0
        //       or by using one of the texture functions, e.g. with GL_REPEAT

        //texCoords...
		texCoords.resize(positions.size());
		{
			const int ringSeg = circleXZ.getSegments();
			const int tubeSeg = static_cast<int>(circleXY.getVertices().size());
			for (int j = 0; j < ringSeg; ++j)
			{
				for (int i = 0; i < tubeSeg; ++i)
				{
					const int idx = j * tubeSeg + i;
					const float u = (static_cast<float>(j) / static_cast<float>(ringSeg)) * 4.0f;
					const float v = static_cast<float>(i) / static_cast<float>(tubeSeg);
					texCoords[static_cast<size_t>(idx)] = glm::vec2(u, v);
				}
			}
		}

        // END TODO

        // TODO: set the tangents for the torus. To do this think about how the tangents
        // have to look like for the torus by drawing it to a paper sheet.
        // There are multiple ways of generating the tangents. Be aware that the normals are interpolated over
        // all adjacent faces so the tangents at these points will not necessarily follow one of the surface edges.

        // tangents...
		accumulateTangentsFromFaces(positions, texCoords, faces, tangents, normals);

        // END TODO
    }

	void Torus::addTwoFaces(unsigned int _idx0, unsigned int _idx1, unsigned int _idx2, unsigned int _idx3)
	{
		faces.push_back(glm::uvec3(_idx0, _idx2, _idx1));
		faces.push_back(glm::uvec3(_idx2, _idx3, _idx1));
	}
}

