//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

extern double STANDART_MAX_COLOR;
extern float GAMMA;

class Image {
    std::vector<std::vector<double>> r_channel_m;
    std::vector<std::vector<double>> g_channel_m;
    std::vector<std::vector<double>> b_channel_m;
    std::vector<std::vector<double>> a_channel_m;
    int width_m = 0;
    int height_m = 0;

    double max_color_m = 0.0;
    double min_exposure_m = 0.0;

    SDL_Renderer *renderer_m = nullptr;
    SDL_Texture *texture_m = nullptr;

public:
    ~Image();

    void initialize(int width, int height, SDL_Renderer *renderer);

    void setPixel(int x, int y, double r, double g, double b, double a);

    [[nodiscard]] glm::vec4 getPixel(int x, int y) const;

    void display();

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] glm::vec4 convertColor(double r, double g, double b, double a) const;

    void initTexture();

    void computeMaxValues();

    static Uint32 postProcess(glm::vec4 rgba);
};

#endif //RAY_TRACER_IMAGE_HPP
