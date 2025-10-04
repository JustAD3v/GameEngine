#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector2D.h"
#include <vector>

class Collider {
    public:
        Collider(Vector2D* target) : m_Target(target), m_Position(*target) {};
        virtual ~Collider() = default;

        inline void Update() {
            m_Position = *m_Target;
            UpdateAxesAndVertices();
        }

        virtual void UpdateAxesAndVertices() = 0;
        virtual void ProjectOnAxis(const Vector2D& axis, float& min, float& max) const = 0;
        
        //isOverlapped methods
        virtual bool isOverlapped(const Collider& other) const = 0;

        //for double dispatch
        virtual bool isOverlappedWithBox(const class BoxCollider& box) const = 0;
        //virtual bool isOverlappedWithCircle(const class CircleCollider& circle) const = 0;


        virtual std::vector<Vector2D> GetAxes() const = 0; 
        virtual std::vector<Vector2D> GetVertices() const = 0;
        
        inline const Vector2D& GetPosition() const {return m_Position;} //second const indicates that the current Object (this) is not modified by the method

    protected:
        Vector2D* m_Target;
        Vector2D m_Position;
};


#endif