#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{   
    private:
        glm::vec3* direction;
        glm::vec3* origin;
    public:
        Ray(glm::vec3* origin, glm::vec3* direction);
        glm::vec3* getRayDirection() { return this->direction; };
        glm::vec3* getRayOrigin() { return this->origin; };
};
#endif