#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "include/vec2.h"
#include "include/circle.h"
#include "include/vecMath.h"
#include "include/boundary.h"
#include "include/rectangle.h"
#include "include/peg.h"
#include "include/emitter.h"
#include "include/singletonRenderer.h"
#include "include/shapeFactory.h"
#include "include/button.h"
#include "include/toggleButton.h"
#include "include/displayBoard.h"

using namespace std;

class Simulation {
    public:

        void LeftClick(SDL_MouseButtonEvent& b) {
            if(b.button == SDL_BUTTON_LEFT){
                int posX;
                int posY;
                SDL_GetMouseState(&posX, &posY);
                for (int i = 0; i < (int) buttons.size(); i++) {
                    buttons[i]->ProcessClick(posX, posY);
                }
            }

        }

        void RightClick(SDL_MouseButtonEvent& b) {
            if(b.button == SDL_BUTTON_RIGHT){
                int posX;
                int posY;
                SDL_GetMouseState(&posX, &posY);
                emitters.push_back(shapeFact->createEmitter((double) posX, (double) posY));
            }

            // int posX;
            // int posY;
            // SDL_GetMouseState(&posX, &posY);
            // SDL_Color color;
            // color.r = rand() % 255 + 1;
            // color.g = rand() % 255 + 1;
            // color.b = rand() % 255 + 1;
            // color.a = 255;
            // circles.push_back(new Circle(Vec2(posX, posY), Vec2(0, 0), Vec2(0, 0), 3, color));
        }

        void GKeyPressed(SDL_KeyboardEvent& k) {
            if(k.keysym.scancode == SDL_SCANCODE_G){
                if(!gravOn) {
                    gravity.setVec(0, 0.1);
                    gravOn = true;
                }
                else{
                    gravity.setVec(0, 0);
                    gravOn = false;
                }       
            }
        }

        void PKeyPressed(SDL_KeyboardEvent& k) {
            if(k.keysym.scancode == SDL_SCANCODE_P){
                int posX;
                int posY;
                SDL_GetMouseState(&posX, &posY);
                Vec2 pos(posX, posY);

                pegs.push_back(shapeFact->createPeg(pos,3));
            }
        }

        void RKeyHeld(SDL_KeyboardEvent& k) {
            if (k.keysym.scancode == SDL_SCANCODE_R) {

                if(!boxPointASelected) {
                    SDL_GetMouseState(&boxPosX, &boxPosY);
                    boxPointASelected = true;
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
                }
            }
        }

        void AKeyPressed(SDL_KeyboardEvent& k) {
                    if(k.keysym.scancode == SDL_SCANCODE_A){
                        int posX;
                        int posY;
                        int random = rand()%6+3;
                        SDL_GetMouseState(&posX, &posY);
                        Vec2 vel(0,0);
                        Vec2 pos(posX, posY);

                        circles.push_back(shapeFact->createCircle(pos, vel, random,true));
                    }
                }

        void KKeyPressed(SDL_KeyboardEvent& k)
        {
            if(k.keysym.scancode == SDL_SCANCODE_K)
            {
                int posX;
                int posY;
                int random = rand()%6+3;
                SDL_GetMouseState(&posX, &posY);
                Vec2 vel(0,0);
                Vec2 pos(posX, posY);

                circles.push_back(shapeFact->createCircle(pos, vel, random,false));
            }
        }

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
            
            TTF_Init();
            gravOn = false;
            gravity.setVec(0, 0);
            linePointASelected = false;
            boxPointASelected = false;
            srand (time(NULL));
            quit_flag = false;
            init_error = SDL_Init( SDL_INIT_VIDEO );
            window = SDL_CreateWindow("Physics Engine",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                WIDTH, HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_Color c = {.r = 100, .g=100, .b=0, .a=255};
            SDL_Color c2 = {.r = 0, .g=100, .b=200, .a=255};
            SDL_Color c3 = {.r = 50, .g=100, .b=200, .a=255};
            buttons.push_back(new ToggleButton(400, 200, 100, 25, c, c, "Gravity On", "Gravity Off"));
            buttons.push_back(new Button(300, 200, 100, 25, c2, c2, "Create Circle"));
            displays.push_back(new DisplayBoard(500, 200, 100, 25, c3, c3, "Circles: "));
            // GeneratePachinko();
            GenerateSolarSystem();

        }

        ~Simulation(){
            SDL_DestroyRenderer( renderer );
            SDL_DestroyWindow( window );
            SDL_Quit();
            cout << "EXIT SUCCESS" << endl;
        }

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

        void HandleUI(TTF_Font* font) {
            for (int i = 0; i < (int) buttons.size(); i++) {
                int posX;
                int posY;
                SDL_GetMouseState(&posX, &posY);
                SDL_Color White = {255, 255, 255};
                buttons[i]->Update(renderer, posX, posY, White, font);
            }
            for (int i = 0; i < (int) displays.size(); i++) {
                SDL_Color White = {255, 255, 255};
                string c_size = "Circles: " + std::to_string(circles.size());
                char const* c_char = c_size.c_str();
                displays[i]->Update(renderer, White, font, c_char);
            }
        }

        void EventHandler() {
            /* Check for events */
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit_flag = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    LeftClick(e.button);
                    RightClick(e.button);
                    
                }
                if (e.type == SDL_KEYDOWN) {
                    RKeyHeld(e.key);
                    PKeyPressed(e.key);
                    AKeyPressed(e.key);
                    KKeyPressed(e.key);
                    GKeyPressed(e.key);
                }
            }
        }

        void ProcessCircles() {
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

        /* MAIN SIMULATION LOOP */
        int MainLoop() {
            TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);\
            
            while (!quit_flag) {
                FillScreen(25,25,25,255);
                EventHandler();
                HandleUI(Sans);

                /* Only attract and repel each circle once */
                AttractCircles(circles);
                RepelCircles(circles);

                ProcessCircles();

                /* If the first point of a box was selected (R key), then continue to draw the outline of the box */
                if (boxPointASelected) {
                    DrawBoxOutline();
                }

                /* Draw the static objects, present the renderer, then delay by 1sec/FRAMERATE */
                DrawStaticObjects();
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
        
    private:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        //SDL_Renderer* renderer;
        SDL_Event e;

        const int WIDTH = 800;
        const int HEIGHT = 800;
        const int FRAMERATE = 60;

        int init_error;
        bool quit_flag;

        vector<Circle*> circles;
        vector<Rectangle*> rectangles; 
        vector<Boundary*> boundaries;  
        vector<Peg*> pegs;
        vector<Emitter*> emitters;

        vector<Button*> buttons;
        vector<DisplayBoard*> displays;

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


int WinMain () {

    Simulation physics_engine;

    // Check for any initialization errors
    if(physics_engine.CheckForErrors()) return EXIT_FAILURE;
    physics_engine.MainLoop();

    return EXIT_SUCCESS;
}