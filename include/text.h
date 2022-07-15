#ifndef _TEXT_
#define _TEXT_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

class Text {
public:
    SDL_Rect* rect;
    const char* text;

    Text () {
        rect = nullptr;
    }

    Text (SDL_Rect* r, const char* str) {
        rect = r;
        text = str;
    }

    void SetRect(SDL_Rect* r) {
        rect = r;
    }

    void SetText(const char* str) {
        text = str;
    }

    void Render (SDL_Renderer* renderer, SDL_Color color, TTF_Font* font) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_RenderCopy(renderer, message, NULL, rect);
    }

};

#endif