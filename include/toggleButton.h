#pragma once
#ifndef _TOGGLEBUTTON_
#define _TOGGLEBUTTON_

#include <SDL2/SDL.h>
#include <iostream>
#include "button.h"
#include "Subject.h"

using namespace std;

class ToggleButton : public Button {

private:
    bool activated;
    SDL_Color onColor;
    SDL_Color offColor;
    const char* offText;
    const char* onText;
    int id;
public:

    ToggleButton(int x, int y, int w, int h, SDL_Color fColor, SDL_Color bColor, const char* str, const char* toggleStr, int myID)
    : Button(x, y, w, h, fColor, bColor, str, myID) {
        activated = false;
        offColor = fColor;
        onColor.r = fColor.r + hoverOffset;
        onColor.g = fColor.g + hoverOffset;
        onColor.b = fColor.b + hoverOffset; 
        onText = str;
        offText = toggleStr;
        id = myID;
    }

    int ProcessClick(float px, float py) {
        if (mouseOver) {
            if (!activated) {
                cout << "clicked a toggle button ON" << endl;
                SetClickedColor();
                activated = true;
                return 0;
            }
            else {
                cout << "clicked a toggle button OFF" << endl;
                SetUnclickedColor();
                activated = false;
                return 1;
            }
        }
        return -1;
    }

    void Update(SDL_Renderer* renderer, int mx, int my, SDL_Color textColor, TTF_Font* font, SDL_Window* currentWin){
        //made it here constantly
        MouseOverBehavior(renderer, mx, my, currentWin);
       //made it here constantly
        if (!activated) {
            text->Render(renderer, textColor, font, offText);
        }
        else {
            text->Render(renderer, textColor, font, onText);
        }
        
    }

    void SetClickedColor() {
        fillColor = onColor;
    }

    void SetUnclickedColor() {
        fillColor = offColor;
    }

    void Draw(SDL_Renderer* renderer, int r, int g, int b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &button);
        SDL_RenderDrawRect(renderer, &button);  
    }

    int getID()
    {
        return id;
    }
};

#endif