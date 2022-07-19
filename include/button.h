#ifndef _BUTTON_
#define _BUTTON_

#include <SDL2/SDL.h>
#include <iostream>
#include "Subject.h"
#include "text.h"

using namespace std;

class Button {

protected:
    SDL_Rect button;

    SDL_Color fillColor;
    SDL_Color hoverColor;
    SDL_Color originalColor;
    SDL_Color borderColor;
    const int hoverOffset = 50;
    
    bool mouseOver;
    const char* str;
    Text* text;
    int id;

    //error coming from the fact we try to perform an operation
    //not in a function. So move to another funciton
    Subject *subjected = new Subject();
    //Subject::subjected->Attach(Logger::getInstance());
public:

    Button(int x, int y, int w, int h, SDL_Color fColor, SDL_Color bColor, const char* s, int myID) {
        button.x = x;
        button.y = y;
        button.w = w;
        button.h = h;
        fillColor = fColor;
        originalColor = fillColor;
        hoverColor.r = fColor.r + hoverOffset;
        hoverColor.g = fColor.g + hoverOffset;
        hoverColor.b = fColor.b + hoverOffset;
        borderColor = bColor;
        mouseOver = false;
        str = s;
        text = new Text(&button);
        id = myID;
    }

    void Update(SDL_Renderer* renderer, int mx, int my, SDL_Color textColor, TTF_Font* font, SDL_Window* currentWin) {
        MouseOverBehavior(renderer, mx, my, currentWin);
        text->Render(renderer, textColor, font, str);
    }

    void Draw(SDL_Renderer* renderer, int r, int g, int b) {
//continuosly in draw it seems, rgb: 100,100,0
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &button);
        SDL_RenderDrawRect(renderer, &button); 
    }

    int ProcessClick(float px, float py, int whichButton) {
        if (mouseOver) {
            if (whichButton ==2)
            {
                cout << "clicked the normal circle button" << endl;
                return 2;
            }
            else if (whichButton ==3)
            {
                cout << "clicked the attracter circle button" << endl;
                return 3;
            }
            else if (whichButton ==4)
            {
                cout << "clicked the repeler circle button" << endl;
                return 4;
            }
            else if (whichButton ==5)
            {
                cout << "clicked the add line button" << endl;
                return 5;
            }
            else if (whichButton ==6)
            {
                cout << "clicked the add box button" << endl;
                return 6;
            }
            else
            {;
            }
        }
        return -1;
    }

    void MouseOverBehavior(SDL_Renderer* renderer, float px, float py, SDL_Window* currentWin) {
        if (IsMouseOver(px, py) && SDL_GetMouseFocus() == currentWin) {
            Draw(renderer, hoverColor.r, hoverColor.g, hoverColor.b);
        }
        else {
            Draw(renderer, fillColor.r, fillColor.g, fillColor.b);
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

    int getID()
    {
        return id;
    }

};

#endif