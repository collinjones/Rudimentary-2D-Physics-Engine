#ifndef _TEXT_
#define _TEXT_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

class Text {
    
private:

    SDL_Rect* rect;

public:
    Text () {
        rect = nullptr;
    }

    Text (SDL_Rect* r) {
        rect = r;
    }

    void SetRect(SDL_Rect* r) {
        rect = r;
    }

    void Render (SDL_Renderer* renderer, SDL_Color color, TTF_Font* font, const char* msg) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, msg, color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect copy = *rect;

        /* Centering text */
        copy.x += rect->w * .10;
        copy.w -= rect->w * .20;
        SDL_RenderCopy(renderer, message, NULL, &copy);
    }

};

#endif