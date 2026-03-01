#include "GLExample.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> // for lookAt, perspective

namespace cgCourse
{
    GLExample::GLExample(glm::uvec2 _windowSize, std::string _title)
        : GLApp(_windowSize, _title, false)
    {
    }

    bool GLExample::init()
    {
        // Set viewport
        glm::uvec2 fbSize = getFramebufferSize();
        glViewport(0, 0, int(fbSize.x), int(fbSize.y));

        // Load & compile shaders
        std::string vertShaderString = loadFile(std::string(SHADER_DIR) + "/Cube.vert");
        std::string fragShaderString = loadFile(std::string(SHADER_DIR) + "/Cube.frag");

        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        loadAndCompileShaderToGPU(vertShader, vertShaderString);
        loadAndCompileShaderToGPU(fragShader, fragShaderString);

        program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);
        checkLinkStatusOfProgram(program);

        // We can delete the intermediate shader objects
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        // Retrieve uniform location for the MVP matrix
        mvpUniformLocation = glGetUniformLocation(program, "mvpMatrix");

        // **TODO**: Create your torus object with some warp
        // For example: R=5.0f, r=1.0f, numSegments=32, numTubeSegments=16, offset=0.5, twistFactor=0.2)


        // (Optional) position the torus
        // torus->setShapePosition(glm::vec3(0.0f, 0.0f, 0.0f));

        return true;
    }

    bool GLExample::render()
    {
        glEnable(GL_DEPTH_TEST);

        // Clear color & depth
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // **TODO**: Optionally enable face culling
 

        // **TODO**: Switch between wireframe & fill


        // Use our shader program
        glUseProgram(program);

        // Compute MVP
        glm::mat4 viewProj = computeViewProjectionMatrix();
        mvpMatrix = viewProj * torus->getModelMatrix();
        glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, &mvpMatrix[0][0]);


        // **TODO**: Draw the torus

        return true;
    }

    bool GLExample::end()
    {
        if(program)
        {
            glDeleteProgram(program);
        }
        return true;
    }

    bool GLExample::loadAndCompileShaderToGPU(GLuint shader, const std::string & source)
    {
        GLint status;
        GLchar errorMessage[512];

        const char* sPtr = source.c_str();
        int length = (int)source.size();
        glShaderSource(shader, 1, &sPtr, &length);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if(!status)
        {
            glGetShaderInfoLog(shader, 512, nullptr, errorMessage);
            std::cerr << "Shader compilation error:\n" << errorMessage << std::endl;
            return false;
        }
        return true;
    }

    bool GLExample::checkLinkStatusOfProgram(GLuint prog)
    {
        GLint status;
        GLchar errorMessage[512];

        glGetProgramiv(prog, GL_LINK_STATUS, &status);
        if(!status)
        {
            glGetProgramInfoLog(prog, 512, nullptr, errorMessage);
            std::cerr << "Linking error:\n" << errorMessage << std::endl;
            return false;
        }
        return true;
    }

    glm::mat4 GLExample::computeViewProjectionMatrix() const
    {
        // Basic camera
        glm::mat4 view = glm::lookAt(
            glm::vec3(-1, 18, -18),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );

        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;
        glm::uvec2 fbSize = getFramebufferSize();
        float aspect = float(fbSize.x) / float(fbSize.y);

        glm::mat4 proj = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
        return proj * view;
    }
}
