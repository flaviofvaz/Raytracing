#include "light.h"
#include "scene.h"
#include "ray.h"
#include <memory>

PointLight::PointLight(const glm::vec3& position, const glm::vec3& power) 
    : Light(), position(position), power(power) {}

glm::vec3 PointLight::radiance(const Scene* scene, const glm::vec3& point, glm::vec3* L) const
{
    glm::vec3 l = glm::normalize(position - point);
    float r = glm::distance(point, position);
    
    // Check if light is visible (not blocked by any object)
    Ray shadowRay(point, l);
    auto hit = scene->computeIntersection(shadowRay);
    
    // If there's a hit and it's not the light itself, or if the hit is closer than the light
    if (hit && hit->isLight() && hit->getLight() == this) 
    {
        // Light is visible, calculate attenuation
        float attenuation = 1.0f / (r * r);
        *L = power * attenuation;
        return l;
    }
    else
    {
        *L = glm::vec3(0.0f);
        return glm::vec3(0.0f);
    }
}