#include "hit.h"

Hit::Hit(int t, glm::vec3 position, glm::vec3 normal, bool backface)
{
    this->t = t;
    this->backface = backface;
    this->position = position;
    this->normal = normal;
}

