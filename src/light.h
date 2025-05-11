#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "scene.h"

class Light
{
    public:
        Light(){};
        glm::vec3 power;
        glm::vec3 radiance(Scene* scene, glm::vec3 point, glm::vec3* L);
};

class PointLight : public Light
{   
    public:
        PointLight(glm::vec3 position, glm::vec3 power);
        glm::vec3 position;
        glm::vec3 radiance(Scene* scene, glm::vec3 point, glm::vec3* L);
};
#endif 