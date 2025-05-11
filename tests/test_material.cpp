#include "../src/material.h"
#include "../src/hit.h"

int main()
{
    Phong* material = new Phong();
    glm::vec3 c = material->Eval(new Hit(), glm::vec3(0.0f, 1.0f, 2.0f));
    printf("");
}