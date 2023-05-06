//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Image {
    int width_m = 0;
    int height_m = 0;

    SDL_Renderer *renderer_m = nullptr;
    SDL_Texture *texture_m = nullptr;

public:
    ~Image();

    Image() = default;

    Image(const Image &) = delete;

    Image &operator=(const Image &) = delete;

    Uint32 *pixels_m = nullptr;
    glm::vec3 bg_color_m{};

    void initialize(int width, int height, SDL_Renderer *renderer);

    void display();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    void setPixel(int x, int y, glm::vec3 color) const;

    [[nodiscard]] static Uint32 convertColor(float r, float g, float b);

    void initTexture();
};

#endif //RAY_TRACER_IMAGE_HPP
