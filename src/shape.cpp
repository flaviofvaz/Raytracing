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

Box::Box(glm::vec3 bMin, glm::vec3 bMax)
{
    this->bMin = bMin;
    this->bMax = bMax;
}

bool Box::intersect(Ray* ray, Hit* hit)
{
    glm::vec3* rayOrigin = ray->getRayOrigin();
    glm::vec3* rayDirection = ray->getRayDirection();

    // Calculate intersection t values for each slab
    glm::vec3 t0s = (this->bMin - *rayOrigin) / *rayDirection;
    glm::vec3 t1s = (this->bMax - *rayOrigin) / *rayDirection;

    glm::vec3 t_near_axis = glm::min(t0s, t1s);
    glm::vec3 t_far_axis = glm::max(t0s, t1s);

     // The overall t_enter is the maximum of the near t's for each axis
    float t_enter = glm::max(glm::max(t_near_axis.x, t_near_axis.y), t_near_axis.z);
    // The overall t_exit is the minimum of the far t's for each axis
    float t_exit = glm::min(glm::min(t_far_axis.x, t_far_axis.y), t_far_axis.z);

    // Condition for no intersection:
    // 1. If entry point is after exit point (ray misses the intersection of slabs)
    // 2. If the entire box is behind the ray's origin (t_exit < 0)
    if (t_enter > t_exit || t_exit < EPSILON) 
    {
        return false;
    }

    // Determine the actual intersection distance t_final
    float t_final = t_enter;
    bool ray_starts_inside = false;

    if (t_enter < EPSILON) { // Ray origin is inside the box or on its surface
        t_final = t_exit;    // Use the exit point as the intersection
        ray_starts_inside = true;
    }

    // If this intersection is closer than what's already in 'hit'
    if (t_final < hit->t && t_final > EPSILON) { // Ensure t_final is positive and closer
        hit->t = t_final;
        hit->position = *rayOrigin + t_final * (*rayDirection);
        //hit->object = this; 

        // Calculate the normal at the intersection point
        glm::vec3 p = hit->position;
        glm::vec3 normal(0.0f);
        const float norm_epsilon = 1e-4f; // Tolerance for comparing point to face

        // The normal points outwards. If the ray starts inside, t_final corresponds
        // to an exit point, and the normal should still be the outward normal of that exit face.
        if (std::abs(p.x - this->bMin.x) < norm_epsilon) normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        else if (std::abs(p.x - this->bMax.x) < norm_epsilon) normal = glm::vec3(1.0f, 0.0f, 0.0f);
        else if (std::abs(p.y - this->bMin.y) < norm_epsilon) normal = glm::vec3(0.0f, -1.0f, 0.0f);
        else if (std::abs(p.y - this->bMax.y) < norm_epsilon) normal = glm::vec3(0.0f, 1.0f, 0.0f);
        else if (std::abs(p.z - this->bMin.z) < norm_epsilon) normal = glm::vec3(0.0f, 0.0f, -1.0f);
        else if (std::abs(p.z - this->bMax.z) < norm_epsilon) normal = glm::vec3(0.0f, 0.0f, 1.0f);
        // else: In a perfect scenario, one of these should be true.
        // For robustness if p is slightly off due to float precision, a more complex normal
        // determination might be needed, but this is standard for AABBs.
        // You might also determine the normal based on which t_near_axis[i] or t_far_axis[i]
        // defined t_enter or t_exit, which is more robust for edge cases.

        hit->normal = normal;
        return true;
    }

    return false;
}