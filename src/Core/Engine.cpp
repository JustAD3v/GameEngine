#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

#include "Warrior.h"

#include <iostream>
#include <SDL3/SDL.h>

Engine* Engine::s_Instance = nullptr;
TextureManager* TextureManager::s_Instance = nullptr;
Warrior* player = nullptr;

void Engine::Init() {

    m_IsRunning = false;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
    m_Window = SDL_CreateWindow("Engine", SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_Window == nullptr) {
        SDL_Log("Failed to create window : %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, NULL);
    if (!m_Renderer) {
        SDL_Log("Failed to create Renderer : %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    if(!MapParser::GetInstance()->Load("level1", "/Users/colin/Code/GameEngine/assets/maps/level1.tmj")) {
        std::cout << "Failed to load map" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    TextureManager::GetInstance()->Load("playerIdle", "/Users/colin/Code/GameEngine/assets/player/Idle32.png");
    TextureManager::GetInstance()->Load("playerRun", "/Users/colin/Code/GameEngine/assets/player/Run32.png");
    
    player = new Warrior(new Properties("playerRun", SCREEN_WIDTH/2, 0, 32, 32));
    player->AddCollider<class BoxCollider>(player->GetOrigin(), 32, 32);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    m_IsRunning = true;
}

void Engine::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 255, 236, 161, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap->Render();
    player->Draw();
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

