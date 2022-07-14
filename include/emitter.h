#ifndef _EMITTER_
#define _EMITTER_

#include <SDL2/SDL.h>
#include "circle.h"
#include "vec2.h"

class Emitter {

private:

    Vec2 pos;
    int numObjects;

public:

    Emitter(double x, double y) {
        pos.setVec(x, y);
        numObjects = 0;
    }

    void Emit(vector<Circle*> *circles) {
        if(numObjects <= 2) {
            Vec2 vel(rand() % 3 + 1 , rand() % 3 + 1);
            SDL_Color color;
            color.r = rand() % 255 + 1;
            color.g = rand() % 255 + 1;
            color.b = rand() % 255 + 1;
            color.a = 255;
            circles->push_back(new Circle(pos, vel, 3, color));
            numObjects++;
        }
    }
};

#endif