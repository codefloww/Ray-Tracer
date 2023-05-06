//
// Created by paul on 3/8/23.
//

#include "app/image.hpp"
#include <algorithm>
#include <iostream>

double STANDART_MAX_COLOR = 0.05;
float GAMMA = 2.2;

Image::~Image() {
    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }
}

void Image::initialize(int width, int height, SDL_Renderer *renderer) {
    r_channel_m.resize(width, std::vector<double>(height, 0.0));
    g_channel_m.resize(width, std::vector<double>(height, 0.0));
    b_channel_m.resize(width, std::vector<double>(height, 0.0));
    a_channel_m.resize(width, std::vector<double>(height, 0.0));

    width_m = width;
    height_m = height;
    renderer_m = renderer;

    min_exposure_m = 1.0;

    initTexture();
}

void Image::setPixel(int x, int y, double r, double g, double b, double a) {
    r_channel_m[x][y] = r;
    g_channel_m[x][y] = g;
    b_channel_m[x][y] = b;
    a_channel_m[x][y] = a;
}

glm::vec4 Image::getPixel(int x, int y) const {
    return {r_channel_m[x][y], g_channel_m[x][y], b_channel_m[x][y], a_channel_m[x][y]};
}

void Image::display() {
    computeMaxValues();
    auto *temp_pixels = new Uint32[width_m * height_m];

    memset(temp_pixels, 0, width_m * height_m * sizeof(Uint32));

    for (int y = 0; y < height_m; y++) {
        for (int x = 0; x < width_m; x++) {
            temp_pixels[y * width_m + x] = postProcess(convertColor(r_channel_m[x][y],
                                                        g_channel_m[x][y],
                                                        b_channel_m[x][y],
                                                        a_channel_m[x][y]));
        }
    }

    auto uint32_size = static_cast<int>(sizeof(Uint32));
    SDL_UpdateTexture(texture_m, nullptr, temp_pixels, width_m * uint32_size);

    delete[] temp_pixels;

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

glm::vec4 Image::convertColor(double r, double g, double b, double a) const {
    auto red = (r / max_color_m);
    auto green = (g / max_color_m);
    auto blue = (b / max_color_m);

    return {red, green, blue, a};
}

int Image::getWidth() const {
    return width_m;
}

int Image::getHeight() const {
    return height_m;
}

void Image::computeMaxValues() {
    double max_red = 0.0;
    double max_green = 0.0;
    double max_blue = 0.0;
    for (int x = 0; x < width_m; x++) {
        for (int y = 0; y < height_m; y++) {
            max_red = std::max(max_red, r_channel_m[x][y]);
            max_green = std::max(max_green, g_channel_m[x][y]);
            max_blue = std::max(max_blue, b_channel_m[x][y]);
        }
    }

    double max_color = std::max({max_red, max_green, max_blue, STANDART_MAX_COLOR});

    //std::cout << max_color << std::endl;
//    if (max_color < min_exposure_m) {
//        return;
//    }
    max_color_m = max_color;
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