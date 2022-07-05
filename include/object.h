

#ifndef _OBJECT_
#define _OBJECT_ 

#include <SDL2/SDL.h>
#include "vec2.h"
#include "vecMath.h"

class Object {

    protected:
        Vec2 position; 
        Vec2 velocity;
        Vec2 acceleration;
        double mass;
        SDL_Color color;

    public:

        Object(Vec2 pos, Vec2 vel, Vec2 acc, double m, SDL_Color col) {
            position = pos;
            velocity = vel;
            acceleration = acc;
            mass = m;
            color = col;
        }

        /* Newton's Second Law: Force = Mass * Acceleration, or Acceleration = Force / Mass */
        void ApplyForce(Vec2 force) {
            VecMath::div(&force, mass);  /* Divide by the mass of the object */
            acceleration.add(force); /* We add, not set, here so that multiple forces can affect the object */
        }

        void Update() {
            /* Euler integration algorithm:
            *   1. Add acceleration to velocity
            *   2. Add velocity to position 
            *   3. Clear the (set to 0) acceleration (acceleration DOES NOT accumulate)
            */
            velocity.add(acceleration);
            position.add(velocity);
            acceleration.setVec(0, 0); // or acceleration.mult(0);
        }

        void subVel(Vec2 vel) { velocity.sub(vel); }
        void setVel(Vec2 vel) { velocity = vel; }
        
        Vec2 getPos() { return position; }
        Vec2 getVel() { return velocity; }
        Vec2 getAcc() { return acceleration; }
        double getMass() { return mass; }
        

        void Draw(SDL_Renderer* renderer);
};

#endif