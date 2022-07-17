#ifndef _TOGGLEBUTTON_
#define _TOGGLEBUTTON_

#include <SDL2/SDL.h>
#include <iostream>
#include "button.h"

using namespace std;

class ToggleButton : public Button {

private:
    bool activated;
    SDL_Color onColor;
    SDL_Color offColor;
    const char* offText;
    const char* onText;

public:

    ToggleButton(int x, int y, int w, int h, SDL_Color fColor, SDL_Color bColor, const char* str, const char* toggleStr) 
    : Button(x, y, w, h, fColor, bColor, str) {
        activated = false;
        offColor = fColor;
        onColor.r = fColor.r + hoverOffset;
        onColor.g = fColor.g + hoverOffset;
        onColor.b = fColor.b + hoverOffset; 
        onText = str;
        offText = toggleStr;
    }

    void ProcessClick(float px, float py) {
        if (mouseOver) {
            if (!activated) {
                cout << "clicked a toggle button ON" << endl;
                SetClickedColor();
                activated = true; 
            }
            else {
                cout << "clicked a toggle button OFF" << endl;
                SetUnclickedColor();
                activated = false;
            }
        }
    }

    void Update(SDL_Renderer* renderer, int mx, int my, SDL_Color textColor, TTF_Font* font){
        //made it here constantly
        MouseOverBehavior(renderer, mx, my);
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

    

};

#endif