#ifndef GAMEFILE_H
#define GAMEFILE_H
/*Imports from Engine*/
#include "IGame.h" 
#include "GameMap.h"
#include "Scene.h"
/*===================*/ 
#include "Warrior.h"
#include "Obstacle.h"

class MyGame : public IGame {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnClean() override;

private:
    GameMap* m_LevelMap;
    Warrior* player = nullptr;
    Obstacle *obstacle = nullptr;
    Scene *m_Scene1 = nullptr;
    int countCollide = 0;
};
#endif