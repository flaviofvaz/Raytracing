#include "material.h"
#include <glm/glm.hpp>
#include "scene.h"
#include "light.h"

glm::vec3* Phong::eval(Scene* scene, Hit* hit, glm::vec3* rayOrigin)
{
    glm::vec3 c, v, L, l;
    glm::vec3* r; 
    c = glm::vec3(0,0,0);

    v = glm::normalize(*rayOrigin - hit->position);
    for (Light* lightSource : scene->lightSources)
    {
        l = lightSource->radiance(scene, hit->position, &L);
        c += *this->diffuse * L * hit->normal * l;
        r = this->reflect(&-l, &hit->normal);
        c += *this->glossy * glm::max(0.0f, glm::dot(*r, v));
    }
    return &c;
}

glm::vec3* Phong::reflect(glm::vec3* l, glm::vec3* normal)
{
    return &(2.0f * glm::dot(*normal, *l) * *normal - *l); 
}