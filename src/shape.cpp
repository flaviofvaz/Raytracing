#include "shape.h"
#include "ray.h"
#include "hit.h"

#include <glm/glm.hpp>
#include <cmath>

#define EPSILON 1e-6f

Plane::Plane(const glm::vec3& point, const glm::vec3& normal)
    : point(point)
    , normal(glm::normalize(normal))
{
}

bool Plane::intersect(const Ray& ray, Hit* hit) const
{
    const glm::vec3& rayDirection = ray.getRayDirection();
    const glm::vec3& rayOrigin = ray.getRayOrigin();
    float dotProd = glm::dot(rayDirection, normal);

    // check if ray and plane are parallel
    if(std::abs(dotProd) < EPSILON)
    {
        return false;
    }
    
    // calculating intersection point
    float t = glm::dot((point - rayOrigin), normal) / dotProd;

    // intersection behind ray?
    if(t < 0) 
    {
        return false;
    }
    
    hit->t = t;
    hit->position = rayOrigin + t * rayDirection;
    
    // backface?
    if(dotProd < 0)
    {
        hit->normal = -normal;
        hit->backface = true;
    }
    else
    {
        hit->normal = normal;
        hit->backface = false;
    }
    return true;
}

Sphere::Sphere(const glm::vec3& center, float radius)
    : center(center)
    , radius(radius)
{
}

bool Sphere::intersect(const Ray& ray, Hit* hit) const
{
    const glm::vec3& rayDirection = ray.getRayDirection();
    const glm::vec3& rayOrigin = ray.getRayOrigin();
    glm::vec3 rayCenterDistance = rayOrigin - center;

    float a = glm::dot(rayDirection, rayDirection);
    float b = 2.0f * glm::dot(rayDirection, rayCenterDistance);
    float c = glm::dot(rayCenterDistance, rayCenterDistance) - radius * radius;

    float delta = b*b - 4*a*c;
    if(delta < 0) // no intersection
    {
        return false;
    }

    float t1 = (-b - std::sqrt(delta))/(2*a);
    float t2 = (-b + std::sqrt(delta))/(2*a);

    if(t1 < 0 && t2 < 0)
    {
        // both intersections are behind the ray
        return false;
    }

    // at this point at least one of the values is greater than or equal to 0  
    float t = (t1 < 0) ? t2 : t1;
    
    // avoiding auto intersection
    if(t < EPSILON)
    {
        return false;
    }

    hit->t = t;
    hit->position = rayOrigin + t * rayDirection;      

    glm::vec3 normal = (hit->position - center) / radius; // normalizing
    if (t1 < 0 || t2 < 0)
    {
        hit->normal = -normal;
        hit->backface = true;
    }
    else
    {
        hit->normal = normal;
        hit->backface = false;
    }
    return true;
}

Box::Box(const glm::vec3& bMin, const glm::vec3& bMax)
    : bMin(bMin)
    , bMax(bMax)
{
}

bool Box::intersect(const Ray& ray, Hit* hit) const
{
    const glm::vec3& rayOrigin = ray.getRayOrigin();
    const glm::vec3& rayDirection = ray.getRayDirection();

    // Calculate intersection t values for each slab
    glm::vec3 t0s = (bMin - rayOrigin) / rayDirection;
    glm::vec3 t1s = (bMax - rayOrigin) / rayDirection;

    glm::vec3 t_near_axis = glm::min(t0s, t1s);
    glm::vec3 t_far_axis = glm::max(t0s, t1s);

    // The overall t_enter is the maximum of the near t's for each axis
    float t_enter = glm::max(glm::max(t_near_axis.x, t_near_axis.y), t_near_axis.z);
    // The overall t_exit is the minimum of the far t's for each axis
    float t_exit = glm::min(glm::min(t_far_axis.x, t_far_axis.y), t_far_axis.z);

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
        hit->position = rayOrigin + t_final * rayDirection;

        // Calculate the normal at the intersection point
        glm::vec3 p = hit->position;
        glm::vec3 normal(0.0f);
        const float norm_epsilon = 1e-4f; // Tolerance for comparing point to face

        // The normal points outwards. If the ray starts inside, t_final corresponds
        // to an exit point, and the normal should still be the outward normal of that exit face.
        if (std::abs(p.x - bMin.x) < norm_epsilon) normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        else if (std::abs(p.x - bMax.x) < norm_epsilon) normal = glm::vec3(1.0f, 0.0f, 0.0f);
        else if (std::abs(p.y - bMin.y) < norm_epsilon) normal = glm::vec3(0.0f, -1.0f, 0.0f);
        else if (std::abs(p.y - bMax.y) < norm_epsilon) normal = glm::vec3(0.0f, 1.0f, 0.0f);
        else if (std::abs(p.z - bMin.z) < norm_epsilon) normal = glm::vec3(0.0f, 0.0f, -1.0f);
        else if (std::abs(p.z - bMax.z) < norm_epsilon) normal = glm::vec3(0.0f, 0.0f, 1.0f);

        hit->normal = normal;
        hit->backface = ray_starts_inside;
        
        return true;
    }

    return false;
}