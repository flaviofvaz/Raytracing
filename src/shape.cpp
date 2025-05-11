#include "shape.h"
#include "ray.h"
#include "hit.h"

#include <glm/glm.hpp>

#define EPSILON 1e-6f

Plane::Plane(glm::vec3 point, glm::vec3 normal)
{
    this->point = point;
    this->normal = glm::normalize(normal);
}

bool Plane::intersect(Ray* ray, Hit* hit)
{
    glm::vec3* rayDirection;
    glm::vec3* rayOrigin;
    float dotProd, t;

    rayDirection = ray->getRayDirection();
    rayOrigin = ray->getRayOrigin();

    // check if ray and plane are parallel
    dotProd = glm::dot(*rayDirection, this->normal);
    if(std::abs(dotProd) < EPSILON)
    {
        return false;
    }
    else
    {   
        // calculating intersection point
        t = glm::dot((this->point - *rayOrigin), this->normal) / dotProd;

        // intersection behind ray?
        if(t < 0) 
        {
            return false;
        }
        
        hit->t = t;
        hit->position = *rayOrigin + t * (*rayDirection);
        
        // backface?
        if(dotProd < 0)
        {
            hit->normal = -this->normal;
            hit->backface = true;
        }
        else
        {
            hit->normal = this->normal;
            hit->backface = false;
        }
        return true;
    }
}

Sphere::Sphere(glm::vec3 center, float radius)
{
    this->radius = radius;
    this->center = center;
}

bool Sphere::intersect(Ray* ray, Hit* hit)
{
    glm::vec3* rayDirection;
    glm::vec3* rayOrigin;
    glm::vec3 rayCenterDistance;
    glm::vec3* normal;
    float dotProd, t, t1, t2, a, b, c, delta;

    rayDirection = ray->getRayDirection();
    rayOrigin = ray->getRayOrigin();

    rayCenterDistance = *rayOrigin - this->center;

    // check if ray and plane are parallel
    a = glm::dot(*rayDirection, *rayDirection);
    b = 2.0f * glm::dot(*rayDirection, rayCenterDistance); // more efficient multiplying by a scalar
    c = glm::dot(rayCenterDistance, rayCenterDistance) - this->radius * this->radius;

    delta = b*b - 4*a*c;
    if(delta < 0) // no intersection
    {
        return false;
    }
    else
    {
        t1 = (-b - std::sqrt(delta))/(2*a); // this one is the nearest intersection since delta is greater than zero
        t2 = (-b + std::sqrt(delta))/(2*a);

        if(t1 < 0 && t2 < 0)
        {
            // both intersections are behind the ray
            return false;
        }

        // at this point at least one of the values is greater than or equal to 0  
        if(t1 < 0)
        {
            t = t2;
        }
        else
        {
            t = t1;
        }
    }
    
    // avoiding auto intersection
    if(t < EPSILON)
    {
        return false;
    }

    hit->t = t;
    hit->position = *rayOrigin + t * (*rayDirection);      

    *normal = (hit->position - center) / radius; // normalizing
    if (t1 < 0 || t2 < 0)
    {
        hit->normal = -*normal;
        hit->backface = true;
    }
    else
    {
        hit->normal = *normal;
        hit->backface = false;
    }
    return true;
}