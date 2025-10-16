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