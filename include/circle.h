#pragma once
#ifndef _CIRCLE_
#define _CIRCLE_

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "object.h"
#include "vec2.h"
#include "boundary.h"
#include "rectangle.h"
#include "peg.h"

using namespace std;

#define SIZE_SCALAR 5 /* a scalar for the size of the circle */

class Circle: public Object {

protected:
    const double restitution = 0.9;  /* Dampening when objects collide */
    double radius;
    double diameter;

    bool collisionWithBoundary; 
    bool collisionWithCircle;
    bool topCollision; 
    bool bottomCollision;
    bool leftCollision;
    bool rightCollision;

    bool attracter = false;
    bool repulser = false;

public:

    Circle() {
        ;
    }

    Circle(Vec2 pos, Vec2 vel, double m, SDL_Color col) 
    : Object(pos, vel, m, col) {  
        radius = m * 3;
        diameter = 2 * radius;

        collisionWithBoundary = false;
        topCollision = false;
        bottomCollision = false;
        leftCollision = false;
        rightCollision = false;
    }

    /* true for the bool means attracter and false means repulser*/
    Circle(Vec2 pos, Vec2 vel, double m, SDL_Color col, bool attractOrRepulse)
        : Object(pos, vel, m, col) {
            radius = m * 3;
            diameter = 2 * radius;
            
            collisionWithBoundary = false;
            topCollision = false;
            bottomCollision = false;
            leftCollision = false;
            rightCollision = false;

            if(attractOrRepulse == true)
            {
                attracter = true;
            }
            else{
                repulser = true;
            }
        }

    /* Circle drawing algorithm https://stackoverflow.com/questions/28346989/drawing-and-filling-a-circle */
    void Draw(SDL_Renderer* renderer) {
        DrawVelocity(renderer);
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

    /* Draws the velocity of the object represented as a line */
    void DrawVelocity(SDL_Renderer* renderer) {
        Vec2 velPos((position.getX() + velocity.getX()*8), (position.getY() + velocity.getY()*8));
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, color.a);
        SDL_RenderDrawLine(renderer, position.getX(), position.getY(), velPos.getX(), velPos.getY());
    }

    /* This stackoverflow post helped me implement this code */
    /* https://stackoverflow.com/questions/16417891/how-can-i-find-a-normal-vector-of-a-2d-line */
    /* Calculate bounce vector given incoming velocity vector and normal vector */
    void LineBounce(Vec2 normal) {
        Vec2 tmp;
        normal.multiply(-2 * velocity.Dot(normal));
        tmp = normal;
        tmp.add(velocity);
        velocity = tmp;
    }

    void CollisionEdges(int width, int height) {
        /* Checks and resolves collisions with the edges of the screen */

        if (this->position.getY() >= height - this->radius) {
            this->position.setY(height - this->radius);
            this->velocity.multY(-restitution);  /* Reverse velocity */
        }
        else if (this->position.getY() <= this->radius) {
            this->position.setY(this->radius);
            this->velocity.multY(-restitution);  /* Reverse velocity */
        }
        if (this->position.getX() >= width-this->radius) {
            this->position.setX(width - this->radius);
            this->velocity.multX(-restitution);  /* Reverse velocity */
        }
        else if (this->position.getX() <= this->radius) {
            this->position.setX(this->radius);
            this->velocity.multX(-restitution);  /* Reverse velocity */
        }
    }

    void WrapAround(int WIDTH, int HEIGHT) {
        if (position.getX() < - radius) position.setX(WIDTH + radius);
        if (position.getY() < - radius) position.setY(HEIGHT + radius);
        if (position.getX() > WIDTH + radius) position.setX(-radius);
        if (position.getY() > HEIGHT + radius) position.setY(-radius);
    }

    /* Checks all boundaries in list for collision */
    void CollisionBoundaries(vector<Boundary*> boundaries) {
        for (int i = 0; i < (int) boundaries.size(); i++) {
            if (boundaries[i]->CircleIntersect(position, radius)){
                setCollisionWithBoundary(true);
                this->LineBounce(boundaries[i]->getNormal());
            }
        }
    }

    /* Checks for a single boundary collision */
    void CollisionBoundary(Boundary boundary) {
        if (boundary.CircleIntersect(position, radius)){
            setCollisionWithBoundary(true);
            this->LineBounce(boundary.getNormal());
        }
    }

    /* Loops through a list of circles to check if this circle is colliding, then resolve */
    void CollisionCircles(vector<Circle*> circles) {
        for (int i = 0; i < (int) circles.size(); i++) {

            /* Don't check collision with itself */
            if (position != circles[i]->getPos()){

                /* Get the distance between the two circles and check if 
                    the distance <= circle1rad + circle2rad */
                double dist = circles[i]->getPos().Distance(position);
                if (dist <= (circles[i]->getRadius() + radius)) {

                    /* COLLISION */
                    setCollisionWithCircle(true);
                    ResolveCollisionCircle(circles[i]);
                }
            }
        }
    }

