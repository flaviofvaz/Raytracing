#ifndef INSTANCE_H
#define INSTANCE_H

#include "material.h"
#include "light.h"
#include "shape.h"
#include "hit.h"
#include "ray.h"

class Instance
{
    private:
        enum class InstanceType { LIGHT, MATERIAL };
        union 
        {
            Light* light;
            Material* material;
        };
        InstanceType type;
        Shape* shape;
    public:
        Instance(Material* m, Shape* shape)
        {
            this->material = m;
            type = InstanceType::MATERIAL;
            this->shape = shape;
        };

        Instance(Light* l, Shape* shape)
        {
            this->light = l;
            type = InstanceType::LIGHT;
            this->shape = shape;
        };

        ~Instance() 
        {
            if (type == InstanceType::LIGHT) {
                light->~Light();
            } else {
                material->~Material();
            }
            shape->~Shape();
        }

        bool isLight() {return this->type == InstanceType::LIGHT;};
        bool isMaterial() {return this->type == InstanceType::MATERIAL;};

        Hit* computeIntersection(Ray* ray);
};
#endif