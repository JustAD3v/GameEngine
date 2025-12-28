#include "Obstacle.h"
#include "TextureManager.h"

Obstacle::Obstacle(Properties* props) : GameObject(props) {
    #ifdef DEBUG
    std::cout << "Obstacle Constructor called !" << std::endl;
    #endif
}

void Obstacle::Draw() {
    TextureManager::GetInstance()->DrawFrame("boxIdle", m_Transform->x, m_Transform->y, m_Width, m_Height,1,0); //Actually draws the sprite on the screen
}

void Obstacle::Update(float dt) {
    (void)dt;
    if (m_Collider) {
        m_Collider->Update();
    }
}

void Obstacle::Clean() {
    //TextureManager::GetInstance()->Clean();
}

Obstacle::~Obstacle() {
    #ifdef DEBUG
    std::cout << "Obstacle Destructor called !" << std::endl;
    #endif
}