    /* Loops through a list of pegs to check if this circle is colliding, then resolve */
    void CollisionPegs(vector<Peg*> pegs) {
        for (int i = 0; i < (int) pegs.size(); i++) {
            if (position != pegs[i]->getPos()){
                double dist = pegs[i]->getPos().Distance(position);
                if (dist <= (pegs[i]->getRadius() + radius)) {
                    setCollisionWithCircle(true);
                    ResolveCollisionPeg(pegs[i]);
                }
            }
        }
    }

    /* Checks and resolves collisions with other rectangles */
    void CollisionRectangles(vector<Rectangle*> rectangles) {
        for (int i = 0; i < (int) rectangles.size(); i++) {
            if (rectangles[i]->CollisionWithCircle(position.getX(), position.getY(), radius, &leftCollision, &rightCollision, &topCollision, &bottomCollision)) {
                if(topCollision) {
                    this->position.setY(rectangles[i]->getRect().y - radius);
                    this->velocity.multY(-restitution);  /* Reverse velocity */
                }
                else if(bottomCollision) {
                    this->position.setY(rectangles[i]->getRect().y + rectangles[i]->getRect().h + radius);
                    this->velocity.multY(-restitution);  /* Reverse velocity */
                }
                else if(leftCollision) {
                    this->position.setX(rectangles[i]->getRect().x - this->radius);
                    this->velocity.multX(-restitution);  /* Reverse velocity */
                }
                else if(rightCollision) {
                    this->position.setX(rectangles[i]->getRect().x + rectangles[i]->getRect().w  + this->radius);
                    this->velocity.multX(-restitution);  /* Reverse velocity */
                }
            }
            resetCollisions();
        }
    }

    /* This is my altered version of the collision resolution algorithm */
    void ResolveCollisionPeg(Peg* peg) {
        /* Resolves a collision with another peg */

        Vec2 vCollision;  /* Holds the direction of collision */
        Vec2 vRelativeVelocity;
        Vec2 momentum1;
        Vec2 momentum2;
        Vec2 obj2VelCpy; 
        double speed;    /* Used to calculate impulse */
        double impulse;  /* Used to calculate momentums */

        /* Get the collision vector and its distance (magnitude) */
        vCollision.setVec(peg->getPos().getX() - position.getX(), 
                        peg->getPos().getY() - position.getY());

        /* Normalize the collision vector to get its direction */
        vCollision.divide(vCollision.magnitude());
        

        /* Get the relative velocity vector and calculate the collision speed, then dampen the speed by the restituion */
        vRelativeVelocity.setVec(velocity.getX() - peg->getVel().getX(), 
                               velocity.getY() - peg->getVel().getY());
        speed = vRelativeVelocity.getX() * vCollision.getX() + vRelativeVelocity.getY() * vCollision.getY();
        speed *= restitution;

        /* If the speed is less than 0 (object moving away), just return here */
        if (speed < 0){
            return;
        }

        /* Calculate impulse, which will be used to calculate each objects momentum */ 
        impulse = 2 * speed / (peg->getMass() + mass);
        momentum1 = VecMath::mult(vCollision, impulse * peg->getMass()); 
        momentum1.multiply(1.8);  // strength of bounce 
        

        /* Subtract the momentum1 from this objects velocity */
        velocity.sub(momentum1);
    }


    /* https://spicyyoghurt.com/tutorials/html5-javascript-game-development/collision-detection-physics was used to get the collision resolution algorithm with impulse */
    /* and momentum. Nothing else was used, all initial physics concepts came from NoC book. */
    /* Resolves a collision with another circle */
    void ResolveCollisionCircle(Circle* circle) {
        
        Vec2 vCollision;        /* The subtracted vector the two objects made when colliding */
        Vec2 vRelativeVelocity; /* Their relative velocity */
        Vec2 momentum1;         /* Momentum of object 1 */
        Vec2 momentum2;         /* Momentum of object 1 */
        Vec2 obj2VelCpy;        /* A copy of object 2s velocity */
        double speed;           /* Used to calculate impulse */
        double impulse;         /* Used to calculate momentums */

        /* Get the collision vector and its distance (magnitude) */
        vCollision.setVec(circle->getPos().getX() - position.getX(), 
                        circle->getPos().getY() - position.getY());

        /* Normalize the collision vector to get its direction */
        vCollision.divide(vCollision.magnitude());

        /* Get the relative velocity vector and calculate the collision speed, then dampen the speed by the restituion */
        vRelativeVelocity.setVec(velocity.getX() - circle->getVel().getX(), 
                               velocity.getY() - circle->getVel().getY());
        speed = vRelativeVelocity.getX() * vCollision.getX() + vRelativeVelocity.getY() * vCollision.getY();
        speed *= restitution;

        /* If the speed is less than 0 (object moving away), just return here */
        if (speed < 0){
            return;
        }

        /* Calculate impulse, which will be used to calculate each objects momentum */ 
        impulse = 2 * speed / (circle->getMass() + mass);
        momentum1 = VecMath::mult(vCollision, impulse * circle->getMass()); 
        momentum2 = VecMath::mult(vCollision, impulse * mass); 

        /* Subtract the momentum1 from this objects velocity */
        velocity.sub(momentum1);

        /* Add the momentum2 to the other objects velocity */
        obj2VelCpy = circle->getVel();
        obj2VelCpy.add(momentum2);
        circle->setVel(obj2VelCpy);
    }

