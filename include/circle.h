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

#define SIZE_SCALAR 5 /* a scalar for the size of the circle */

class Circle: public Object {

private:
    double radius;
    double diameter;
    Vec2 closestLinePoint;
    bool collisionWithBoundary;
    bool collisionWithCircle;

public:

    /* Constructor - calls Object constructor */
    Circle(Vec2 pos, Vec2 vel, Vec2 acc, double m, SDL_Color col) 
    : Object(pos, vel, acc, m, col) {  
        radius = (m + m) * SIZE_SCALAR;
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
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, color.a);
        SDL_RenderDrawLine(renderer, position.getX(), position.getY(), (position.getX() + velocity.getX()*10), (position.getY() + velocity.getY()*10));
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

    void CollisionBoundaries(vector<Boundary*> boundaries) {
        for (int i = 0; i < (int) boundaries.size(); i++) {
            if (boundaries[i]->CircleIntersect(position, radius)){
                setCollisionWithBoundary(true);
                boundaries[i]->getNormal();
                this->Bounce(boundaries[i]->getNormal());
            }
        }
    }

    void CollisionCircles(vector<Circle*> circles) {
        for (int i = 0; i < (int) circles.size(); i++) {
            if (position != circles[i]->getPos()){
                double dist = circles[i]->getPos().Distance(position);
                if (dist <= (circles[i]->getRadius() + radius)) {
                    setCollisionWithCircle(true);
                    Vec2 vCollision(circles[i]->getPos().getX() - position.getX(), 
                                    circles[i]->getPos().getY() - position.getY());
                    double dist = vCollision.magnitude();
                    vCollision.divide(dist);
                    Vec2 vRelativeVelocity(velocity.getX() - circles[i]->getVel().getX(), 
                                           velocity.getY() - circles[i]->getVel().getY());
                    double speed = vRelativeVelocity.getX() * vCollision.getX() + vRelativeVelocity.getY() * vCollision.getY();
                    speed *= 0.90;
                    if (speed < 0){
                        continue;
                    }

                    /* Handle impulse and momentum */ 
                    double impulse = 2 * speed / (circles[i]->getMass() + mass);
                    Vec2 momentum1 = VecMath::mult(vCollision, impulse * circles[i]->getMass()); 
                    Vec2 momentum2 = VecMath::mult(vCollision, impulse * mass); 
                    velocity.sub(momentum1);
                    Vec2 cpy = circles[i]->getVel();
                    cpy.add(momentum2);
                    circles[i]->setVel(cpy);
                }
            }
        }
    }

    double getRadius() { return radius; }
    void setCollisionWithBoundary(bool collided) { collisionWithBoundary = collided; }
    bool getCollisionWithBoundary() { return collisionWithBoundary; }
    void setCollisionWithCircle(bool collided) { collisionWithCircle = collided; }
    bool getCollisionWithCircle() { return collisionWithCircle; }
    

};

#endif