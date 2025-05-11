#include "../src/camera.h"
#include "../src/ray.h"

#define PI 3.14159265359f

int main()
{
    float Xn, Yn, angle, distance, ratio;
    glm::vec3 eye, center, up;
    
    Xn = 3.0f;
    Yn = 4.0f;
    angle = PI / 3.6f;
    distance = 2.0f;
    ratio = 800.0f / 600.0f;

    eye = glm::vec3(1.0f, 2.0f, 3.0f);
    center = glm::vec3(4.0f, 5.0f, 6.0f);
    up = glm::vec3(7.0f, 8.0f, 9.0f);
    
    Camera* cam = new Camera(angle, distance, ratio, eye, center, up);
    Ray ray = cam->GenerateRay(Xn, Yn);
    return 0;
}