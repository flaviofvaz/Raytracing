#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include "ray.h"
#include "hit.h"

class Shape
{
    public:
        virtual ~Shape() = default;
        virtual bool intersect(Ray* ray, Hit* hit) = 0;
};

class Sphere : Shape
{
    glm::vec3 center;
    float radius;
    public:
        Sphere(glm::vec3 center, float radius);
        bool intersect(Ray* ray, Hit* hit) override;
};

class Box : Shape
{
    glm::vec3 bMin;
    glm::vec3 bMax;
    public:
        Box(glm::vec3 bMin, glm::vec3 bMax);
        bool intersect(Ray* ray, Hit* hit) override;
};

class Plane : Shape
{
    glm::vec3 point;
    glm::vec3 normal;
    public:
        Plane(glm::vec3 point, glm::vec3 normal);
        bool intersect(Ray* ray, Hit* hit) override;
};
#endif