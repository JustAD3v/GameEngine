#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

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