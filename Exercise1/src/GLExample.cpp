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

        // Screenshot (i): Filled, no offset, no twist
        // torus = std::make_shared<Torus>(5.0f, 1.0f, 32, 16, 0.0f, 0.0f);

        // Screenshot (ii): Wireframe, no offset, no twist
        // torus = std::make_shared<Torus>(5.0f, 1.0f, 32, 16, 0.0f, 0.0f);

        // Screenshot (iii): Wireframe + offset
        // torus = std::make_shared<Torus>(5.0f, 1.0f, 32, 16, 0.5f, 0.0f);

        // Screenshot (iv): Wireframe + offset + twist
        // torus = std::make_shared<Torus>(5.0f, 1.0f, 32, 16, 0.5f, 0.2f);

        // Screenshot (v): Wireframe + offset + twist + face culling (bonus)
        torus = std::make_shared<Torus>(5.0f, 1.0f, 32, 16, 0.5f, 0.2f);

        // (Optional) position the torus
        // torus->setShapePosition(glm::vec3(0.0f, 0.0f, 0.0f));
	torus->createVertexArray(0,1,2);

        return true;
    }

    bool GLExample::render()
    {
        glEnable(GL_DEPTH_TEST);

        // Clear color & depth
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Screenshot (i): filled mode, no culling
        // wireframeMode = false; glDisable(GL_CULL_FACE);

        // Screenshot (ii)-(iv): wireframe mode, no culling
        // wireframeMode = true; glDisable(GL_CULL_FACE);

        // Screenshot (v): wireframe mode + face culling (bonus)
        wireframeMode = true;
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        if (wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // Use our shader program
        glUseProgram(program);

        // Compute MVP
        glm::mat4 viewProj = computeViewProjectionMatrix();
        mvpMatrix = viewProj * torus->getModelMatrix();
        glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, &mvpMatrix[0][0]);


        // **TODO**: Draw the torus
	torus->draw();
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
