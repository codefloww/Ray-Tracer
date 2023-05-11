#ifndef RAY_TRACER_IMAGE_HPP
#define RAY_TRACER_IMAGE_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Image {
    Uint32 *pixels_m = nullptr;
    int width_m = 0;
    int height_m = 0;

    SDL_Renderer *renderer_m = nullptr;
    SDL_Texture *texture_m = nullptr;

public:
    Image() = default;

    Image(const Image&) = delete;

    Image& operator=(const Image&) = delete;

    ~Image();

    void initialize(int width, int height, SDL_Renderer *renderer);

    void initTexture();

    void setPixel(int x, int y, Uint32 color);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] Uint32 getPixel(int x, int y) const;

    void display();

    [[nodiscard]] static glm::vec3 convertColor(glm::vec3& color);

    [[nodiscard]] static Uint32 postProcess(glm::vec3 rgba);
};

#endif //RAY_TRACER_IMAGE_HPP
