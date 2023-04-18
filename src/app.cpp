//
// Created by paul on 3/8/23.
//

#include <iostream>
#include "app.hpp"

#define CAP_FPS
#define SHOW_FPS

constexpr float kTimeStep = 100.0f;
constexpr int kWidth = 640;
constexpr int kHeight = 480;

Application::Application() : is_running_m(true), window_m(nullptr), renderer_m(nullptr) {}

bool Application::onInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    window_m = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWidth, kHeight,
                                SDL_WINDOW_SHOWN);
    if (window_m == nullptr) {
        return false;
    }
    renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer_m == nullptr) {
        return false;
    }
    image_m.initialize(kWidth, kHeight, renderer_m);
    SDL_SetRenderDrawColor(renderer_m, 100.0, 100.0, 100.0, 255.0);
    SDL_RenderClear(renderer_m);

    return true;
}

int Application::onExecute() {
    if (!onInit()) {
        return -1;
    }
    SDL_Event event;

    while (is_running_m) {

        Uint64 start = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event)) {
            onEvent(&event);
        }
        onLoop();
        onRender();
#ifdef CAP_FPS
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = static_cast<float>(end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
        if (elapsed < 1.0f / kTimeStep) {
            SDL_Delay(static_cast<Uint32>((1.0f / kTimeStep - elapsed) * 1000.0f));
        }
#endif // CAP_FPS

#ifdef SHOW_FPS
        Uint64 end_for_counter = SDL_GetPerformanceCounter();
        float elapsed_for_counter =
                static_cast<float>(end_for_counter - start) / static_cast<float>(SDL_GetPerformanceFrequency());
        std::cout << "FPS:" << std::to_string(1.0f / elapsed_for_counter) << std::endl;
#endif // SHOW_FPS
    }

    onExit();
    return 0;
}

void Application::onEvent(const SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        is_running_m = false;
    } else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_j:
                scene_m.moveCamera(Scene::CameraMovement::DOWN);
                break;
            case SDLK_k:
                scene_m.moveCamera(Scene::CameraMovement::UP);
                break;
            case SDLK_h:
                scene_m.moveCamera(Scene::CameraMovement::LEFT);
                break;
            case SDLK_l:
                scene_m.moveCamera(Scene::CameraMovement::RIGHT);
                break;
            case SDLK_u:
                scene_m.moveCamera(Scene::CameraMovement::FORWARD);
                break;
            case SDLK_i:
                scene_m.moveCamera(Scene::CameraMovement::BACKWARD);
                break;
            case SDLK_w:
                scene_m.rotateCamera(glm::vec2(0.0f, 0.05f));
                break;
            case SDLK_s:
                scene_m.rotateCamera(glm::vec2(0.0f, -0.05f));
                break;
            case SDLK_a:
                scene_m.rotateCamera(glm::vec2(0.05f, 0.0f));
                break;
            case SDLK_d:
                scene_m.rotateCamera(glm::vec2(-0.05f, 0.0f));
                break;

            default:
                break;
        }
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
