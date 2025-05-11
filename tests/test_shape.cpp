#include "../src/shape.h"
#include <glm/glm.hpp>

int main ()
{
    bool intersect;
    Ray ray = Ray(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(4.0f, 5.0f, 6.0f)); 
    Hit hit = Hit();
    Plane* plane = new Plane(glm::vec3(1.0f, 2.0f, 3.0f), glm::vec3(2.0f, 3.0f, 4.5f));
    Sphere* sphere = new Sphere(glm::vec3(1.0f, 2.0f, 3.0f), 4.0f);
    
    intersect = plane->Intersect(ray, hit);
    intersect = sphere->Intersect(ray, hit);
}