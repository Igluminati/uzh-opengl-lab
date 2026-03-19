#ifndef UNIT_CUBE_H
#define UNIT_CUBE_H

#include "Shape.h"

namespace cgCourse
{
    class UnitCube : public Shape
    {
    public:
        UnitCube();

        void draw() const override;
    };
}

#endif // UNIT_CUBE
