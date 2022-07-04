

#ifndef _VECMATH_
#define _VECMATH_

#include <math.h>
#include <SDL2/SDL.h>
#include "vec2.h"

class VecMath {
     
public:

    /* Multiply a 2D vector by a scalar */
    static Vec2 mult(Vec2 v1, float scalar) {
        Vec2 newVec(v1.getX() * scalar, v1.getY() * scalar);
        return newVec;
    }  

    static void div(Vec2* v, double scalar) {
        v->setX(v->getX() / scalar);
        v->setY(v->getY() / scalar);
    }

    /* Normalize a vector */
    static Vec2 normalize(Vec2 v) {
        double mag = v.magnitude();
        div(&v, mag);
        return v;
    }
    
};

#endif