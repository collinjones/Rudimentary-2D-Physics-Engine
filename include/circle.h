

#ifndef _CIRCLE_
#define _CIRCLE_

#include <SDL2/SDL.h>
#include "object.h"
#include "vec2.h"
#include "boundary.h"
#include "utilities.h"

#define SIZE_SCALAR 3 /* a scalar for the size of the circle */

class Circle: public Object {

private:
    double radius;
    double diameter;


public:

    /* Constructor - calls Object constructor */
    Circle(Vec2 pos, Vec2 vel, Vec2 acc, double m, SDL_Color col) 
    : Object(pos, vel, acc, m, col) {  
        radius = (m * m) * SIZE_SCALAR;
        diameter = 2 * radius;
    }

    /* Circle drawing algorithm https://stackoverflow.com/questions/28346989/drawing-and-filling-a-circle */
    void Draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        for (int w = 0; w < diameter; w++) {
            for (int h = 0; h < diameter; h++) {
                int dx = radius - w;
                int dy = radius - h;
                if ( (dx*dx + dy*dy) <= (radius * radius) ) {
                    SDL_RenderDrawPoint(renderer, position.getX() + dx, position.getY() + dy);
                }
            }
        }
    }

    void Edges(int width, int height) {

        double edgeDampener = -0.9;  /* Used to slightly slow an object's velocity if it hits the edge */

        if (this->position.getY() >= height - this->radius) {
            this->position.setY(height - this->radius);
            this->velocity.multY(edgeDampener);
        }
        if (this->position.getY() <= this->radius) {
            this->position.setY(this->radius);
            this->velocity.multY(edgeDampener);
        }
        if (this->position.getX() >= width-this->radius) {
            this->position.setX(width - this->radius);
            this->velocity.multX(edgeDampener);
        }
        if (this->position.getX() <= this->radius) {
            this->position.setX(this->radius);
            this->velocity.multX(edgeDampener);
        }
    }

    bool CollisionWithLine(Boundary line) {

        /* Return true if either end of line is inside circle */
        bool inside1 = CollisionWithPoint(line.getPointA());
        bool inside2 = CollisionWithPoint(line.getPointB());
        if (inside1 || inside2) return true;

        /* Dot product of line & circle */
        double dot = (((position.getX()-line.getPointA().getX())*(line.getPointB().getX()-line.getPointA().getX())) + 
            ((position.getY()-line.getPointA().getY())*(line.getPointB().getY()-line.getPointA().getY())) ) / line.getLength() * line.getLength();

        /* Find closest point on the line and check if that point is on the line segment or not */
        double closestX = line.getPointA().getX() + (dot * (line.getPointB().getX() - line.getPointA().getX()));
        double closestY = line.getPointA().getY() + (dot * (line.getPointB().getY() - line.getPointA().getY()));
        Vec2 closestPoint(closestX, closestY);
        bool onSegment = PointCollisionLine(closestPoint, line);
        if (!onSegment) return false;

        double distanceClosestPoint = position.Distance(closestPoint);
        if (distanceClosestPoint <= radius) {
            return true;
        }
        return false;
        
    }  

    bool CollisionWithPoint(Vec2 point) {
        double distance = position.Distance(point);

        if (distance <= this->radius) {
            return true;
        }
        return false;
    }

    bool PointCollisionLine(Vec2 point, Boundary line) {
        double buffer = 0.1;
        if (line.DistancePointA(point) + line.DistancePointB(point) >= line.getLength() - buffer 
            && line.DistancePointA(point) + line.DistancePointB(point) <= line.getLength() + buffer) {
            return true;
        }
        return false;
    }

};

#endif