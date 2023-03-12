//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_APP_HPP
#define RAY_TRACER_APP_HPP

#include <SDL2/SDL.h>
#include "image.hpp"
#include "scene.hpp"

class Application {
private:
    Scene m_scene;
    Image m_image;
    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

public:
    Application();

    int OnExecute();

    bool OnInit();

    void OnEvent(const SDL_Event *Event);

    void OnLoop() const;

    void OnRender();

    void OnExit();

    ~Application() = default;

};

#endif //RAY_TRACER_APP_HPP
