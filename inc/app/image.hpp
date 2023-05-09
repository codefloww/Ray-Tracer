#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Image {
    Uint32 *pixels_m;
    int width_m = 0;
    int height_m = 0;

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

    [[nodiscard]] glm::vec3 convertColor(glm::vec3& color) const;

    void initTexture();

    static Uint32 postProcess(glm::vec4&& rgba); // because we pass rvalue (constructed glm::vec4 in internalRender)
};

#endif //RAY_TRACER_IMAGE_HPP
