//
// Created by paul on 3/8/23.
//

#include "app/image.hpp"
#include <algorithm>
#include <iostream>

constexpr float STANDARD_MAX_COLOR = 0.05f;
//constexpr float GAMMA = 2.2;

Image::~Image() {
    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }

    delete[] pixels_m;
}

void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    width_m = width;
    height_m = height;

    pixels_m = new Uint32[width_m * height_m];

    renderer_m = renderer;
    max_color_m = STANDARD_MAX_COLOR;

    initTexture();
}

void Image::setPixel(int x, int y, Uint32 color) {
    pixels_m[y * width_m + x] = color;
}

Uint32 Image::getPixel(int x, int y) const {
    return pixels_m[y * width_m + x];
}

void Image::display() {
    auto uint32_size = static_cast<int>(sizeof(Uint32));
    SDL_UpdateTexture(texture_m, nullptr, pixels_m, width_m * uint32_size);
    SDL_RenderCopy(renderer_m, texture_m, nullptr, nullptr);
}

void Image::initTexture() {
    Uint32 r_mask, g_mask, b_mask, a_mask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    r_mask = 0xFF000000;
    g_mask = 0x00FF0000;
    b_mask = 0x0000FF00;
    a_mask = 0x000000FF;
#else
    r_mask = 0x000000FF;
    g_mask = 0x0000FF00;
    b_mask = 0x00FF0000;
    a_mask = 0xFF000000;
#endif

    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }
    SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, width_m, height_m, 32,
                                                     r_mask, g_mask, b_mask, a_mask);

    texture_m = SDL_CreateTextureFromSurface(renderer_m, temp_surface);
    SDL_FreeSurface(temp_surface);
}

glm::vec3 Image::convertColor(glm::vec3& color) const {

    color.r = color.r / max_color_m;
    color.g = color.g / max_color_m;
    color.b = color.b / max_color_m;

    // Still there is god know why a possibility that the color is greater than 1.0f
    if (color.r > 1.0f) {
        color.r = 1.0f;
    }
    if (color.g > 1.0f) {
        color.g = 1.0f;
    }
    if (color.b > 1.0f) {
        color.b = 1.0f;
    }
    return {color.r, color.g, color.b};
}

int Image::getWidth() const {
    return width_m;
}

int Image::getHeight() const {
    return height_m;
}

Uint32 Image::postProcess(glm::vec4&& rgba) {
    Uint8 red = rgba.r * 255;
    Uint8 green = rgba.g * 255;
    Uint8 blue = rgba.b * 255;
    Uint8 alpha = rgba.a * 255;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    return red << 24 | (green << 16) | (blue << 8) | alpha;
#else
    return (alpha << 24) | (blue << 16) | (green << 8) | red;
#endif
}