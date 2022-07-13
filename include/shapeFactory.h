#ifndef _CIRCLEFACTORY_
#define _CIRCLEFACTORY_

#include <iostream>
#include <string>
#include "circle.h"
#include "vec2.h"
#include "peg.h"


using namespace std;

class shapeFactory{

    public:
        shapeFactory(){
        ;
        }

        Circle* createCircle(Vec2 pos, Vec2 vel, double m){
            Vec2 acc(0, 0);
            SDL_Color col = {.r=255,.g=0,.b=0,.a=255};
            Circle* crc = new Circle(pos, vel, acc, m, col);
            return crc;
        }

        Circle* createCircle(Vec2 pos, Vec2 vel, double m, bool attractOrRepulse){
            Vec2 acc(0, 0);
            Circle* crc;
            if(attractOrRepulse == true)
            {
                SDL_Color col = {.r=0,.g=255,.b=0,.a=255};
                crc = new Circle(pos, vel, acc, m, col,true);
            }
            else
            {
                SDL_Color col = {.r=0,.g=0,.b=255,.a=255};
                crc = new Circle(pos, vel, acc, m, col,false);
            }
            return crc;
        }

        Peg* createPeg(Vec2 pos, int size){
            SDL_Color col = {.r=128,.g=0,.b=128,.a=255};
            Peg* pg = new Peg(pos, size, col);
            return pg;
        }

        Boundary* createBoundary(Vec2 start, Vec2 end)
        {
            Boundary* bound = new Boundary(start, end);
            return bound;
        }

        Emitter* createEmitter(double x, double y)
        {
            Emitter* emit = new Emitter(x,y);
            return emit;
        }

        Rectangle* createRectangle (int x, int y, int w, int h)
        {
            Rectangle* rect = new Rectangle(x,y,w,h);
            return rect;
        }
};

#endif