#ifndef TORUSKNOT_H
#define TORUSKNOT_H

#include "Shape.h"

namespace cgCourse
{
    class TorusKnot : public Shape
    {
    public:
        TorusKnot();
        TorusKnot(float offset);
        void draw();

        glm::vec3 getTubeCenterPoint(float t);

        glm::vec3 getNormal(float t, float s);

        size_t p = 1;                      // Windings horizontal
        size_t q = 5;                      // Windings vertical
        size_t tSegments = 150;            // Samples along torus knot
        size_t tubeSegments = 10;           // Segments of tube around torus knot
        float tubeRadius = 0.1;             // Radius of torus knot tube
        float majorRadiusTorus = 1.0;      // Outer radius of torus
        float minorRadiusTorus = 0.3;       // Inner radius of torus
    };
}

#endif //  TORUS_H