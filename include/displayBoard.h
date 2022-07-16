#ifndef _DISPLAYBOARD_
#define _DISPLAYBOARD_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class DisplayBoard {

protected:
    SDL_Rect rect;
    SDL_Color fillColor;
    SDL_Color borderColor;
    Text* text;

public:

    DisplayBoard(int x, int y, int w, int h, SDL_Color fColor, SDL_Color bColor, const char* str) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        fillColor = fColor;
        borderColor = bColor;
        text = new Text(&rect, str);
    }

    void Update(SDL_Renderer* renderer, SDL_Color textColor, TTF_Font* font, const char* str) {
        Draw(renderer);
        text->Render(renderer, textColor, font, str);
    }

    void Draw(SDL_Renderer* renderer) {
        SDL_RenderDrawRect(renderer, &rect);  
    }

    void Fill(SDL_Renderer* renderer, int r, int g, int b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect); 
    }

};

#endif