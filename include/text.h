#ifndef _TEXT_
#define _TEXT_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

class Text {
    
public:
    SDL_Rect* rect;

    Text () {
        rect = nullptr;
    }

    Text (SDL_Rect* r, const char* str) {
        rect = r;
    }

    void SetRect(SDL_Rect* r) {
        rect = r;
    }

    void Render (SDL_Renderer* renderer, SDL_Color color, TTF_Font* font, const char* msg) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, msg, color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_RenderCopy(renderer, message, NULL, rect);
    }

};

#endif