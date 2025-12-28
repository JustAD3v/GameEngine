#ifndef GAEMOBJECT_H
#define GAEMOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "GameObjectCollider.h"
#include "BoxCollider.h"
#include "RigidBody.h"

//#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <string>

//forward declaration to avoid circular inclusion with Scene.h
class Scene;

struct Properties {
    public: // "public" not necessary because struct is public by default
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
            #ifdef DEBUG
            std::cout << "Properties constructor : textureID='" << textureID << "', x=" << x << ", y=" << y << "\n";
            #endif
        }
};

class GameObject : public IObject {
    public:
        GameObject(Properties* props) : m_Width(props->Width), m_Height(props->Height), m_TextureID(props->textureID), m_Flip(props->Flip)
        {
            #ifdef DEBUG
            std::cout << "GameObject ctor: textureID='" << m_TextureID << "', w=" << m_Width << ", h=" << m_Height << "\n";
            #endif
            m_Transform = new Transform(props->x, props->y);
            float px = props->x + props->Width / 2;
            float py = props->y + props->Height / 2;
            m_Origin = new Vector2D(px, py);
        }

        virtual ~GameObject() {
            #ifdef DEBUG
            std::cout << "GameObject dtor: textureID='" << m_TextureID << "'\n";
            #endif
            if (m_Collider) delete m_Collider;
            if (m_Transform) delete m_Transform;
            if (m_Origin) delete m_Origin;
        }

        template<typename ColliderType, typename... Args>
        void AddCollider(Args&&... args) {
            if (m_Collider) {
                delete m_Collider;
            }
            m_Collider = new ColliderType(std::forward<Args>(args)...); //work on it later to understand it better
        }

        inline GameObjectCollider* getCollider() {return m_Collider;}
        inline Vector2D* GetOrigin() {return m_Origin;}

        inline void setScene(Scene *scene_ptr) {m_Scene = scene_ptr;}

        inline friend std::ostream& operator<<(std::ostream& os, const GameObject& go) {os << "GameObject with textureID : " << go.m_TextureID << std::endl; return os;}
        friend class Scene;

        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
    
        protected:
            Vector2D* m_Origin; //represent the center of the GameObject
            Transform* m_Transform;
            RigidBody* m_RigidBody = nullptr;
            GameObjectCollider* m_Collider = nullptr;
            int m_Width, m_Height;
            std::string m_TextureID;
            SDL_FlipMode m_Flip;
            Scene* m_Scene = nullptr;
};
#endif