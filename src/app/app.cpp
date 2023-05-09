//
// Created by paul on 3/8/23.
//

#include <iostream>
#include "app/app.hpp"

//#define CAP_FPS
#define SHOW_FPS

constexpr float kFpsCap = 30.0f;
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
    renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_ACCELERATED);
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
            if (event.type == SDL_QUIT) {
                is_running_m = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                is_running_m = false;
            }
        }

        onEvent();
        onRender();
#ifdef CAP_FPS
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = static_cast<float>(end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
        if (elapsed < 1.0f / kFpsCap) {
            SDL_Delay(static_cast<Uint32>((1.0f / kFpsCap - elapsed) * 1000.0f));
        }
#endif // CAP_FPS

#ifdef SHOW_FPS
        Uint64 end_for_counter = SDL_GetPerformanceCounter();
        float elapsed_for_counter =
                static_cast<float>(end_for_counter - start) / static_cast<float>(SDL_GetPerformanceFrequency());
        std::cout << "FPS:" << std::to_string(1.0f / elapsed_for_counter) << std::endl;
        scene_m.update_time_m = elapsed_for_counter;
#endif // SHOW_FPS
    }

    onExit();
    return 0;
}

void Application::onEvent() {
    auto *keyboard_state = SDL_GetKeyboardState(nullptr);

    if (keyboard_state[SDL_SCANCODE_W]) {
        scene_m.moveCamera(Scene::CameraMovement::FORWARD);
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        scene_m.moveCamera(Scene::CameraMovement::BACKWARD);
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        scene_m.moveCamera(Scene::CameraMovement::LEFT);
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        scene_m.moveCamera(Scene::CameraMovement::RIGHT);
    }
    if (keyboard_state[SDL_SCANCODE_Q]) {
        scene_m.moveCamera(Scene::CameraMovement::DOWN);
    }
    if (keyboard_state[SDL_SCANCODE_E]) {
        scene_m.moveCamera(Scene::CameraMovement::UP);
    }

    if (keyboard_state[SDL_SCANCODE_UP]) {
        scene_m.rotateCamera(Scene::CameraRotation::UP);
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        scene_m.rotateCamera(Scene::CameraRotation::DOWN);
    }
    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        scene_m.rotateCamera(Scene::CameraRotation::LEFT);
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        scene_m.rotateCamera(Scene::CameraRotation::RIGHT);
    }
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
