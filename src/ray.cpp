#include "ray.h"
#include <glm/glm.hpp>

Ray::Ray(glm::vec3* origin, glm::vec3* direction)
{
    this->origin = origin;
    this->direction = &glm::normalize(*direction);
}