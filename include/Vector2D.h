#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <iostream>

class Vector2D {
    public:
        float x, y;

        Vector2D(float X=0, float Y=0) : x(X), y(Y) {}

        inline Vector2D operator+(const Vector2D v2) const {
            return Vector2D (x + v2.x, y + v2.y);
        }
        inline Vector2D operator-(const Vector2D v2) const {
            return Vector2D (x - v2.x, y - v2.y);
        }
        inline Vector2D operator*(const float scalar) const {
            return Vector2D(x*scalar, y*scalar);
        }

        void Log(std::string msg = "") {
            std::cout << msg << "(x, y) = (" << x << ", " << y << ")" << std::endl;
        }
};

#endif