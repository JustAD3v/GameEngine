#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"
#include "Scene.h"

Warrior::Warrior(Properties* props) : Character(props) {
    #ifdef DEBUG
    std::cout << "Entering Warrior ctor\n";
    #endif
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
    (void)dt;
    GetFlipState() ? m_Animation->SetProps("playerIdle", 1, 11, 80, SDL_FLIP_HORIZONTAL) : m_Animation->SetProps("playerIdle", 1, 11, 80);
    m_RigidBody->UnsetForce(); //do not move when the player does not press a key

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_Animation->SetProps("playerRun", 1, 12, 80, SDL_FLIP_HORIZONTAL);
        m_RigidBody->ApplyForceX(-15);
        SetFlipState(true);
        // GameObject* obstacleObj = m_Scene->getObjectById("obstacle");
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_Animation->SetProps("playerRun", 1, 12, 80);
        m_RigidBody->ApplyForceX(15);
        SetFlipState(false);
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
    // add free of Collider ?
    #ifdef DEBUG
    std::cout << "Warrior Destructor called !" << std::endl;
    #endif
}


