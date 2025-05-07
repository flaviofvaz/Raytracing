#ifndef FILM_H
#define FILM_H

#include <glm/glm.hpp>

class Film
{
    glm::vec2 resolution;
    glm::vec2 pixelSampler(int i, int j);
    glm::vec3 image;    
};
#endif