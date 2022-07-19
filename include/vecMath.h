#pragma once
/* VecMath is used to return a new vector instead of performing
   the operation on a vector itself. */

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
    
};

#endif