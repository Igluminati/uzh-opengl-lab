#include "TorusKnot.h"
#include <iostream>

// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES

#include <math.h>

namespace cgCourse {
    TorusKnot::TorusKnot() : TorusKnot(0.0) {}

    TorusKnot::TorusKnot(float offset) {
        // This implementation is based primarily on: https://www.gsn-lib.org/docs/nodes/MeshTorusNode.php

        float deltaT = 2 * M_PI / tSegments;
        float deltaTube = 2 * M_PI / tubeSegments;

        for (int t_i = 0; t_i < tSegments; t_i++) {
            float t = t_i * deltaT;
            glm::vec3 center = getTubeCenterPoint(t);
            for (int s_i = 0; s_i < tubeSegments; s_i++) {
                float s = s_i * deltaTube;
                glm::vec3 normal = getNormal(t, s);
                positions.push_back(center + tubeRadius * normal);
                normals.push_back(normal);
                colors.push_back(glm::vec3(1.0, 0.1, 0.0));

                size_t a = t_i * tubeSegments + s_i;
                size_t b = t_i * tubeSegments + (s_i + 1) % tubeSegments;
                size_t c = ((t_i + 1) % tSegments) * tubeSegments + (s_i + 1) % tubeSegments;
                size_t d = ((t_i + 1) % tSegments) * tubeSegments + s_i;
                faces.push_back(glm::vec3(d, a, c));
                faces.push_back(glm::vec3(c, a, b));
            }
        }

        // apply scaling along normals

        for (int i = 0; i < positions.size(); i++) {
            positions[i] = positions[i] + normals[i] * offset;
        }
    }

    void TorusKnot::draw() {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    glm::vec3 TorusKnot::getTubeCenterPoint(float t) {
        return glm::vec3((majorRadiusTorus + minorRadiusTorus * cos(q * t)) * cos(p * t),
                         (majorRadiusTorus + minorRadiusTorus * cos(q * t)) * sin(p * t), minorRadiusTorus * sin(q * t));
    }

    glm::vec3 TorusKnot::getNormal(float t, float s) {
        glm::vec3 nPrime = glm::vec3(cos(p * t) * cos(q * t), sin(p * t) * cos(q * t), sin(q * t));
        glm::vec3 tPrime = glm::normalize(
                p * (majorRadiusTorus + minorRadiusTorus * cos(q * t)) * glm::vec3(-sin(p * t), cos(p * t), 0.0) +
                q * minorRadiusTorus * glm::vec3(-sin(q * t) * cos(p * t), -sin(q * t) * sin(p * t), cos(q * t))
        );
        glm::vec3 bPrime = glm::cross(tPrime, nPrime);
        return glm::normalize(cos(s) * nPrime + sin(s) * bPrime);
    }
}