#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameMap.h"


#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define LEVEL_WIDTH 960*2
#define LEVEL_HEIGHT 640

class Engine {
    public: 
        static Engine* GetInstance() {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        void Init();
        void Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool isRunning(){return m_IsRunning;};
        inline SDL_Renderer* GetRenderer() {return m_Renderer;};

    private:
        Engine() {};
        bool m_IsRunning;

        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
};

#endif

/*
// Engine.h
#pragma once
#include <SDL3/SDL.h>
#include "Timer.h"
#include "IGame.h"

class Engine {
public:
    static Engine* GetInstance();
    void Run(IGame* game);

private:
    Engine() = default;
    bool Init();
    void Events();
    void Update();
    void Render();
    void Clean();

    bool m_IsRunning = false;
    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    IGame* m_CurrentGame = nullptr;
};
*/