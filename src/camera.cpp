#include "camera.h"
#include "ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float angle, float distance, float ratio, glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    angle = angle;
    distance = distance;
    ratio = ratio; 
    eye = eye;
    center = center;
    up = up;
    viewMatrix = glm::lookAt(eye, center, up);
    inverseViewMatrix = glm::inverse(viewMatrix);
}

Ray Camera::GenerateRay(float Xn, float Yn)
{
    float deltaV, deltaU;
    glm::vec4 p, o, t, zero;
    glm::vec3 direction;

    deltaV = this->distance * std::tan(this->angle / 2.0);
    deltaU = deltaV * this->ratio;

    p.x = -deltaU + 2 * deltaU * Xn;
    p.y = -deltaV + 2 * deltaV * Yn;
    p.z = -this->distance;
    p.w = 1;

    zero = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    o = this->inverseViewMatrix * zero;
    t = this->inverseViewMatrix * p;
    
    direction = t - o;

    return Ray(o, glm::normalize(direction));
}