    /* Constrains a between b and c */
    double constrain(double a, double b, double c)
    {
        if (a<b)
            return b;
        else if(a > c)
            return c;
        else
            return a;
    }

    /* Both Attract and Repel force algorithms come from NoC book */
    /* F = (G(m1 * m2)/r^2) * r hat */
    void Attract(Circle* circ)
    {
        Vec2 force = this->position;
        force.sub(circ->position);
        double distanceSq = constrain(force.magnitudeSq(), 25, 2500);
        double G = 1.3;
        double strength = ((this->getMass() * circ->getMass())/distanceSq)*G;
        force.setMag(strength);
        circ->ApplyForce(force);
    }

    void Repel(Circle* circ)
    {
        Vec2 force = this->position;
        force.sub(circ->position);
        double distanceSq = constrain(force.magnitudeSq(), 25, 2500);
        int G = 1.3;
        double strength = ((this->getMass() * circ->getMass())/distanceSq)*G;
        force.setMag(-1*(strength));
        circ->ApplyForce(force);
    }

    /*
    Fdrag = -1/2 * p * v^2 * A * Cd * v-hat (vel unit vec)
    -1/2 = opposite direction! (1/2 is irrelevant for our purpose)
    p    = greek letter rho, refers to density of liquid
    v^2  = speed of object (magnitude of velocity!)^2
    A    = Frontal area of object pushing through liquid. Since we only operate on circles, this is irrelevant. 
    Cd   = coefficient of drag! How much drag will be applied?
    v-hat= velocity vector normalized (to become a unit vector, or v-hat) 
    https://en.wikipedia.org/wiki/Drag_equation */
    // One thing we can do with this is create "water". A box with collisions turned off and a slight opacity, so that when objects pass through it, the box's drag force is applied to each object inside. 
    // Calculates a drag force to be applied to a body of mass
    void Drag(double c)
    {
       Vec2 drag = this->velocity;
       drag.Normalize();
       drag.multiply(-1);
       double speedSq = this->velocity.magnitudeSq();
       drag.setMag(c*speedSq);
       this->ApplyForce(drag);
    }

    /* KINETIC FRICTION (as opposed to static friction) */
    // Ffrict = -µ * N * v-hat
    // -µ (mu) = coefficient of friction (ice, rubber, etc)
    // N       = normal force that the object is on
    // v-hat   = velocity unit vector
    // https://en.wikipedia.org/wiki/Friction
    void Friction(int height)
    {
        //check if bottom of canvas, have the HEIGHT macro in main
        double diff = height - (this->position.getY() + this->getRadius());
        double mu = 0.01;
        if (diff < 1)
        {
            Vec2 friction = this->velocity;
            friction.Normalize();
            friction.multiply(-1);
            double normal = this->mass;
            friction.setMag(mu*normal);
            this->ApplyForce(friction);
        }
    }

    void setCollisionWithBoundary(bool collided) { collisionWithBoundary = collided; }
    void setCollisionWithCircle(bool collided) { collisionWithCircle = collided; }
    bool getCollisionWithBoundary() { return collisionWithBoundary; }
    bool getCollisionWithCircle() { return collisionWithCircle; }
    double getRadius() { return radius; }

    bool getTopCollision() { return topCollision; }
    bool getBottomCollision() { return bottomCollision; }
    bool getLeftCollision() { return leftCollision; }
    bool getRightCollision() { return rightCollision; }

    bool getAtracter(){return attracter;}
    bool getRepulser(){return repulser;}

    void resetCollisions() {
        topCollision = false;
        bottomCollision = false;
        leftCollision = false;
        rightCollision = false;
    }

};

#endif