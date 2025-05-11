#include "light.h"
#include "scene.h"
#include "ray.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 power) 
{
    this->position = position;
    this->power = power;
}

glm::vec3 PointLight::radiance(Scene* scene, glm::vec3 point, glm::vec3* L)
{
    glm::vec3 l;
    Hit* hitScene;
    float distance;

    l = glm::normalize(this->position - point);
    Ray* ray = new Ray(&point, &l);
    hitScene = scene->computeIntersection(ray);
    if(hitScene->isLight())
    {
        distance = glm::distance(point, hitScene->position);
        *L = this->position / (distance * distance);
    }
    else
    {
        *L = glm::vec3(0.0f, 0.0f, 0.0f);
        l = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    return l;
}