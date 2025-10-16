#include "Engine.h"
#include "MyGame.h"

int main() {
    MyGame game;
    Engine::GetInstance()->Run(&game);
    return 0;
}