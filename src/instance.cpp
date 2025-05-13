#include "instance.h"

Instance::Instance(std::unique_ptr<Shape> shape)
    : type(InstanceType::NONE)
    , shape(std::move(shape))
{
}

Instance::~Instance()
{
    // No need to delete pointers as they are owned by the Scene
    light = nullptr;
    material = nullptr;
}

Instance::Instance(Instance&& other) noexcept
    : type(other.type)
    , shape(std::move(other.shape))
{
    if (type == InstanceType::LIGHT) {
        light = other.light;
        other.light = nullptr;
    } else if (type == InstanceType::MATERIAL) {
        material = other.material;
        other.material = nullptr;
    }
    other.type = InstanceType::NONE;
}

Instance& Instance::operator=(Instance&& other) noexcept
{
    if (this != &other) {
        // Clean up current state
        if (type == InstanceType::LIGHT) {
            light = nullptr;
        } else if (type == InstanceType::MATERIAL) {
            material = nullptr;
        }

        // Move from other
        type = other.type;
        shape = std::move(other.shape);
        
        if (type == InstanceType::LIGHT) {
            light = other.light;
            other.light = nullptr;
        } else if (type == InstanceType::MATERIAL) {
            material = other.material;
            other.material = nullptr;
        }
        other.type = InstanceType::NONE;
    }
    return *this;
}

void Instance::setMaterial(Material* material)
{
    if (type == InstanceType::LIGHT) {
        light = nullptr;
    }
    this->material = material;
    type = material ? InstanceType::MATERIAL : InstanceType::NONE;
}

void Instance::setLight(Light* light)
{
    if (type == InstanceType::MATERIAL) {
        material = nullptr;
    }
    this->light = light;
    type = light ? InstanceType::LIGHT : InstanceType::NONE;
}

std::unique_ptr<Hit> Instance::computeIntersection(const Ray& ray) const
{
    if (!shape) {
        return nullptr;
    }

    auto hit = std::make_unique<Hit>();
    if (shape->intersect(ray, hit.get())) {
        if (type == InstanceType::LIGHT) {
            hit->setLight(light);
        } else if (type == InstanceType::MATERIAL) {
            hit->setMaterial(material);
        }
        return hit;
    }
    return nullptr;
}