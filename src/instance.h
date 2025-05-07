#ifndef INSTANCE_H
#define INSTANCE_H

#include "material.h"
#include "shape.h"

class Instance
{
    Instance();
    Material material;
    Shape shape;
};
#endif