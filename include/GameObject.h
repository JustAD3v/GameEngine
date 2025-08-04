#ifndef GAEMOBJECT_H
#define GAEMOBJECT_H

#include "IObject.h"
#include "Transform.h"

//#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <string>

struct Properties {
    public: // "public" pas nécessaire car tout est public par défaut dans une struct
        float x, y;
        int Width, Height;
        std::string textureID;
        SDL_FlipMode Flip;

        Properties(std::string TextureID, int X, int Y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE) {
            x = X;
            y = Y;
            Flip = flip;
            Width = width;
            Height = height;
            textureID = TextureID; 
        }
};

class GameObject : public IObject {
    public:
        GameObject(Properties* props) : m_TextureID(props->textureID), m_Flip(props->Flip), m_Height(props->Height), m_Width(props->Width) {
            m_Transform = new Transform(props->x, props->y);
        };

        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
    
        protected:
            Transform* m_Transform;
            int m_Width, m_Height;
            std::string m_TextureID;
            SDL_FlipMode m_Flip;
};

#endif