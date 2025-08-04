#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>


class Input {
    public:
        static Input* GetInstance() {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);


    private:
        Input();
        void KeyUp();
        void KeyDown();

        const bool* m_KeyStates;
        static Input* s_Instance;
};

#endif
