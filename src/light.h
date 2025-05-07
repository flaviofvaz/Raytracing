#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
    Light();

    float power;
};

class PointLight : Light
{
    glm::vec3 position;
};
#endif 