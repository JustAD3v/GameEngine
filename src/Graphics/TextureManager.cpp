#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load surface : %s", SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);

    if (texture == nullptr) {
        SDL_Log("Failed to create texture : %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, float x, float y, float width, float height, SDL_FlipMode flip) {
    SDL_FRect srcRect = {0, 0, width, height};
    SDL_FRect destRect = {x, y, width, height};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, float x, float y, float width, float height, int row, int frame, SDL_FlipMode flip) {
    SDL_FRect srcRect = {frame*width, (row-1)*height, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    // SDL_FRect destRect = {x, y, width, height};
    SDL_FRect destRect = {x - cam.x, y - cam.y, width, height};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawTile(std::string id, float x, float y, float tileSize, int row, int frame, SDL_FlipMode flip) {
    SDL_FRect srcRect = {frame*tileSize, row*tileSize, tileSize, tileSize};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    //SDL_FRect destRect = {x, y, tileSize, tileSize};
    SDL_FRect destRect = {x - cam.x, y - cam.y, tileSize, tileSize};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean() {
    for (auto it = m_TextureMap.begin(); it != m_TextureMap.end(); it++){
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    SDL_Log("Texture map cleaned !");
}

TextureManager::~TextureManager() {
    SDL_Log("TextureManager destroyed!");
}

void TextureManager::DestroyInstance() {
    if (s_Instance) {
        delete s_Instance;
        s_Instance = nullptr;
    }
}