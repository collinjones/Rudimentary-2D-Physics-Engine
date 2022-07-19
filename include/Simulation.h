#pragma once
#ifndef _Simulation_
#define _Simulation_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "vec2.h"
#include "circle.h"
#include "vecMath.h"
#include "boundary.h"
#include "rectangle.h"
#include "peg.h"
#include "emitter.h"
#include "singletonRenderer.h"
#include "shapeFactory.h"
#include "button.h"
#include "toggleButton.h"
#include "displayPanel.h"
#include "slider.h"
#include "LWindow.h"
//#include "Controller.h"
//#include "ConcreteCommands.h"
//#include "Subject.h"

using namespace std;

class Simulation {

    public:
        //0: grav on, 1: grav off, 2: add normal circle, 3: add attractor, 4: add repeler
        bool LeftClick(SDL_MouseButtonEvent& b) {
            if(b.button == SDL_BUTTON_LEFT){
                if(!linePointASelected) {
                    int posX;
                    int posY;
                    SDL_GetMouseState(&posX, &posY);
                    pA.setVec(posX, posY);
                    linePointASelected = true;
                    return true;
                }
                else {
                    int posX;
                    int posY;
                    SDL_GetMouseState(&posX, &posY);
                    if(posX != pA.getX() && posY != pA.getY()) {
                        pB.setVec(posX, posY);
                        boundaries.push_back(new Boundary(pA, pB));
                        linePointASelected = false;
                        return false;
                    }

                }
            }
            return true;
        }
//
//        void PKeyPressed(SDL_KeyboardEvent& k) {
//            if(k.keysym.scancode == SDL_SCANCODE_P){
//                int posX;
//                int posY;
//                SDL_GetMouseState(&posX, &posY);
//                Vec2 pos(posX, posY);
//                pegs.push_back(shapeFact->createPeg(pos,3));
//            }
//        }
//
        bool rectLeftClick(SDL_MouseButtonEvent& b) {
             if(b.button == SDL_BUTTON_LEFT) {

                if(!boxPointASelected) {
                    SDL_GetMouseState(&boxPosX, &boxPosY);
                    boxPointASelected = true;
                    return true;
                }

                else {
                    int secondPosX;
                    int secondPosY;
                    int width;
                    int height;
                    SDL_GetMouseState(&secondPosX, &secondPosY);
                    if(secondPosX < boxPosX) {
                        width = boxPosX - secondPosX;
                        boxPosX -= width;
                    }
                    else {
                        width = secondPosX - boxPosX;
                    }

                    if(secondPosY < boxPosY) {
                        height = boxPosY - secondPosY;
                        boxPosY -= height;
                    }
                    else {
                        height = secondPosY - boxPosY;
                    }
                    rectangles.push_back(shapeFact->createRectangle(boxPosX, boxPosY, width, height));
                    boxPointASelected = false;
                    return false;
                }
            }
            return true;
        }
//
//        void AKeyPressed(SDL_KeyboardEvent& k) {
//                    if(k.keysym.scancode == SDL_SCANCODE_A){
//                        int posX;
//                        int posY;
//                        int random = rand()%6+3;
//                        SDL_GetMouseState(&posX, &posY);
//                        Vec2 vel(0,0);
//                        Vec2 pos(posX, posY);
//
//                        circles.push_back(shapeFact->createCircle(pos, vel, random,true));
//                    }
//                }
//
//        void KKeyPressed(SDL_KeyboardEvent& k)
//        {
//            if(k.keysym.scancode == SDL_SCANCODE_K)
//            {
//                int posX;
//                int posY;
//                int random = rand()%6+3;
//                SDL_GetMouseState(&posX, &posY);
//                Vec2 vel(0,0);
//                Vec2 pos(posX, posY);
//
//                circles.push_back(shapeFact->createCircle(pos, vel, random,false));
//            }
//        }

        void GeneratePachinko() {
            for (int y = 2; y < 12; y+= 1) {
                for (int x = 0; x < WIDTH; x += 50) {
                    if (y % 2 == 1){
                        Vec2 pos(x, y*50);

                        pegs.push_back(shapeFact->createPeg(pos,3));
                    }
                    else {
                        Vec2 pos(x + 25, y*50);

                        pegs.push_back(shapeFact->createPeg(pos,3));
                    }
                }
            }

            for(int x = 0; x < WIDTH; x += 50) {
                rectangles.push_back(shapeFact->createRectangle(x, HEIGHT-300, 10, 300));
            }
        }

