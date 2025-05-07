#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    public:
        Ray(glm::vec3 origin, glm::vec3 direction);
};
#endif