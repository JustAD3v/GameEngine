#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"
#include "Scene.h"

Warrior::Warrior(Properties* props) : Character(props) {
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 12, 80, SDL_FLIP_HORIZONTAL);
    #ifdef DEBUG
    std::cout << "Warrior Constructor called !" << std::endl;
    #endif
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
        GameObject* obstacleObj = m_Scene->getObjectById("obstacle");
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_Animation->SetProps("playerRun", 1, 12, 80);
        m_RigidBody->ApplyForceX(15);
        SetFlipState(false);
    }

    Vector2D oldPos = m_Transform->GetPosition();
    //oldPos.x -= m_RigidBody->GetPosition().x*2;
    //m_RigidBody->GetPosition().Log();
    //oldPos.Log("Old : ");
    m_RigidBody->Update(dt);
    m_Transform->TranslateX(m_RigidBody->GetPosition().x);
    //m_Transform->Translate(m_RigidBody->GetPosition());
    //m_Transform->Log("New : ");
    
    GameObject* obstacleObj = m_Scene->getObjectById("obstacle");

    if (m_Collider && obstacleObj && m_Collider->isOverlapped(*(obstacleObj->getCollider()))) {
        //m_RigidBody->UnsetForce();
        oldPos.x -= 0.1;
        m_Transform->SetPosition(oldPos); 
    }

    if (m_Collider) {
        m_Collider->Update();
    }

    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Width/2;

    m_Animation->Update(); //Updates the frame to render according to the Animation speed
}

void Warrior::Clean() {
    //TextureManager::GetInstance()->Clean();
}

Warrior::~Warrior() {
    if (m_Animation) delete m_Animation;
    if (m_RigidBody) delete m_RigidBody;
    #ifdef DEBUG
    std::cout << "Warrior Destructor called !" << std::endl;
    #endif
}


