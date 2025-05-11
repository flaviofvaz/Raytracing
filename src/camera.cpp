#include "camera.h"
#include "ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float angle, float distance, float ratio, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    this->angle = angle;
    this->distance = distance;
    this->ratio = ratio; 
    this->eye = eye;
    this->center = center;
    this->up = up;
    viewMatrix = glm::lookAt(eye, center, up);
    inverseViewMatrix = glm::inverse(viewMatrix);
}

Ray Camera::generateRay(float Xn, float Yn)
{
    float deltaV, deltaU;
    glm::vec4 p, o4, t4, zero;
    glm::vec3 direction, normalized_direction, o, t;

    deltaV = this->distance * std::tan(this->angle / 2.0);
    deltaU = deltaV * this->ratio;

    p.x = -deltaU + 2 * deltaU * Xn;
    p.y = -deltaV + 2 * deltaV * Yn;
    p.z = -this->distance;
    p.w = 1;

    zero = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    o4 = this->inverseViewMatrix * zero;
    t4 = this->inverseViewMatrix * p;
    
    o = glm::vec3(o4) / o4.w;
    t = glm::vec3(t4) / t4.w;

    direction = t - o;
    normalized_direction = glm::normalize(direction);

    return Ray(&o, &normalized_direction);
}