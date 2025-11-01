#ifndef GOCOLLIDER_H
#define GOCOLLIDER_H

#include "Collider.h"

class GameObjectCollider : public Collider {
    public:
        GameObjectCollider(Vector2D* target) : Collider(target) {};
        virtual ~GameObjectCollider() = default;

        inline void Update() {
            m_Position = *m_Target;
            UpdateAxesAndVertices();
        }

        inline bool isSolid() {return m_IsSolid;} 

        virtual void UpdateAxesAndVertices() = 0;
    
    private:
        bool m_IsSolid;

};


#endif