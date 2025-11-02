#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <iostream>
#include <cmath>

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
        inline bool operator==(const Vector2D v2) const {
            return (x == v2.x) && (y == v2.y);
        }
        inline bool operator!=(const Vector2D v2) const {
            return (x != v2.x) || (y != v2.y);
        }

        inline float dot(const Vector2D v2) const {
            return (x*v2.x + y*v2.y);
        }

        inline float GetNorm() const {
            return std::sqrt(x*x + y*y);
        }

        inline Vector2D Normalized() const {
            const float norm = this->GetNorm();
            return (norm == 0 ? Vector2D(0,0) : Vector2D(x / norm, y / norm));
        }

        inline Vector2D Perpendicular() const {
            return Vector2D(-y, x);
        }

        void Log(std::string msg = "") {
            std::cout << msg << "(x, y) = (" << x << ", " << y << ")" << std::endl;
        }
};

#endif