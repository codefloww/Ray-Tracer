//
// Created by paul on 3/8/23.
//

#include <iostream>
#include <chrono>
#include "../inc/app.hpp"


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
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
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
    while (isRunning) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
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
    auto start = std::chrono::high_resolution_clock::now();
    SDL_RenderClear(pRenderer);
    m_scene.Render(m_image);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "FPS: " << 1.0 / elapsed.count() << std::endl;
}

void Application::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}
