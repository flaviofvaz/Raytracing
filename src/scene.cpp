#include "scene.h"
#include "hit.h"

Scene::Scene(){}

Hit* Scene::computeIntersection(Ray* ray) 
{
    return new Hit();
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
}
