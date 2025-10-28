#ifndef CAMERA_H
#define CAMERA_H

#include <Vector2D.h>
#include <SDL3/SDL.h>
#include "Engine.h"

class Camera {

    public:
        inline static Camera* GetInstance() {return s_Instance = (s_Instance != nullptr ? s_Instance : new Camera());}
        inline SDL_FRect GetViewBox() {return m_ViewBox;}
        inline Vector2D GetPosition() {return m_Position;}
        inline void SetTarget(Vector2D* target) {m_Target = target;}
        void Update(float dt);

    private:
        Camera() { m_Target = nullptr; m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }
        Vector2D* m_Target;
        Vector2D m_Position;

        SDL_FRect m_ViewBox;

        static Camera* s_Instance;
};

#endif