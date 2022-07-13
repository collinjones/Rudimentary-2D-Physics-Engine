#ifndef _EMITTER_
#define _EMITTER_

#include <SDL2/SDL.h>
#include "circle.h"
#include "vec2.h"

class Emitter {
private:
    Vec2 pos;
public:
    Emitter(double x, double y) {
        pos.setVec(x, y);
    }

    void Emit(vector<Circle*> *circles) {
        if(circles->size() <= 2) {
            Vec2 a(0, 0);
            Vec2 vel(rand() % 3 + 1 , rand() % 3 + 1);
            SDL_Color color;
            color.r = rand() % 255 + 1;
            color.g = rand() % 255 + 1;
            color.b = rand() % 255 + 1;
            color.a = 255;
            circles->push_back(new Circle(pos, vel, a, 3, color));
            //int rdmNumber = rand()%2;
//            int rdmNumber = 0;
//            if (rdmNumber == 0)
//            {
//
//                circles->push_back(new Circle(pos, vel, a, 3, color,true));
//                rdmNumber++;
//            }
//            else
//            {
//                circles->push_back(new Circle(pos, vel, a, 3, color));
//            }
        }

    }
};

#endif