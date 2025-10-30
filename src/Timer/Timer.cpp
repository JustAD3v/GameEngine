#include "Timer.h"
#include <SDL3/SDL.h>

Timer* Timer::s_Instance = nullptr;

void Timer::Tick() {
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS/1000.0f);

    if(m_DeltaTime > TARGET_DELTATIME) {
        m_DeltaTime = TARGET_DELTATIME;
    }
    m_LastTime = SDL_GetTicks();
    // SDL_Log("DeltaTime : %0.4f", m_DeltaTime);
}

void Timer::DestroyInstance() {
    if (s_Instance) {
        delete s_Instance;
        s_Instance = nullptr;
    }
}


