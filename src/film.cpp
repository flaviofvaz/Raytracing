#include "film.h"
#include <glm/glm.hpp>

Film::Film(glm::ivec2 resolution)
{
    this->resolution = resolution;
    this->image.resize(resolution.x * resolution.y, glm::vec3(0.0f, 0.0f, 0.0f)); // initialize image with black
}

glm::vec2 Film::pixelSampler(int i, int j)
{
    float Xn, Yn;
    glm::vec2 pixel;
    
    // Sample center of the pixel
    Xn = (static_cast<float>(i) + 0.5f) / static_cast<float>(this->resolution.x);
    Yn = (static_cast<float>(j) + 0.5f) / static_cast<float>(this->resolution.y);

    // Create pixel vector
    pixel = glm::vec2(Xn, Yn);
    return pixel;
}

int Film::getHeight()
{
    return this->resolution.y;
}

int Film::getWidth()
{
    return this->resolution.x;
}

void Film::setValue(int i, int j, glm::vec3 pixelColor)
{
    int index = j * this->resolution.x + i;
    this->image[index] = pixelColor;
}