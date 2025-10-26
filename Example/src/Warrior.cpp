#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props) {
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 12, 80, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height); //Actually draws the sprite on the screen
}

void Warrior::Update(float dt) {
    GetFlipState() ? m_Animation->SetProps("playerIdle", 1, 11, 80, SDL_FLIP_HORIZONTAL) : m_Animation->SetProps("playerIdle", 1, 11, 80);
    m_RigidBody->UnsetForce(); //do not move when the player does not press a key

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_Animation->SetProps("playerRun", 1, 12, 80, SDL_FLIP_HORIZONTAL);
        m_RigidBody->ApplyForceX(-15);
        SetFlipState(true);
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_Animation->SetProps("playerRun", 1, 12, 80);
        m_RigidBody->ApplyForceX(15);
        SetFlipState(false);
    }

    m_RigidBody->Update(dt);
    
    m_Transform->TranslateX(m_RigidBody->GetPosition().x);
    //m_Transform->Translate(m_RigidBody->GetPosition());

    if (m_Collider) {
        m_Collider->Update();
    }

    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Width/2;

    m_Animation->Update(); //Updates the frame to render according to the Animation speed
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Clean();
}


