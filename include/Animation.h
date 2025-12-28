#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL3/SDL.h>
#include <iostream>

class Animation {
    public:
        Animation() {
            #ifdef DEBUG
            std::cout << "Animation constructor called ! \n";
            #endif
        };

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_FlipMode flip = SDL_FLIP_NONE);

    private:
        int m_SpriteRow;
        std::string m_TextureID;
        int m_FrameCount;
        int m_AnimSpeed;
        int m_SpriteFrame;
        SDL_FlipMode m_Flip;



};

#endif