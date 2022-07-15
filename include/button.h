#ifndef _BUTTON_
#define _BUTTON_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "text.h"

using namespace std;

class Button {

protected:
    SDL_Rect button;
    SDL_Color fillColor;
    SDL_Color borderColor;
    bool mouseOver;
    int hoverOffset;
    Text* text;

public:

    Button(int x, int y, int w, int h, SDL_Color fColor, SDL_Color bColor, const char* str) {
        button.x = x;
        button.y = y;
        button.w = w;
        button.h = h;
        fillColor = fColor;
        hoverOffset = 50;
        borderColor = bColor;
        mouseOver = false;
        text = new Text(&button, str);
    }

    void Update(SDL_Renderer* renderer, int mx, int my, SDL_Color textColor, TTF_Font* font) {
        MouseOverBehavior(renderer, mx, my);
        Draw(renderer);
        RenderText(renderer, textColor, font);
    }

    void RenderText(SDL_Renderer* renderer, SDL_Color c, TTF_Font* font) {
        text->Render(renderer, c, font);
    }

    virtual void Draw(SDL_Renderer* renderer) {
        SDL_RenderDrawRect(renderer, &button);  
    }

    void Fill(SDL_Renderer* renderer, int r, int g, int b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &button);
        SDL_RenderDrawRect(renderer, &button); 
    }

    virtual void ProcessClick(float px, float py) {
        if (mouseOver) {
            cout << "Clicked a regular button!" << endl;
        }
    }

    void MouseOverBehavior(SDL_Renderer* renderer, float px, float py) {
        if (IsMouseOver(px, py)) {
            Fill(renderer, fillColor.r + hoverOffset, fillColor.g + hoverOffset, fillColor.b + hoverOffset);
        }
        else {
            Fill(renderer, fillColor.r, fillColor.g, fillColor.b);
        }
    }

    // https://www.jeffreythompson.org/collision-detection/point-rect.php
    bool IsMouseOver(float px, float py) {
        if (px >= button.x &&        // right of the left edge AND
            px <= button.x + button.w &&   // left of the right edge AND
            py >= button.y &&        // below the top AND
            py <= button.y + button.h) {   // above the bottom
                mouseOver = true;
                return true;
        }
        mouseOver = false;
        return false;
    }

    

};

#endif