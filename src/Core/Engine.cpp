#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

#include <iostream>
#include <SDL3/SDL.h>

Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;

bool Engine::Init() {

    m_IsRunning = false;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
    m_Window = SDL_CreateWindow("Engine", SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_Window == nullptr) {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, NULL);
    if (!m_Renderer) {
        SDL_Log("Failed to create Renderer : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void Engine::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_CurrentGame->OnUpdate(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 255, 236, 161, 255);
    SDL_RenderClear(m_Renderer);
    m_CurrentGame->OnRender();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}

void Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();   
}

void Engine::Quit() {
    m_IsRunning = false;
}

void Engine::Run(IGame* game) {
    if (!Init()) return;

    m_CurrentGame = game;
    m_CurrentGame->OnInit();
    m_IsRunning = true;
    //std::cout << "Running" << std::endl; 
    while (m_IsRunning) {
        Events();
        Update();
        Render();
        Timer::GetInstance()->Tick();
    }

    m_CurrentGame->OnClean();
    Clean();
}

