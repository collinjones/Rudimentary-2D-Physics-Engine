#ifndef _RECTANGLE_
#define _RECTANGLE_

#include <SDL2/SDL.h>
#include "boundary.h"
#include "vec2.h"

class Rectangle {

private:
    SDL_Rect rect;



    

public:
    Rectangle(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;

        

    }

    void Draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }

    void Fill(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 200, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    bool CollisionWithCircle(int cx, int cy, double rad, Vec2* closestPointToRect, bool* leftCollision, bool* rightCollision, bool* topCollision, bool* bottomCollision) {
        double testX = cx;
        double testY = cy;

        /*  If the circle is to the RIGHT of the square, check against the RIGHT edge.
            If the circle is to the LEFT of the square, check against the LEFT edge.
            If the circle is ABOVE the square, check against the TOP edge.
            If the circle is to the BELOW the square, check against the BOTTOM edge.
        */

        /* Left */
        if (cx < rect.x) { 
            *leftCollision = true; 
            testX = rect.x;
        }
        /* Right */
        else if (cx > rect.x + rect.w) {
            *rightCollision = true;
            testX = rect.x + rect.w;
        }

        /* Top */
        if (cy < rect.y) {
            *topCollision = true;
            testY = rect.y;
        }
        /* Bottom */
        else if (cy > rect.y + rect.h) {
            *bottomCollision = true;
            testY = rect.y + rect.h;
        }

        closestPointToRect->setVec(testX, testY);
        double distX = cx-testX;
        double distY = cy-testY;
        double dist = sqrt( (distX*distX) + (distY*distY) );

        if (dist <= rad) {
            /* Return true if circle is colliding with rectangle */
            return true;
        }
        /* Return false if circle is not colliding with rectangle */
        return false;
    }

    SDL_Rect getRect() { return rect; }

    
};

#endif