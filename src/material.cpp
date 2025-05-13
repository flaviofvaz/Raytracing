#include "material.h"
#include <glm/glm.hpp>
#include <cmath>
#include "scene.h"
#include "light.h"

glm::vec3 Phong::eval(const Scene* scene, const Hit* hit, const glm::vec3& rayOrigin) const
{
    glm::vec3 c = ambient * scene->getAmbientLight();
    glm::vec3 v = glm::normalize(rayOrigin - hit->position);

    for (const auto& lightSource : scene->getObjects())
    {
        if (lightSource->isLight())
        {
            glm::vec3 L;
            glm::vec3 l = lightSource->getLight()->radiance(scene, hit->position, &L);
            
            //if (glm::length(L) > 0.0f)  // Only process if light is visible
            //{
                // Diffuse component
                float diffuseFactor = glm::max(0.0f, glm::dot(hit->normal, l));
                c += diffuse * L * diffuseFactor;
            
                // Specular component
                glm::vec3 r = reflect(-l, hit->normal);
                float glossyFactor = glm::max(0.0f, glm::dot(r, v));
                //color += glossy * L * std::pow(glossyFactor, shininess);
                c += glossy * std::pow(glossyFactor, shininess);
            //}
        }
    }
    
    return glm::clamp(c, 0.0f, 1.0f);
}

glm::vec3 Phong::reflect(const glm::vec3& incident, const glm::vec3& normal) const
{
    return 2.0f * glm::dot(normal, incident) * normal - incident;
}