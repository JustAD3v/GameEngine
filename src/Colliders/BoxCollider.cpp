#include "BoxCollider.h"
#include <cmath>

void BoxCollider::UpdateAxesAndVertices() {
    m_Vertices.clear();
    m_Vertices.push_back(m_Position + Vector2D(-m_Width/2, m_Height/2)); //0 : top left
    m_Vertices.push_back(m_Position + Vector2D(m_Width/2, m_Height/2)); //1 : top right
    m_Vertices.push_back(m_Position + Vector2D(-m_Width/2, -m_Height/2)); //2 : bottom left
    m_Vertices.push_back(m_Position + Vector2D(m_Width/2, -m_Height/2)); //3 : bottom righ
    m_Axes.clear();
    //Compute axis 1
    Vector2D p1 = m_Vertices.at(0);
    Vector2D p2 = m_Vertices.at(1);
    Vector2D axis1 = p2-p1;
    m_Axes.push_back(axis1.Normalized());
    //Compute axis 2
    Vector2D p3 = m_Vertices.at(1);
    Vector2D p4 = m_Vertices.at(3);
    Vector2D axis2 = p4-p3;
    m_Axes.push_back(axis2.Normalized());
}

void BoxCollider::ProjectOnAxis(const Vector2D& axis, float& min, float& max) const {
    //min and max must be already initialized by a function or INFINITY/-INFINITY if they are used for the first time
    for (size_t i = 0; i < m_Vertices.size(); i++) {
        float projVert = axis.dot(m_Vertices[i]);
        if (projVert < min) {min = projVert;}
        if (projVert > max) {max = projVert;}
    }
}

bool BoxCollider::isOverlapped(const Collider& other) const {
    return other.isOverlappedWithBox(*this);
}

bool BoxCollider::isOverlappedWithBox(const BoxCollider& box) const {
    std::vector<Vector2D> axesToTest;

    for (size_t i = 0; i < this->m_Axes.size(); i++) {
        axesToTest.push_back(this->m_Axes[i]);
    }
    for (size_t i = 0; i < box.m_Axes.size(); i++) {
        axesToTest.push_back(box.m_Axes[i]);
    }
    //factor this later in a TAS(const vector<Vector2D> axesToTest, Collider& other)
    for (size_t i = 0; i < axesToTest.size(); i++) {
        float minthis = INFINITY, maxthis = -INFINITY;
        float minother = INFINITY, maxother = -INFINITY;
        this->ProjectOnAxis(axesToTest[i], minthis, maxthis);
        box.ProjectOnAxis(axesToTest[i], minother, maxother);
        if (maxthis < minother || minthis > maxother) {
            return false;
        }
    }
    return true; 
}

