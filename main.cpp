
#include "include/Simulation.h"
#include "include/Controller.h"
#include "include/ConcreteCommands.h"


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		if( !gWindows[ 0 ].init1() )
		{
			printf( "Window 0 could not be created!\n" );
			success = false;
		}
	}

	return success;
}

void close()
{
	//Destroy windows
	for( int i = 0; i < TOTAL_WINDOWS; ++i )
	{
		gWindows[ i ].free();
	}

	//Quit SDL subsystems
	SDL_Quit();
}

Controller* createController(Simulation sim)
{
    Controller* ControlGUI = new Controller();

    GravOff* turnOffGrav = new GravOff(sim);

    ControlGUI->setCommand(0,turnOffGrav);
    return ControlGUI;
}

int WinMain () {

    Simulation physics_engine;


    // Check for any initialization errors
    if(physics_engine.CheckForErrors()) return EXIT_FAILURE;
    Controller* physics_engine_controller = createController(physics_engine);
    physics_engine.MainLoop(physics_engine,physics_engine_controller);

    return EXIT_SUCCESS;
}