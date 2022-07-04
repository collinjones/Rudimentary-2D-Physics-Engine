#ifndef _CIRCLE_
#define _CIRCLE_

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "object.h"
#include "vec2.h"
#include "utilities.h"
#include "boundary.h"

using namespace std;

#define SIZE_SCALAR 3 /* a scalar for the size of the circle */

class Circle: public Object {

private:
    double radius;
    double diameter;
    Vec2 closestLinePoint;
    bool collisionWithBoundary;

public:

    /* Constructor - calls Object constructor */
    Circle(Vec2 pos, Vec2 vel, Vec2 acc, double m, SDL_Color col) 
    : Object(pos, vel, acc, m, col) {  
        radius = (m * m) * SIZE_SCALAR;
        diameter = 2 * radius;
        collisionWithBoundary = false;
    }

    /* Circle drawing algorithm https://stackoverflow.com/questions/28346989/drawing-and-filling-a-circle */
    void Draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        for (int w = 0; w < diameter; w++) {
            for (int h = 0; h < diameter; h++) {
                double dx = radius - w;
                double dy = radius - h;
                if ( (dx*dx + dy*dy) <= (radius * radius) ) {
                    SDL_RenderDrawPoint(renderer, position.getX() + dx, position.getY() + dy);
                }
            }
        }
    }

    void Bounce(Vec2 normal) {
        /* Calculate bounce vector given incoming velocity vector and normal vector */
        Vec2 tmp;
        normal.multiply(-2 * velocity.Dot(normal));
        tmp = normal;
        tmp.add(velocity);
        velocity = tmp;
    }

    void CollisionEdges(int width, int height) {

        double edgeDampener = -0.5;  /* Used to slightly slow an object's velocity if it hits the edge */

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

    void CollisionBoundaries(vector<Boundary*> boundaries) {
        for (int i = 0; i < (int) boundaries.size(); i++) {
            if (boundaries[i]->CircleIntersect(position, radius)){
                setCollisionWithBoundary(true);
                boundaries[i]->getNormal().multiply(-1);
                this->Bounce(boundaries[i]->getNormal());
            }
        }
    }

    double getRadius() { return radius; }
    void setCollisionWithBoundary(bool collided) { collisionWithBoundary = collided; }
    bool getCollisionWithBoundary() { return collisionWithBoundary; }

};

#endif