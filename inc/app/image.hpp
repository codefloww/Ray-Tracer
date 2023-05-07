//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

extern const float STANDARD_MAX_COLOR;
extern const float GAMMA;

class Image {
    Uint32 *m_pixels = nullptr;
    int width_m = 0;
    int height_m = 0;
    int m_pitch = 0;

    double min_exposure_m = 0.0;

    SDL_Renderer *renderer_m = nullptr;
    SDL_Texture *texture_m = nullptr;

public:
    float max_color_m = 0.0;

    ~Image();

    void initialize(int width, int height, SDL_Renderer *renderer);

    void setPixel(int x, int y, Uint32 color);

    [[nodiscard]] Uint32 getPixel(int x, int y) const;

    void display();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] glm::vec4 convertColor(glm::vec4 color) const;

    void initTexture();

    void resetColor();

    static Uint32 postProcess(glm::vec4 rgba);
};

#endif //RAY_TRACER_IMAGE_HPP
