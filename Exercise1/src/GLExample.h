#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "GLApp.h"
#include "Torus.h"
#include <glm/mat4x4.hpp>
#include <memory>

namespace cgCourse
{
    class GLExample : public GLApp
    {
    public:
        GLExample(glm::uvec2 _windowSize, std::string _title);

        bool init() override;
        bool render() override;
        bool end() override;

    private:
        bool loadAndCompileShaderToGPU(GLuint shader, const std::string & source);
        bool checkLinkStatusOfProgram(GLuint program);
        glm::mat4 computeViewProjectionMatrix() const;

        GLuint program = 0;
        GLuint mvpUniformLocation = 0;
        glm::mat4 mvpMatrix;

        // Our Warped Torus
        std::shared_ptr<Torus> torus;

        // **TODO**: You could add a boolean or variable to toggle wireframe vs. fill
        bool wireframeMode = false;
    };
}

#endif // GLEXAMPLE_H
