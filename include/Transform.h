#ifndef TRASNFORM_H
#define TRASNFORM_H

#include "Vector2D.h"

class Transform {

    public:
        float x, y;
    
        Transform(float X=0, float Y=0) : x(X), y(Y) {};
        
        void Log(std::string msg = "") {
            std::cout << msg << "(x, y) = (" << x << ", " << y << ")" << std::endl;
        }
        
        inline void TranslateX(float X) {x += X;} 
        inline void TranslateY(float Y) {y += Y;} 
        inline void Translate(Vector2D v) {x += v.x; y += v.y;} 

};


#endif