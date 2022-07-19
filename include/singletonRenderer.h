#pragma once
#ifndef _SINGLETONRENDERER_
#define _SINGLETONRENDERER_

#include <SDL2/SDL.h>

using namespace std;

class singletonRenderer{
    private:
        static SDL_Renderer* renderer;
        singletonRenderer(){;}
    public:
        static SDL_Renderer* getRenderer(SDL_Window* window)
        {
            if (renderer == NULL)
            {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            }
            return renderer;
        }
};
#endif
