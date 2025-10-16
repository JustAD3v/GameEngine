#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameMap.h"
#include "IGame.h"


#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define LEVEL_WIDTH 960*2
#define LEVEL_HEIGHT 640

class Engine {
    public: 
        static Engine* GetInstance() {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }

        void Run(IGame* game);
        void Quit();
        
        inline bool isRunning(){return m_IsRunning;};
        inline SDL_Renderer* GetRenderer() {return m_Renderer;};

    private:
        Engine() {};

        bool Init();
        void Clean();
        void Update();
        void Render();
        void Events();

        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        IGame* m_CurrentGame = nullptr;
        static Engine* s_Instance;
};

#endif