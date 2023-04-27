//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_APP_HPP
#define RAY_TRACER_APP_HPP

#include <SDL2/SDL.h>
#include "image.hpp"
#include "scene.hpp"

class Application {
    Scene scene_m;
    Image image_m;
    bool is_running_m;
    SDL_Window *window_m;
    SDL_Renderer *renderer_m;

public:
    Application();

    int onExecute();

    bool onInit();

    void onEvent(const SDL_Event *event);

    void onLoop() const;

    void onRender();

    void onExit();
};

#endif //RAY_TRACER_APP_HPP
