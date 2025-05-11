#include "../src/hit.h"

int main ()
{
    Hit* hit = new Hit();
    hit->t =  10.0f;
    hit->normal = glm::vec3(1.0f, 2.0f, 3.0f);
    hit->backface = true;
    hit->position = glm::vec3(0.0f, 1.0f, 2.0f);
    hit->isLight = true;
}