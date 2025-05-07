#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>

class Shape
{
    Shape();
};

class Sphere : Shape
{
    float radius;
    glm::vec3 center;
};

class Place : Shape
{
    glm::vec3 position;
    glm::vec3 normal;
};

#endif