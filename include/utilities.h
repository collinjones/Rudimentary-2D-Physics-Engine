#ifndef _UTILITIES_
#define _UTILITIES_

#include <math.h>
#include "vec2.h"

class Utilities {
public:

    /* Just your friendly Pythagorean Theorem */
    static double Distance (Vec2 pointA, Vec2 pointB) {
        double distX = pointA.getX() - pointB.getX();
        double distY = pointA.getY() - pointB.getY();
        return sqrt((distX * distX) + (distY * distY));
    }
};

#endif