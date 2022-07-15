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
                SetClickedColor();
                text->SetText(onText);
                activated = true; 
            }
            else {
                SetUnclickedColor();
                text->SetText(offText);
                activated = false;
            }
            
        }
    }

    void SetClickedColor() {
        fillColor = onColor;
    }

    void SetUnclickedColor() {
        fillColor = offColor;
    }

    void Draw(SDL_Renderer* renderer) {
        SDL_RenderDrawRect(renderer, &button);  
    }

    

};

#endif