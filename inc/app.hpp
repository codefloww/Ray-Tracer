//
// Created by paul on 3/8/23.
//

#ifndef RAY_TRACER_APP_HPP
#define RAY_TRACER_APP_HPP

#include <SDL2/SDL.h>
#include "image.hpp"

class Application {
public:
    Application();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnExit();
    ~Application() = default;
private:
    Image m_image;
    // SDL2 stuff
    bool isRunning;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
};
#endif //RAY_TRACER_APP_HPP
