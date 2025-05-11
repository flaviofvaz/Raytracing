#include "instance.h"

Hit* Instance::computeIntersection(Ray* ray)
{
    bool wasHit;
    Hit* hit = new Hit();
    wasHit = this->shape->intersect(ray, hit);
    if(wasHit)
    {
        hit->setMaterial(this->material);
        return hit;
    }
    else
    {
        delete hit;
        return nullptr;
    }
}