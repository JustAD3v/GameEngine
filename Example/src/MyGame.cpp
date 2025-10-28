//#include <windows.h>

#include "TextureManager.h"
#include "Camera.h"
#include "Engine.h"
#include "MapParser.h"

#include "../include/MyGame.h"

void MyGame::OnInit() {
    /*Stub to set the right directory on windows*/
    //Test with GetCurrentDirectory
    //SetCurrentDirectory((LPCTSTR)".."); //to find assets folder 
    /*==========================================*/
    #ifdef DEBUG
    std::cout << "DEBUG Mode ON" << std::endl;
    #endif

    if(!MapParser::GetInstance()->Load("level1", "assets/maps/level1.tmj")) {
        std::cout << "Failed to load map" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    TextureManager::GetInstance()->Load("playerIdle", "assets/player/Idle32.png");
    TextureManager::GetInstance()->Load("playerRun", "assets/player/Run32.png");

    TextureManager::GetInstance()->Load("boxIdle", "assets/items/BoxIdle.png");
    
    player = new Warrior(new Properties("playerRun", SCREEN_WIDTH/2, 0, 32, 32));
    player->AddCollider<class BoxCollider>(player->GetOrigin(), 32, 32);
    
    obstacle = new Obstacle(new Properties("boxIdle", SCREEN_WIDTH/2 + 50, 0, 28, 24));
    obstacle->AddCollider<class BoxCollider>(obstacle->GetOrigin(), 28, 24);

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    countCollide = 0;
}

void MyGame::OnUpdate(float dt) {
    m_LevelMap->Update();
    player->Update(dt);
    obstacle->Update(dt);
    Camera::GetInstance()->Update(dt);
    // if (player->getCollider()->isOverlapped(*(obstacle->getCollider()))) { //rethink usage of pointers/refs
    //     std::cout << "Player collides with box : " << (countCollide++) << std::endl;
    // } 
}

void MyGame::OnRender() {
    m_LevelMap->Render();
    player->Draw();
    obstacle->Draw();
}

void MyGame::OnClean() {
    //TextureManager::GetInstance()->Clean(); //handled in the Engine before exiting Run method.
    // Remove camera target before deleting the player to avoid a dangling pointer
    Camera::GetInstance()->SetTarget(nullptr);

    delete player;
    player = nullptr;

    delete obstacle;
    obstacle = nullptr;
}
