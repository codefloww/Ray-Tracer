//
// Created by paul on 3/8/23.
//

#include "../inc/image.hpp"

Image::Image() {
    m_width = 0;
    m_height = 0;
    m_pRenderer = nullptr;
    m_pTexture = nullptr;
}

Image::~Image() {
    if (m_pTexture != nullptr) {
        SDL_DestroyTexture(m_pTexture);
    }
}

void Image::Initialize(int width, int height, SDL_Renderer *pRenderer) {
    m_rChannel.resize(width, std::vector<double>(height, 0.0));
    m_gChannel.resize(width, std::vector<double>(height, 0.0));
    m_bChannel.resize(width, std::vector<double>(height, 0.0));
    m_aChannel.resize(width, std::vector<double>(height, 0.0));

    m_width = width;
    m_height = height;
    m_pRenderer = pRenderer;

    InitTexture();
}

void Image::SetPixel(int x, int y, double r, double g, double b, double a) {
    m_rChannel[x][y] = r;
    m_gChannel[x][y] = g;
    m_bChannel[x][y] = b;
    m_aChannel[x][y] = a;
}

void Image::Display() const {
    auto *tempPixels = new Uint32[m_width * m_height];

    memset(tempPixels, 0, m_width * m_height * sizeof(Uint32));

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            tempPixels[y * m_width + x] = ConvertColor(m_rChannel[x][y], m_gChannel[x][y], m_bChannel[x][y],
                                                       m_aChannel[x][y]);
        }
    }
    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_width * sizeof(Uint32));

    delete[] tempPixels;

    SDL_Rect srcRect;
    SDL_Rect bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_width;
    srcRect.h = m_height;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

void Image::InitTexture() {
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    if (m_pTexture != nullptr) {
        SDL_DestroyTexture(m_pTexture);
    }
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_width, m_height, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(double r, double g, double b, double a) const {
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

int Image::GetWidth() const {
    return m_width;
}

int Image::GetHeight() const {
    return m_height;
}

std::vector<double> Image::GetPixel(int x, int y) const {
    std::vector<double> pixel;
    pixel.push_back(m_rChannel[x][y]);
    pixel.push_back(m_gChannel[x][y]);
    pixel.push_back(m_bChannel[x][y]);
    pixel.push_back(m_aChannel[x][y]);
    return pixel;
}
