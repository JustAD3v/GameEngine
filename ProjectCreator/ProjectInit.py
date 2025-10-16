import sys
import os

projectName = sys.argv[1]
mainDir = "./" + sys.argv[1]
includeDir = mainDir + "/include"
srcDir = mainDir + "/src"
if not os.path.exists(mainDir):
    os.makedirs(mainDir)

if not os.path.exists(includeDir):
    os.makedirs(includeDir)

if not os.path.exists(srcDir):
    os.makedirs(srcDir)

IGameFile = """
// IGame.h
#ifndef IGAME_H
#define IGAME_H
class IGame {
public:
    virtual ~IGame() = default;
    virtual void OnInit() = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnRender() = 0;
    virtual void OnClean() = 0;
};
#endif
"""


GameFileH = """
#ifndef GAMEFILE_H
#define GAMEFILE_H
#include "IGame.h"

class {name} : public IGame {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnClean() override;

private:
    
};
#endif

""".format(name=projectName)

GameFileSrc = """
#include "{name}.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Engine.h"
#include "MapParser.h"

void {name}::OnInit() {
    //MapParser::GetInstance()->Load("level1", "assets/maps/level1.tmj");
    //level = MapParser::GetInstance()->GetMap("level1");

    //TextureManager::GetInstance()->Load("playerIdle", "assets/player/Idle32.png");
    //TextureManager::GetInstance()->Load("playerRun", "assets/player/Run32.png");

    //player = new Warrior(new Properties("playerRun", 100, 100, 32, 32));
    //Camera::GetInstance()->SetTarget(player->GetOrigin());
}

void {name}::OnUpdate(float dt) {
    //level->Update();
    //player->Update(dt);
    //Camera::GetInstance()->Update(dt);
}

void {name}::OnRender() {
    //level->Render();
    //player->Draw();
}

void {name}::OnClean() {
    //TextureManager::GetInstance()->Clean();
    //delete player;
}

""".format(name=projectName)

mainFile = """
#include "Engine.h"
#include "{name}.h"

int main() {
    {name} game;
    Engine::GetInstance()->Run(&game);
    return 0;
}
"""