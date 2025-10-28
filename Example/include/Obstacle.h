#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "GameObject.h"
#include "Animation.h"

class Obstacle : public GameObject {
    public:
        Obstacle(Properties* props);
        virtual ~Obstacle();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        
    private:
        Animation* m_Animation;
};

#endif