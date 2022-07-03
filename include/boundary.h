
#ifndef _BOUNDARY_
#define _BOUNDARY_

#include "utilities.h"
#include "vec2.h"

class Boundary {

private:
    Vec2 pointA;
    Vec2 pointB;
    double length;

public:

    Boundary () {
        ;
    }

    Boundary (Vec2 a, Vec2 b){
        pointA = a;
        pointB = b;
        length = pointA.Distance(pointB);
    }

    void Draw (SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, pointA.getX(), pointA.getY(),
            pointB.getX(), pointB.getY());
    }

    double DistancePointA(Vec2 point) {
        return pointA.Distance(point);
    }

    double DistancePointB(Vec2 point) {
        return pointB.Distance(point);
    }

    Vec2 getPointA() { return pointA; }
    Vec2 getPointB() { return pointB; }
    double getLength() { return length; }
};

#endif