#include "../src/ray.h"

int main()
{
    glm::vec3 origin, direction;

    origin = glm::vec3(1.0f, 2.0f, 3.0f);
    direction = glm::vec3(4.0f, 5.0f, 6.0f);

    Ray ray = Ray(origin, direction); 
    return 0;
}