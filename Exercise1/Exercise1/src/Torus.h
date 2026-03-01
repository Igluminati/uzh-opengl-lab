#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

namespace cgCourse
{
    class Torus : public Shape
    {
    public:
        /*
         * Constructor parameters:
         *   - R, r: Major/minor radii
         *   - numSegments, numTubeSegments: Discretization around major/minor circles
         *   - offset: offset along normals
         *   - twistFactor: parameter to warp the torus shape
         */
        Torus(float R, float r,
              int numSegments, int numTubeSegments,
              float offset,
              float twistFactor);

        // Draw the torus
        void draw() override;

    private:
        // Generate positions, normals, color, and faces
        void generateMesh();   
        
        // Shift vertices along their normals by 'offset'
        void applyOffset();

        float R;               // Major radius
        float r;               // Minor radius
        int   numSegments;     // Divisions around major circle
        int   numTubeSegments; // Divisions around tube circle
        float offset;          // Offset along normals
        float twistFactor;     // Warping parameter
    };
}

#endif // TORUS_H
