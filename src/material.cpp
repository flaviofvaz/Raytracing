#include "material.h"
#include <glm/glm.hpp>
#include <cmath>
#include "scene.h"
#include "light.h"

glm::vec3 Phong::eval(const Scene* scene, const Hit* hit, const glm::vec3& rayOrigin) const
{
    glm::vec3 c = ambient * scene->getAmbientLight();
    glm::vec3 v = glm::normalize(rayOrigin - hit->position);

    for (const auto& sceneObject : scene->getObjects())
    {
        if (sceneObject->isLight())
        {
            glm::vec3 L;
            glm::vec3 l = sceneObject->getLight()->radiance(scene, hit->position, &L);
            
            // Diffuse component
            float diffuseFactor = glm::dot(hit->normal, l);//glm::max(0.0f, glm::dot(hit->normal, l));
            c += diffuse * L * diffuseFactor;
        
            // Specular component
            glm::vec3 r = reflect(-l, hit->normal);
            float glossyFactor = glm::max(0.0f, glm::dot(r, v));
            //c += glossy * L * std::pow(glossyFactor, shininess);
            c += glossy * std::pow(glossyFactor, shininess);
        }
    }
    
    return c;
}

glm::vec3 Phong::reflect(const glm::vec3& incident, const glm::vec3& normal) const
{
    return 2.0f * glm::dot(normal, incident) * normal - incident;
}