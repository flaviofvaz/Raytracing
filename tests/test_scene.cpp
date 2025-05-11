#include "scene.h"
#include "../src/hit.h"
#include "../src/ray.h"
#include "../src/shape.h"
#include "../src/light.h"
#include <glm/glm.hpp>

int main ()
{
    Scene scene = Scene();
    glm::vec3 origin, direction, c, lightPosition;

    lightPosition = glm::vec3(1.0f, 2.0f, 3.0f);
    PointLight* lightSource = new PointLight(lightPosition, 50.0f);
    Sphere* sphere = new Sphere(glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);

    // create ray
    origin = glm::vec3(1.0f, 2.0f, 3.0f);
    direction = glm::vec3(4.0f, 5.0f, 6.0f);
    Ray ray = Ray(origin, direction); 

    // add a light source
    scene.AddLight(&lightSource);

    // add an object
    scene.AddObjects(&sphere);

    // test compute intersection
    Hit* hit = scene.ComputeIntersection(ray);

    // test trace ray
    // c = scene.TraceRay(ray);
}