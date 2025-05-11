#include "../src/film.h"

int main()
{
    glm::ivec2 resolution;
    glm::vec2 selectedPixel;
    float widht, height;
    int i, j;

    i = 35;
    j = 22;

    resolution = glm::ivec2(800, 600);
    Film film = Film(resolution);
    selectedPixel = film.PixelSampler(i, j);

    widht = film.GetWidth();
    height = film.GetHeight();
    return 0;
}