        void GenerateSolarSystem() {
            Circle* sun = GenerateSun(WIDTH/2, HEIGHT/2, 0, 0, 10, 252, 229, 112);
            Circle* planet1 = GenerateCircle(WIDTH/2 + 100, HEIGHT/2, 0, -2, 2, 88, 199, 78);
            Circle* planet2 = GenerateCircle(WIDTH/2 + 200, HEIGHT/2, 0, -4, 4, 88, 199, 78);
            Circle* planet3 = GenerateCircle(WIDTH/2 + 300, HEIGHT/2, 0, -6, 4, 88, 199, 78);
            circles.push_back(sun);
            circles.push_back(planet1);
            circles.push_back(planet2);
            circles.push_back(planet3);
        }

        Simulation() {

            TTF_Init();  /* Init TrueType Fonts */

            /* Gravity off at startup */
            gravOn = false;
            gravity.setVec(0, 0.0);

            /* Set user control booleans */
            leftButtonHeld = false;
            linePointASelected = false;
            boxPointASelected = false;
            quit_flag = false;

            /* Creating window and renderer */
            srand (time(NULL));
            init_error = SDL_Init( SDL_INIT_VIDEO );
            window = SDL_CreateWindow("Physics Engine----",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                WIDTH, HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            /* EXAMPLE UI ELEMENTS: BUTTON, TOGGLE BUTTON, DISPLAY PANEL, and SLIDER */
//            SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
//            SDL_Color c2 = {.r = 0, .g=100, .b=200, .a=255};
//            SDL_Color c3 = {.r = 50, .g=60, .b=187, .a=255};

            /* Main setting */
            /* System of buttons */
//            toggleButtons.push_back(new ToggleButton(400, 200, 200, 25, c, c, "Toggle Status: ON", "Toggle Status: OFF"));
//            buttons.push_back(new Button(300, 200, 100, 25, c2, c2, "Event Button"));
//            displays.push_back(new DisplayPanel(100, 525, 100, 25, c3));
//            sliders.push_back(new Slider(150, 575, 50, 100));

            /* Initialize simulation on startup */
            // GeneratePachinko();
            GenerateSolarSystem();
        }

//        ~Simulation(){
//            SDL_DestroyRenderer( renderer );
//            SDL_DestroyWindow( window );
//            SDL_Quit();
//            TTF_Quit();
//            cout << "EXIT SUCCESS" << endl;
//        }

        Circle* GenerateCircle (Vec2 pos, Vec2 vel, double mass) {
            SDL_Color color;
            color.r = rand() % 255 + 1;
            color.g = rand() % 255 + 1;
            color.b = rand() % 255 + 1;
            color.a = 255;
            return new Circle(pos, vel, mass, color);
        }

        Circle* GenerateSun(int px, int py, int vx, int vy, double m, int r, int g, int b) {
            Vec2 pos(px, py);
            Vec2 vel(vx, vy);
            SDL_Color color;
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = 255;
            return new Circle(pos, vel, m, color, true);
        }

        /* Generates a "planet" - duplicate of GenerateCircle but different inputs.. */
        Circle* GenerateCircle(int px, int py, int vx, int vy, double m, int r, int g, int b) {
            Vec2 pos(px, py);
            Vec2 vel(vx, vy);
            SDL_Color color;
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = 255;
            return new Circle(pos, vel, m, color);
        }

        /* Loops through all circles to find attractors, then attracts every circle to that attractor circle */
        void AttractCircles(vector<Circle*> circles) {
            for (int c = 0; c < (int) circles.size(); c++) {
                if(circles[c]->getAtracter()) {
                    for (int k = 0; k < (int) circles.size(); k++) {
                        if (c!=k) {
                            circles[c]->Attract(circles[k]);
                        }
                    }
                }
            }
        }

        /* Loops through all circles to find repellers, then repels every circle from that repeller circle */
        void RepelCircles(vector<Circle*> circles) {
            for (int c = 0; c < (int) circles.size(); c++) {
                if(circles[c]->getRepulser()) {
                    for (int k = 0; k < (int) circles.size(); k++) {
                        if (c!=k) {
                            circles[c]->Repel(circles[k]);
                        }
                    }
                }
            }
        }

        /* If an origin point is selected, draw the outline of the box while the user moves their mouse */
        void DrawBoxOutline() {
            int tempPosX;
            int tempPosY;
            int tempWidth;
            int tempHeight;
            SDL_Rect* rect = new SDL_Rect();

            SDL_GetMouseState(&tempPosX, &tempPosY);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            if(tempPosX < boxPosX) {
                tempWidth = boxPosX - tempPosX;
                tempWidth *= -1;
            }
            else {
                tempWidth = tempPosX - boxPosX;
            }

            if(tempPosY < boxPosY) {
                tempHeight = boxPosY - tempPosY;
                tempHeight *= -1;
            }
            else {
                tempHeight = tempPosY - boxPosY;
            }

            rect->x = boxPosX;
            rect->y = boxPosY;
            rect->w = tempWidth;
            rect->h = tempHeight;
            SDL_RenderDrawRect(renderer, rect);
        }

        void DrawStaticObjects() {
            /* Draw all of the lines (boundaries) */
            for(int i = 0; i < (int) boundaries.size(); i++) {
                boundaries[i]->Draw(renderer);
            }

            for(int i = 0; i < (int) rectangles.size(); i++) {
                rectangles[i]->Draw(renderer);
            }

            for(int i = 0; i < (int) pegs.size(); i++) {
                pegs[i]->Draw(renderer);
            }

            for(int i = 0; i < (int) emitters.size(); i++) {
                emitters[i]->Emit(&circles);
            }
        }

        /* Handles additional user interaction with UI */
        void UIHandler(TTF_Font* font, SDL_Renderer * cRenderer) {

            SDL_Color White = {255, 255, 255};
            int posX;
            int posY;
            SDL_GetMouseState(&posX, &posY);
            Slider* sliderRef;

            for (int i = 0; i < (int) buttons.size(); i++) {
                buttons[i]->Update(cRenderer, posX, posY, White, font, SDL_GetMouseFocus());
            }

            for (int i = 0; i < (int) toggleButtons.size(); i++) {
                toggleButtons[i]->Update(cRenderer, posX, posY, White, font, SDL_GetMouseFocus());
            }

            for (int i = 0; i < (int) sliders.size(); i++) {
                sliders[i]->Draw(cRenderer);
                if (leftButtonHeld) {
                    sliders[i]->SetClicked(true);
                    int posX;
                    int posY;
                    SDL_GetMouseState(&posX, &posY);
                    if(sliders[i]->GetClicked()) {
                        sliders[i]->SetDinglePosition(posY);
                    }
                }
                sliderRef = sliders[i];
            }

            for (int i = 0; i < (int) displays.size(); i++) {
                string circlesSize = "Slider: " + to_string(sliderRef->GetCurrentValue());
                char const* circlesSize_char = circlesSize.c_str();
                displays[i]->Update(renderer, White, font, circlesSize_char);
            }

        }

        void buttonClicked(int type, Simulation sim)
        {
            //Controller remoteControl = new Controller();
            //GravOn turnOnGrav = new GravOn(sim);
            if (type == 0)
            {
                gravity.setVec(0, 0.1);
                gravOn = true;
            }
            else if (type ==1)
            {
                gravity.setVec(0, 0);
                gravOn = false;
            }
            else if (type ==2)
            {
                int random = rand()%3+3;
                Vec2 vel(0,0);
                Vec2 pos(200, 200);

                circles.push_back(shapeFact->createCircle(pos, vel, random));
            }
            else if (type ==3)
            {
                int random = rand()%3+3;
                Vec2 vel(0,0);
                Vec2 pos(200, 200);

                circles.push_back(shapeFact->createCircle(pos, vel, random,true));
            }
            else if (type ==4)
            {
                int random = rand()%3+3;
                Vec2 vel(0,0);
                Vec2 pos(200, 200);

                circles.push_back(shapeFact->createCircle(pos, vel, random,false));
            }
            else if (type ==5)
            {
                SDL_ShowWindow( window );
                SDL_RaiseWindow( window );
                SDL_SetWindowGrab(window, SDL_TRUE);
                EventHandler(true,1,sim);
                SDL_SetWindowGrab(window, SDL_FALSE);
             }

            else if (type ==6)
            {
                SDL_ShowWindow( window );
                SDL_RaiseWindow( window );
                EventHandler(true,2,sim);
            }
            else{
            ;
            }
        }

        //destroyer called here after leaving event handler, but why
        void EventHandler(bool drawOnMain, int boxOrLine, Simulation sim) {
            /* Check for events */

            if (drawOnMain && boxOrLine == 1)
            {
                bool loop= true;
                while(loop)
                {
                    while (SDL_PollEvent(&e)){
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            loop = LeftClick(e.button);
                        }
                    }
                }
            }
            if (drawOnMain && boxOrLine == 2)
            {
                bool loop= true;
                while(loop)
                {
                    while (SDL_PollEvent(&e)){
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            loop = rectLeftClick(e.button);
                            /* If the first point of a box was selected (R key), then continue to draw the outline of the box */
                            if (boxPointASelected) {
                                DrawBoxOutline();
                            }
                        }
                    }
                }
            }

            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                //never here
                    quit_flag = true;
                }
                //Handle window events
                for( int i = 0; i < TOTAL_WINDOWS; ++i )
                {

                    int eventHappened = -1;
                    gWindows[ i ].handleEvent( e );
                    eventHappened = gWindows[i].handleButtonClick(e);
                    buttonClicked(eventHappened,sim);
                }
            }
        }

        void ProcessCircles() {

            AttractCircles(circles);
            RepelCircles(circles);

            /* Update and render circles on screen */
            for (int c = 0; c < (int) circles.size(); c++) {

                /* Apply friction to circle if they are rolling on ground */
                circles[c]->Friction(HEIGHT);

                /* COLLISION DETECTION AND RESOLUTION */
                circles[c]->CollisionEdges(WIDTH, HEIGHT);
                circles[c]->CollisionBoundaries(boundaries);
                circles[c]->CollisionCircles(circles);
                circles[c]->CollisionPegs(pegs);
                circles[c]->CollisionRectangles(rectangles);

                /* If circle is colliding with another circle or line, don't apply gravity */
                /* This is a hacky solution to preventing objects from clipping into eachother */
                if(!circles[c]->getCollisionWithCircle()) {
                    circles[c]->ApplyForce(gravity);
                }
                else {
                    Vec2 reverseGravity(0, -0.11);
                    circles[c]->ApplyForce(reverseGravity);
                }
                if(!circles[c]->getCollisionWithBoundary()) {
                    circles[c]->ApplyForce(gravity);
                }
                else {
                    Vec2 reverseGravity(0, -0.5);
                    circles[c]->ApplyForce(reverseGravity);
                }

                /* Reset collisions flag to false and draw the circle */
                circles[c]->setCollisionWithBoundary(false);
                circles[c]->setCollisionWithCircle(false);

                /* Update the circle then draw it */
                circles[c]->Update();
                circles[c]->Draw(renderer);
            }
        }

        void handleLWUI(TTF_Font* font)
        {
            SDL_Window * currentFocus = SDL_GetMouseFocus();
            SDL_RaiseWindow(currentFocus);


            for( int i = 0; i < TOTAL_WINDOWS; ++i )
            {
                gWindows[ i ].LWUIHandler(font);
            }

        }

        void handleLWFillScreen()
        {
            for( int i = 0; i < TOTAL_WINDOWS; ++i )
            {
                gWindows[ i ].LWFillScreen();
            }
        }

        void handleLWRenderPresent()
        {
            for( int i = 0; i < TOTAL_WINDOWS; ++i )
            {
                gWindows[ i ].LWRenderPresent();
            }
        }

        /* MAIN SIMULATION LOOP */
        int MainLoop(Simulation sim) {

            TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 50);

            if( !init() )
            {
                printf( "Failed to initialize!\n" );
            }
            else
            {
                gWindows[ 1 ].init2();
                gWindows[2].init3();
                gWindows[3].init4();
            }
            while (!quit_flag) {

                FillScreen(0,0,0,255);
                handleLWFillScreen();
                EventHandler(false,-1, sim);
                //UIHandler(Sans,renderer);

                handleLWUI(Sans);

                /* Only attract and repel each circle once */
                AttractCircles(circles);
                RepelCircles(circles);
                ProcessCircles();
                DrawStaticObjects();
                handleLWRenderPresent();
                SDL_RenderPresent(renderer);
                SDL_Delay(1000 / FRAMERATE);
            }


            return 0;

        }

        void FillScreen(int r, int g, int b, int a){
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderClear(renderer);
        }

        int CheckForErrors() {

            if ( init_error < 0 ) {
                cout << "SDL Could not be initialized: " << endl;
                return EXIT_FAILURE;
            }
            if( !window ) {
                cout << "Window could not be created! SDL_Error: " << endl;
                return EXIT_FAILURE;
            }
            if( !renderer ) {
                cout << "Renderer could not be created! SDL_Error: " << endl;
                return EXIT_FAILURE;
            }
            return 0;
        }

        SDL_Window* getWindow()
        {
            return window;
        }

        void setGravOn(bool change)
        {
            gravOn = change;
        }

        void setGravity(Vec2 toChange)
        {
            gravity = toChange;
        }

        void addToCirc(Circle* circ)
        {
            circles.push_back(circ);
        }

    private:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        //SDL_Renderer* renderer;
        SDL_Event e;

        const int WIDTH = 750;
        const int HEIGHT = 700;
        const int FRAMERATE = 60;

        int init_error;
        bool quit_flag;
        bool leftButtonHeld;

        vector<Circle*> circles;
        vector<Rectangle*> rectangles;
        vector<Boundary*> boundaries;
        vector<Peg*> pegs;
        vector<Emitter*> emitters;
        vector<Button*> buttons;
        vector<ToggleButton*> toggleButtons;
        vector<DisplayPanel*> displays;
        vector<Slider*> sliders;

        Vec2 gravity;

        bool linePointASelected;
        bool boxPointASelected;
        Vec2 pA;
        Vec2 pB;

        bool gravOn;

        int boxPosX;
        int boxPosY;

        shapeFactory* shapeFact = new shapeFactory();
};
#endif