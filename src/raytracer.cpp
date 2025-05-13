#include "raytracer.h"
#include "glm/glm.hpp"

void RayTracer::render(Film* film, Camera* camera, Scene* scene)
{
    for(int j = 0; j < film->getHeight(); j++)
    {
        for(int i = 0; i < film->getWidth(); i++)
        {
            // Sample pixel position
            glm::vec2 sampledPixel = film->pixelSampler(i, j);
            
            // Generate ray for this pixel
            Ray ray = camera->generateRay(sampledPixel.x, sampledPixel.y);
            
            // Trace ray and get color
            glm::vec3 color = scene->traceRay(ray);
            
            // Set pixel color
            film->setValue(i, j, color);
        }
    }
}