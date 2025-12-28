#ifndef WARRIOR_H
#define WARRIOR_H
/*Imports from Engine*/
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
/*===================*/ 

class Warrior: public Character{
    public:
        Warrior(Properties* props);
        virtual ~Warrior();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        inline void SetFlipState(bool state) {m_HasFlipped = state;}
        inline bool GetFlipState() {return m_HasFlipped;}

        inline RigidBody* getRigidBody() {return m_RigidBody;}

    private:
        // int m_Row, m_Frame, m_FrameCount;
        // int m_AnimSpeed;
        Animation* m_Animation;
        bool m_HasFlipped;
};

#endif
