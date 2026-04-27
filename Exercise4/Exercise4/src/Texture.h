#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLIncludes.h"
#include <string>
#include <glm/vec2.hpp>

namespace cgCourse
{
    class Texture
    {
    public:
        void loadFromFile(const std::string & filename);
        void createBonus(int checkerSize);
        void createBonusSpecular(int checkerSize);
        void createBonusNormal(int checkerSize);
        const GLuint & getTexHandle() const;

    private:
        GLuint texhandle = 0;

        // Texture info
        glm::vec2 size;
        uint8_t bitsPerPixel = 0;
    };
}

#endif // TEXTURE_H

