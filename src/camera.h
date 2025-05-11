#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "ray.h"

class Camera
{
    float angle;
    float distance;
    float ratio;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::mat4 viewMatrix;
    glm::mat4 inverseViewMatrix;

    public:
        Camera(float angle, float distance, float ratio, glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        Ray generateRay(float Xn, float Yn);
};
#endif