#include "camera.h"
#include "ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, 
               float fov, float distance, int width, int height)
    : eye(eye)
    , lookAt(lookAt)
    , up(up)
    , fov(fov)
    , distance(distance)
    , aspectRatio(static_cast<float>(width) / height)
{
    glm::vec3 w = glm::normalize(eye - lookAt);
    glm::vec3 u = glm::normalize(glm::cross(up, w));
    glm::vec3 v = glm::cross(w, u);
    
    viewMatrix = glm::lookAt(eye, lookAt, up);
    inverseViewMatrix = glm::inverse(viewMatrix);
}

Ray Camera::generateRay(float Xn, float Yn) const
{
    // Convert FOV from degrees to radians and divide by 2
    float fovRadians = glm::radians(fov) * 0.5f;
    
    // Calculate view plane dimensions at the focal distance
    float deltaV = distance * std::tan(fovRadians);
    float deltaU = deltaV * aspectRatio;
    
    // Calculate ray direction in camera space
    glm::vec4 p;
    p.x = -deltaU + 2.0f * deltaU * Xn;
    p.y = -deltaV + 2.0f * deltaV * Yn;
    p.z = -distance;
    p.w = 1.0f;
    
    glm::vec4 o = inverseViewMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 t = inverseViewMatrix * p;

    glm::vec3 rayOrigin = glm::vec3(o) / o.w;
    glm::vec3 rayDirection = glm::normalize(glm::vec3(t) / t.w - rayOrigin);

    return Ray(rayOrigin, rayDirection);
}