#include "Obstacle.h"
#include "TextureManager.h"

Obstacle::Obstacle(Properties* props) : GameObject(props) {
    std::cout << "Obstacle created !" << std::endl;
}

void Obstacle::Draw() {
    TextureManager::GetInstance()->Draw("boxIdle", m_Transform->x, m_Transform->y, m_Width, m_Height); //Actually draws the sprite on the screen
}

void Obstacle::Update(float dt) {
    
    if (m_Collider) {
        m_Collider->Update();
    }
}

void Obstacle::Clean() {
    TextureManager::GetInstance()->Clean();
}


