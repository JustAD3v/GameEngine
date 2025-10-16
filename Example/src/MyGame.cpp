#include "../include/MyGame.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Engine.h"
#include "MapParser.h"

void MyGame::OnInit() {
    if(!MapParser::GetInstance()->Load("level1", "assets/maps/level1.tmj")) {
        std::cout << "Failed to load map" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    TextureManager::GetInstance()->Load("playerIdle", "assets/player/Idle32.png");
    TextureManager::GetInstance()->Load("playerRun", "assets/player/Run32.png");
    
    player = new Warrior(new Properties("playerRun", SCREEN_WIDTH/2, 0, 32, 32));
    //player->AddCollider<class BoxCollider>(player->GetOrigin(), 32, 32);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
}

void MyGame::OnUpdate(float dt) {
    m_LevelMap->Update();
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void MyGame::OnRender() {
    m_LevelMap->Render();
    player->Draw();
}

void MyGame::OnClean() {
    //TextureManager::GetInstance()->Clean();
    delete player;
}
