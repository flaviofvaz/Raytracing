#ifndef HIT_H
#define HIT_H

#include<glm/glm.hpp>
#include "light.h"
#include "material.h"

class Hit
{
    private:
        enum class InstanceType { LIGHT, MATERIAL };
        union 
        {
            Light* light;
            Material* material;
        };
        InstanceType type;
    public:
        Hit(){};
        Hit(int t, glm::vec3 position, glm::vec3 normal, bool backface);
        bool backface;
        int t;
        glm::vec3 position;
        glm::vec3 normal;

        ~Hit() 
        {
            if (type == InstanceType::LIGHT) {
                light->~Light();
            } else {
                material->~Material();
            }
        }

        bool isLight() {return this->type == InstanceType::LIGHT;};
        bool isMaterial() {return this->type == InstanceType::MATERIAL;};
        Light* getLight() { return light; }
        Material* getMaterial() { return material; }
        void setMaterial(Material* material) { this->material = material; };
        void setLight(Light* light) { this->light = light; };

};
#endif