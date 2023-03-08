//
// Created by paul on 3/8/23.
//

# include "../inc/app.hpp"

Application::Application() {
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool Application::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    pWindow = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (pWindow == nullptr) {
        return false;
    }
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == nullptr) {
        return false;
    }
    m_image.Initialize(640, 480, pRenderer);
    return true;
}

int Application::OnExecute() {
    if (OnInit() == false) {
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

void Application::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_QUIT) {
        isRunning = false;
    }
}

void Application::OnLoop() {
//    for (int y = 0; y < 480; y++) {
//        for (int x = 0; x < 640; x++) {
//            double r = rand() % 255;
//            double g = rand() % 255;
//            double b = rand() % 255;
//            double a = 255.0;
//            m_image.SetPixel(x, y, r, g, b, a);
//        }
//    }
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            double r = static_cast<double>(x) / 640.0 * 255.0;
            double g = static_cast<double>(y) / 480.0 * 255.0;
            double b = 0.2 * 255.0;
            double a = 255.0;
            m_image.SetPixel(x, y, r, g, b, a);
        }
    }
}

void Application::OnRender() {
    // set the background color to white
    SDL_RenderClear(pRenderer);
    m_image.Display();
    SDL_RenderPresent(pRenderer);
}

void Application::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}
