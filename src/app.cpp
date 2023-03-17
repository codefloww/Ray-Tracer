//
// Created by paul on 3/8/23.
//

#include <iostream>
#include <chrono>
#include "../inc/app.hpp"

// set the timestep to 64ms which is roughly 30fps
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(64ms);

Application::Application() {
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool Application::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    pWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                               SDL_WINDOW_SHOWN);
    if (pWindow == nullptr) {
        return false;
    }
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    if (pRenderer == nullptr) {
        return false;
    }
    m_image.Initialize(640, 480, pRenderer);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    return true;
}

int Application::OnExecute() {
    if (!OnInit()) {
        return -1;
    }
    SDL_Event Event;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds lag(0ns);
    auto last_time = clock::now();

    while (isRunning) {
        auto current_time = clock::now();
        auto frame_time = current_time - last_time;
        last_time = current_time;
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(frame_time);

        // if there are visible delay between closing the window then that means that fps is lower than 30
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        while (lag >= timestep) {
            lag -= timestep;
            OnLoop();
            OnRender();
        }

    }
    OnExit();
    return 0;
}

void Application::OnEvent(const SDL_Event *Event) {
    if (Event->type == SDL_QUIT) {
        isRunning = false;
    }
}

void Application::OnLoop() const {
    // do nothing for now
}

void Application::OnRender() {
    SDL_RenderClear(pRenderer);
    m_scene.Render(m_image);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
}

void Application::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}
