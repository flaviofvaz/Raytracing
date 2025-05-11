#include "../src/light.h"
#include <glm/glm.hpp>

int main ()
{
    glm::vec3 L, position, power;

    position = glm::vec3(1.0f, 2.0f, 3.0f);
    power = glm::vec3(50.0f, 50.0f, 50.0f);
    Light light = Light();
    PointLight* pointLight = new PointLight(position, power);

    glm::vec3 c = pointLight->Radiance(position, L);
}