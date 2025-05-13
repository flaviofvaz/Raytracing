#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

// Forward declaration
class Scene;

class Light
{
    public:
        virtual ~Light() = default;
        virtual glm::vec3 radiance(const Scene* scene, const glm::vec3& point, glm::vec3* L) const = 0;
        virtual glm::vec3 getPower() const = 0;
};

class PointLight : public Light
{   
    private:
        glm::vec3 position;
        glm::vec3 power;

    public:
        PointLight(const glm::vec3& position, const glm::vec3& power);
        glm::vec3 radiance(const Scene* scene, const glm::vec3& point, glm::vec3* L) const override;
        glm::vec3 getPower() const override { return power; }
};
#endif 