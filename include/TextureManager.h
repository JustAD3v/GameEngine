#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <SDL3/SDL.h>
#include <map>
#include <SDL3_image/SDL_image.h>

class TextureManager {
    public:
        static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();}

        bool Load(std::string id, std::string filename);
        void Drop(std::string id);

        /*Draws at absolute position on the screen, useful for UI and interface*/
        void Draw(std::string id, float x, float y, float widht, float height, SDL_FlipMode flip=SDL_FLIP_NONE);
        
        /*Draws at position relative to the cameras position*/
        void DrawTile(std::string tilesetID, float x, float y, float tileSize, int row, int frame, SDL_FlipMode flip=SDL_FLIP_NONE);
        void DrawFrame(std::string id, float x, float y, float widht, float height, int row, int frame, SDL_FlipMode flip=SDL_FLIP_NONE);
        
        void Clean();
        static void DestroyInstance();

    private:
        TextureManager() {};
        ~TextureManager();
        static TextureManager* s_Instance;
        std::map<std::string, SDL_Texture*> m_TextureMap;
};

#endif