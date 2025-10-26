#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "GameObject.h"

class Obstacle : public GameObject {
    public:
        Obstacle(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        
    private:

};

#endif