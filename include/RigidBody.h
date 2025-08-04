#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define U_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody {
    public:
        RigidBody() {
            m_Mass = U_MASS;
            m_Gravity = GRAVITY;
        }
    
        inline void SetMass(float mass) {m_Mass = mass;}

        inline void SetGravity(float gravity) {m_Gravity = gravity;}

        inline void ApplyForce(Vector2D F) {m_Force = F;}
        inline void ApplyForceX(float Fx) {m_Force.x = Fx;}
        inline void ApplyForceY(float Fy) {m_Force.y = Fy;}
        inline void UnsetForce() {m_Force = Vector2D(0,0);}

        inline void ApplyFriction(Vector2D Fr) {m_Friction = Fr;}
        inline void UnsetFriction() {m_Friction = Vector2D(0,0);}

        inline float GetMass() {return m_Mass;}
        inline Vector2D GetPosition() {return m_Position;}
        inline Vector2D GetVelocity() {return m_Velocity;}
        inline Vector2D GetAcceleration() {return m_Acceleration;}

        void Update(float dt) {
            m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
            m_Acceleration.y = m_Gravity + m_Force.y/m_Mass;
            m_Velocity = m_Acceleration*dt;
            m_Position = m_Velocity*dt;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;
    
        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;
};

#endif