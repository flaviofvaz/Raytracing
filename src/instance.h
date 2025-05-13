#ifndef INSTANCE_H
#define INSTANCE_H

#include "material.h"
#include "light.h"
#include "shape.h"
#include "hit.h"
#include "ray.h"
#include <memory>

class Instance
{
    private:
        enum class InstanceType { NONE, LIGHT, MATERIAL };
        union 
        {
            Light* light;
            Material* material;
        };
        InstanceType type;
        std::unique_ptr<Shape> shape;

    public:
        Instance(std::unique_ptr<Shape> shape);
        ~Instance();

        // Prevent copying
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        // Allow moving
        Instance(Instance&& other) noexcept;
        Instance& operator=(Instance&& other) noexcept;

        void setMaterial(Material* material);
        void setLight(Light* light);

        bool isLight() const { return type == InstanceType::LIGHT; }
        bool isMaterial() const { return type == InstanceType::MATERIAL; }
        Light* getLight() const { return type == InstanceType::LIGHT ? light : nullptr; }
        Material* getMaterial() const { return type == InstanceType::MATERIAL ? material : nullptr; }
        const Shape* getShape() const { return shape.get(); }

        std::unique_ptr<Hit> computeIntersection(const Ray& ray) const;
};
#endif