#ifndef GAMEFILE_H
#define GAMEFILE_H
#include "IGame.h"
#include "Warrior.h"
#include "GameMap.h"

class MyGame : public IGame {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnClean() override;

private:
    GameMap* m_LevelMap;
    Warrior* player = nullptr;
};
#endif