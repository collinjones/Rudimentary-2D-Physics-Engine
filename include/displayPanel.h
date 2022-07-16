#ifndef _DISPLAYPANEL_
#define _DISPLAYPANEL_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

#include <iostream>

class DisplayPanel {

protected:
    SDL_Rect* rect;
    SDL_Color panelColor;
    Text* text;

public:
    DisplayPanel(int x, int y, int w, int h, SDL_Color fColor) {
        rect = new SDL_Rect();
        rect->x = x;
        rect->y = y;
        rect->w = w;
        rect->h = h;
        panelColor = fColor;
        text = new Text(rect);
    }

    void Update(SDL_Renderer* renderer, SDL_Color textColor, TTF_Font* font, const char* str) {
        Draw(renderer, panelColor.r, panelColor.g, panelColor.b);
        text->Render(renderer, textColor, font, str);
    }

    void Draw(SDL_Renderer* renderer, int r, int g, int b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, rect);
        SDL_RenderDrawRect(renderer, rect);  
    }
};

#endif