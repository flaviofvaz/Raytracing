#include "light.h"
#include "scene.h"
#include "ray.h"

    
inline float Random()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

PointLight::PointLight(const glm::vec3& position, const glm::vec3& power) 
    : Light(), position(position), power(power) {}

glm::vec3 PointLight::radiance(const Scene* scene, const glm::vec3& point, glm::vec3* L) const
{
    glm::vec3 l = glm::normalize(position - point);
    float r = glm::distance(position, point);
    
    // adding a small epsilon to avoid self-intersection
    Ray shadowRay(point + 1e-4f, l);
    auto hit = scene->computeIntersection(shadowRay);
    
    if (hit && hit->isLight() && hit->getLight() == this) 
    {
        *L = power / (r * r);
        return l;
    }
    {
       *L = glm::vec3(0.0f);
       return glm::vec3(0.0f);
    }
}

AreaLight::AreaLight(const glm::vec3& position, const glm::vec3& power, const glm::vec3& ei, const glm::vec3& ej, float nSamples)
    : Light(), position(position), power(power), ei(ei), ej(ej), nSamples(nSamples)
    {
        glm::vec3 crossProduct = glm::cross(ei, ej);
        normal = glm::normalize(crossProduct);
        area = glm::length(crossProduct);
    } 

glm::vec3 AreaLight::getSample() const
{
    return position + ei * Random() + ej * Random();
}

glm::vec3 AreaLight::radiance(const Scene* scene, const glm::vec3& point, glm::vec3* L) const
{
    glm::vec3 s = getSample();
    
    glm::vec3 l = glm::normalize(s - point);
    
    Ray shadowRay(point + 1e-4f * l, l);
    auto hit = scene->computeIntersection(shadowRay);
    if (hit && hit->isLight() && hit->getLight() == this) 
    {
        glm::vec3 dif = point - s;
        float r = glm::dot(dif, dif);

        *L = power * glm::dot(-l, normal) / (r * r);
        *L *= getArea() / getSampleCount();
        return l;
    }
    {
       *L = glm::vec3(0.0f);
       return glm::vec3(0.0f);
    }
}