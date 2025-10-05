#ifndef GAEMOBJECT_H
#define GAEMOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "GameObjectCollider.h"
#include "BoxCollider.h"

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
            float px = props->x + props->Width/2;
            float py = props->y + props->Height/2;
            m_Origin = new Vector2D(px, py);
        };

        template<typename ColliderType, typename... Args>
        void AddCollider(Args&&... args) {
            if (m_Collider) {
                delete m_Collider;
            }
            m_Collider = new ColliderType(std::forward<Args>(args)...); //work on it later to understand it better
        }

        inline Vector2D* GetOrigin() {return m_Origin;}

        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
    
        protected:
            Vector2D* m_Origin; //represent the center of the GameObject
            Transform* m_Transform;
            GameObjectCollider* m_Collider = nullptr;
            int m_Width, m_Height;
            std::string m_TextureID;
            SDL_FlipMode m_Flip;
};

#endif