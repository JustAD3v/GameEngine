#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "GameObjectCollider.h"

class BoxCollider : public GameObjectCollider {
    public : 
        BoxCollider(Vector2D* target, float width, float height) : GameObjectCollider(target), m_Width(width), m_Height(height) {};
        ~BoxCollider();
        void UpdateAxesAndVertices() override;
        void ProjectOnAxis(const Vector2D& axis, float& min, float& max) const override;
        bool isOverlapped(const Collider& other) const override;
        bool isOverlappedWithBox(const class BoxCollider& box) const override;
        //bool isOverlappedWithCircle(const class CircleCollider& circle) const override;
        inline std::vector<Vector2D> GetVertices() const override {return m_Vertices;}
        inline std::vector<Vector2D> GetAxes() const override {return m_Axes;}

    private :
        float m_Width, m_Height;
        std::vector<Vector2D> m_Axes;
        std::vector<Vector2D> m_Vertices;
};

#endif