#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "include/vec2.h"
#include "include/circle.h"
#include "include/vecMath.h"
#include "include/boundary.h"

using namespace std;

#define PI 3.14
const int WIDTH = 1000;
const int HEIGHT = 600;
const int FRAMERATE = 60;

Vec2 startP(0, 200);
Vec2 endP(200, 300);

const Vec2 gravity(0, 0.1);
vector<Circle*> circles; 
vector<Boundary*> boundaries;
Boundary b(startP, endP);

class Simulation {
    public:

        void LeftClick(SDL_MouseButtonEvent& b) {
            if(b.button == SDL_BUTTON_LEFT){
                if(!pointASelected) {
                    int posX;
                    int posY;
                    SDL_GetMouseState(&posX, &posY);
                    pA.setVec(posX, posY);
                    pointASelected = true;
                }
                else {
                    int posX;
                    int posY;
                    SDL_GetMouseState(&posX, &posY);
                    pB.setVec(posX, posY);
                    boundaries.push_back(new Boundary(pA, pB));
                    pointASelected = false;
                }
            }
        }

        void RightClick(SDL_MouseButtonEvent& b) {
            if(b.button == SDL_BUTTON_RIGHT){
                Vec2 pos(WIDTH/2, HEIGHT/2);
                Vec2 vel(rand() % 10 +1, rand() % 10 +1);
                circles.push_back(GenerateCircle(pos, vel, 3));
            }
        }

        Simulation() {
            pointASelected = false;
            srand (time(NULL));
            quit_flag = false;
            init_error = SDL_Init( SDL_INIT_VIDEO );
            window = SDL_CreateWindow("Physics Engine",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                WIDTH, HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            /* Temp - initialize two circles */
            
        }

        ~Simulation(){
            SDL_DestroyRenderer( renderer );
            SDL_DestroyWindow( window );
            SDL_Quit();
            cout << "EXIT SUCCESS" << endl;
        }

        Circle* GenerateCircle (Vec2 pos, Vec2 vel, double mass) {
            Vec2 a(0, 0);

            SDL_Color color;
            color.r = 255;
            color.g = 0;
            color.b = 0;
            color.a = 255;
            return new Circle(pos, vel, a, mass, color);
        }

        /* MAIN SIMULATION LOOP */
        int main_loop() {
            
            while (!quit_flag) {
                fill_screen(0,0,0,255);
                
                /* Get positive normal of line segment */
                double dx = b.getEnd().getX() - b.getStart().getX();
                double dy = b.getEnd().getY() - b.getStart().getY();
                Vec2 n(dy, -dx);
                n.Normalize();
                
                /* Check for events */
                while (SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit_flag = true;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        LeftClick(e.button);
                        RightClick(e.button);
                    }
                }

                /* Update and render circles on screen */
                for (int c = 0; c < (int) circles.size(); c++) {
                    circles[c]->Update();
                    circles[c]->CollisionEdges(WIDTH, HEIGHT);
                    circles[c]->CollisionBoundaries(boundaries);
                    circles[c]->CollisionCircles(circles);

                    /* == AN OBJECT FALLS (GRAVITY) AT THE SAME ACCELERATION INDEPENDENT OF ITS MASS == 
                    *
                    *  Without multiplying gravity with an objects mass, this gravity force being
                    *      applied will be divided with the objects mass in the ApplyForce method, 
                    *      causing gravity to act differently on each object. Galileo proved that 
                    *      objects will fall with the same acceleration (gravity, in this case), 
                    *      regardless of its mass. This new force is the objects weight.
                    */
                   if(!circles[c]->getCollisionWithCircle()) {
                        cout << "applying gravity" << endl;
                        Vec2 weight = VecMath::mult(gravity, circles[c]->getMass());
                        circles[c]->ApplyForce(weight);
                   }
                    circles[c]->setCollisionWithBoundary(false);
                    circles[c]->setCollisionWithCircle(false);
                }

                /* Draw all of the lines (boundaries) */
                for(int i = 0; i < (int) boundaries.size(); i++) {
                    boundaries[i]->Draw(renderer);
                }
                /* Draw all of the Circles */
                for(int c = 0; c < (int) circles.size(); c++) {
                    circles[c]->Draw(renderer);
                }
                
                SDL_RenderPresent(renderer);
                SDL_Delay(1000 / FRAMERATE);
            }
            return 0;
        }

        void fill_screen(int r, int g, int b, int a){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }

        int check_for_errors() {

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
        SDL_Event e;

        int init_error;
        bool quit_flag;

        bool pointASelected;
        Vec2 pA;
        Vec2 pB;
};


int WinMain () {

    Simulation physics_engine;

    // Check for any initialization errors
    
    if(physics_engine.check_for_errors()) return EXIT_FAILURE;
    physics_engine.main_loop();

    return EXIT_SUCCESS;
}