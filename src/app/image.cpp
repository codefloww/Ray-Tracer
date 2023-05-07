//
// Created by paul on 3/8/23.
//

#include "app/image.hpp"
#include <algorithm>
#include <iostream>

constexpr float STANDARD_MAX_COLOR = 0.05;
constexpr float GAMMA = 2.2;

Image::~Image() {
    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }
    delete m_pixels;

}

void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    width_m = width;
    height_m = height;

    m_pixels = new Uint32[width_m * height_m];
    memset(m_pixels, 0, width_m * height_m * sizeof(Uint32));

    renderer_m = renderer;

    min_exposure_m = 1.0;

    auto uint32_size = static_cast<int>(sizeof(Uint32));
    m_pitch = width_m * uint32_size;

    initTexture();
}

void Image::setPixel(int x, int y, Uint32 color) {
    m_pixels[y * width_m + x] = color;
}

Uint32 Image::getPixel(int x, int y) const {
    return m_pixels[y * width_m + x];
}

void Image::display() {
    SDL_UpdateTexture(texture_m, nullptr, m_pixels, m_pitch);

    SDL_Rect src_rect;
    SDL_Rect bounds;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = width_m;
    src_rect.h = height_m;
    bounds = src_rect;
    SDL_RenderCopy(renderer_m, texture_m, &src_rect, &bounds);
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

glm::vec4 Image::convertColor(glm::vec4 color) const {
    return {(color.r / max_color_m), (color.g / max_color_m), (color.b / max_color_m), color.a};
}

int Image::getWidth() const {
    return width_m;
}

int Image::getHeight() const {
    return height_m;
}

void Image::resetColor(){
    max_color_m = STANDARD_MAX_COLOR;
}

Uint32 Image::postProcess(glm::vec4 rgba) {
    auto corrected_rgba = rgba; //TODO: optimize and turn it on: glm::pow(rgba, glm::vec4{1.0f/GAMMA, 1.0f/GAMMA, 1.0f/GAMMA, 1.0f}); // rgba is in [0, 1]
    Uint8 red = corrected_rgba.r * 255; // so corrected_rgba as well
    Uint8 green = corrected_rgba.g * 255;
    Uint8 blue = corrected_rgba.b * 255;
    Uint8 alpha = corrected_rgba.a * 255;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    return red << 24 | (green << 16) | (blue << 8) | alpha;
#else
    return alpha << 24 | (blue << 16) | (green << 8) | red;
#endif
}