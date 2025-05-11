#ifndef MATERIAL_H
#define MATERIAL_H

#include<glm/glm.hpp>
#include "scene.h"
#include "hit.h"

class Material
{
    public:
        Material() {};
        glm::vec3 eval(Scene* scene, Hit* hit, glm::vec3* rayOrigin);
};

class Phong : Material
{
    public:
        Phong(glm::vec3* diffuse, glm::vec3* glossy, glm::vec3* ambient, glm::vec3* shininess)
            : diffuse(diffuse), glossy(glossy), ambient(ambient), shininess(shininess) {};
        glm::vec3* diffuse;
        glm::vec3* glossy;
        glm::vec3* ambient;
        glm::vec3* shininess;
        glm::vec3* eval(Scene* scene, Hit* hit, glm::vec3* rayOrigin);
        glm::vec3* reflect(glm::vec3* l, glm::vec3* normal);
};
#endif