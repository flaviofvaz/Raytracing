#include "scene.h"
#include "hit.h"

Scene::Scene(){}

Hit* Scene::computeIntersection(Ray* ray) 
{
    Hit* closestHit = nullptr;
    float min_t = 1024.0f*1024.0f*1024.0f;

    for (Instance* instance : this->sceneObjects)
    {
        Hit* currentHit = instance->computeIntersection(ray);
        if (currentHit)
        {
            min_t = currentHit->t;
            if (!closestHit)
            {
                closestHit = new Hit();
            }
            closestHit = currentHit;
        }
    }
    return closestHit;
}

glm::vec3 Scene::traceRay(Ray* ray)
{
    float r;
    glm::vec3 c;
    Hit* hit = computeIntersection(ray);
    if(hit)
    {
        if(hit->isLight())
        {
            r = hit->t;
            c = (hit->getLight()->power) / (r * r);
        }
        else
        {
            c = hit->getMaterial()->eval(this, hit, ray->getRayOrigin());
        }
        return c;
    }
    else
    {
        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
}
