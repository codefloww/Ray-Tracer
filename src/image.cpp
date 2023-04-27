//
// Created by paul on 3/8/23.
//

#include "image.hpp"

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

    initTexture();
}

void Image::setPixel(int x, int y, double r, double g, double b, double a) {
    r_channel_m[x][y] = r;
    g_channel_m[x][y] = g;
    b_channel_m[x][y] = b;
    a_channel_m[x][y] = a;
}

void Image::display() const {
    auto *temp_pixels = new Uint32[width_m * height_m];

    memset(temp_pixels, 0, width_m * height_m * sizeof(Uint32));

    for (int y = 0; y < height_m; y++) {
        for (int x = 0; x < width_m; x++) {
            temp_pixels[y * width_m + x] = convertColor(r_channel_m[x][y], g_channel_m[x][y], b_channel_m[x][y],
                                                        a_channel_m[x][y]);
        }
    }
    SDL_UpdateTexture(texture_m, nullptr, temp_pixels, width_m * sizeof(Uint32));

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
    r_mask = 0xff000000;
    g_mask = 0x00ff0000;
    b_mask = 0x0000ff00;
    a_mask = 0x000000ff;
#else
    r_mask = 0x000000ff;
    g_mask = 0x0000ff00;
    b_mask = 0x00ff0000;
    a_mask = 0xff000000;
#endif
    if (texture_m != nullptr) {
        SDL_DestroyTexture(texture_m);
    }
    SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, width_m, height_m, 32,
                                                     r_mask, g_mask, b_mask, a_mask);
    texture_m = SDL_CreateTextureFromSurface(renderer_m, temp_surface);
    SDL_FreeSurface(temp_surface);
}

Uint32 Image::convertColor(double r, double g, double b, double a) {
    Uint32 color = 0;
    auto r8 = static_cast<unsigned char>(r);
    auto g8 = static_cast<unsigned char>(g);
    auto b8 = static_cast<unsigned char>(b);
    auto a8 = static_cast<unsigned char>(a);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    color = (r8 << 24) + (g8 << 16) + (b8 << 8) + a8;
#else
    color = (a8 << 24) + (b8 << 16) + (g8 << 8) + r8;
#endif

    return color;
}

int Image::getWidth() const {
    return width_m;
}

int Image::getHeight() const {
    return height_m;
}

std::vector<double> Image::getPixelColor(int x, int y) const {
    return {r_channel_m[x][y], g_channel_m[x][y], b_channel_m[x][y], a_channel_m[x][y]};
}

glm::vec3 Image::getPixel(int x, int y) const {
    return {r_channel_m[x][y], g_channel_m[x][y], b_channel_m[x][y]};
}
