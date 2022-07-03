#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "include/vec2.h"
#include "include/circle.h"
#include "include/boundary.h"
#include "include/vecMath.h"

using namespace std;

#define PI 3.14
const int WIDTH = 1000;
const int HEIGHT = 600;
const int FRAMERATE = 60;

const Vec2 gravity(0, 0.1);
vector<Circle*> circles; 

class Simulation {
    public:

        Simulation() {
            srand (time(NULL));
            quit_flag = false;
            init_error = SDL_Init( SDL_INIT_VIDEO );
            window = SDL_CreateWindow("Physics Engine",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                WIDTH, HEIGHT,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            /* Temp - initialize two circles */
            Vec2 pos1(350, 100);
            Vec2 pos2(700, 100);
            Vec2 vel(0, 0);

            circles.push_back(GenerateCircle(pos1, vel, 3));
            circles.push_back(GenerateCircle(pos2, vel, 2));
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

            Vec2 v1(200, 400);
            Vec2 v2(400, 300);
            Boundary b(v1, v2);
            
            while (!quit_flag) {

                fill_screen(0,0,0,255);
                b.Draw(renderer);

                
                /* Check for events */
                while (SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit_flag = true;
                    }
                }

                /* Update and render circles on screen */
                for (int c = 0; c < (int) circles.size(); c++) {
                    cout << "CIRCLE " << c << " - Mass: " << circles[c]->getMass() << endl;
                    circles[c]->CollisionWithLine(b);
                    circles[c]->Edges(WIDTH, HEIGHT);

                    /* == AN OBJECT FALLS (GRAVITY) AT THE SAME ACCELERATION INDEPENDENT OF ITS MASS == 
                    *
                    *  Without multiplying gravity with an objects mass, this gravity force being
                    *      applied will be divided with the objects mass in the ApplyForce method, 
                    *      causing gravity to act differently on each object. Galileo proved that 
                    *      objects will fall with the same acceleration (gravity, in this case), 
                    *      regardless of its mass. This new force is the objects weight.
                    */
                    Vec2 weight = VecMath::mult(gravity, circles[c]->getMass());
                    circles[c]->ApplyForce(weight);

                    cout << "Position:     (" << circles[c]->getPos().getX() << ", " << circles[c]->getPos().getY() << ")" << endl;
                    cout << "Velocity:     (" << circles[c]->getVel().getX() << ", " << circles[c]->getVel().getY() << ")" << endl;
                    cout << "Acceleration: (" << circles[c]->getAcc().getX() << ", " << circles[c]->getAcc().getY() << ")" << endl;

                    circles[c]->Update();
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
};


int WinMain () {

    Simulation physics_engine;

    // Check for any initialization errors
    
    if(physics_engine.check_for_errors()) return EXIT_FAILURE;
    physics_engine.main_loop();

    return EXIT_SUCCESS;
}