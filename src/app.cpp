//
// Created by paul on 3/8/23.
//

#include <iostream>
#include <chrono>
#include "../inc/app.hpp"

// set the kTimestep to 64ms which is roughly 30fps
//#define SHOW_FPS

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds kTimestep(40ms);

Application::Application() : is_running_m(true), window_m(nullptr), renderer_m(nullptr) {}

bool Application::onInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    window_m = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                                SDL_WINDOW_SHOWN);
    if (window_m == nullptr) {
        return false;
    }
    renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer_m == nullptr) {
        return false;
    }
    image_m.initialize(640, 480, renderer_m);
    SDL_SetRenderDrawColor(renderer_m, 100.0,100.0,100.0, 255.0);
    SDL_RenderClear(renderer_m);

    return true;
}

int Application::onExecute() {
    if (!onInit()) {
        return -1;
    }
    SDL_Event event;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds lag(0ns);
    auto last_time = clock::now();

    while (is_running_m) {
        auto current_time = clock::now();
        auto frame_time = current_time - last_time;
        last_time = current_time;
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(frame_time);

        // if there are visible delay between closing the window then that means that fps is lower than 30
        while (SDL_PollEvent(&event)) {
            onEvent(&event);
        }
#ifdef SHOW_FPS
        std::cout << "fps: " << 1.0 / (lag.count() / 1e9) << std::endl;
#endif
        while (lag >= kTimestep) {
            lag -= kTimestep;
            onLoop();
            onRender();
        }
    }
    onExit();
    return 0;
}

void Application::onEvent(const SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        is_running_m = false;
    }
}

void Application::onLoop() const {
    // do nothing for now
}

void Application::onRender() {
    SDL_RenderClear(renderer_m);
    scene_m.render(image_m);
    image_m.display();
    SDL_RenderPresent(renderer_m);
}

void Application::onExit() {
    SDL_DestroyRenderer(renderer_m);
    SDL_DestroyWindow(window_m);
    window_m = nullptr;
    SDL_Quit();
}
