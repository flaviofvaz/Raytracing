#include "raytracer.h"

void RayTracer::render(Film* film, Camera* camera, Scene* scene)
{
    glm::vec2 sampledPixel;
    glm::vec3 c;
    for(int i = 0; i < film->getWidth(); i++)
    {
        for(int j = 0; j < film->getHeight(); j++)
        {
            sampledPixel = film->pixelSampler(i, j);
            Ray ray = camera->generateRay(sampledPixel.x, sampledPixel.y);
            c = scene->traceRay(&ray);
            film->setValue(i, j, c);
        }
    }
}