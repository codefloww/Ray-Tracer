//
// Created by paul on 3/8/23.
//

#include "app/image.hpp"
#include <algorithm>

Image::~Image() {
    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }

    delete[] pixels_m;
}

void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    width_m = width;
    height_m = height;
    renderer_m = renderer;

    bg_color_m = glm::vec3(0.0, 0.0, 0.0);

    pixels_m = new Uint32[width_m * height_m];

    initTexture();
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

void Image::setPixel(int x, int y, glm::vec3 color) const {
    auto index = y * width_m + x;
    pixels_m[index] = convertColor(color.r, color.g, color.b);
}

Uint32 Image::convertColor(float r, float g, float b) {
    if (r > 1.0) r = 1.0;
    if (g > 1.0) g = 1.0;
    if (b > 1.0) b = 1.0;

    auto red = static_cast<Uint8>(255 * r);
    auto blue = static_cast<Uint8>(255 * b);
    auto green = static_cast<Uint8>(255 * g);
    auto alpha = 0xFF000000;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    alpha = 0x000000FF;
    return red << 24 | (green << 16) | (blue << 8) | alpha;
#else
    return alpha | (blue << 16) | (green << 8) | red;
#endif
}

int Image::getWidth() const {
    return width_m;
}

int Image::getHeight() const {
    return height_m;
}

glm::vec3 Image::getBgColor() const {
    return bg_color_m;
}
