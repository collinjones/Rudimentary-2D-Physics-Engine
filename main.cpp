
#include "include/Simulation.h"
#include "include/Subject.h"

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

int WinMain () {

    Simulation physics_engine;

    // Check for any initialization errors
    if(physics_engine.CheckForErrors()) return EXIT_FAILURE;
    physics_engine.MainLoop(physics_engine);

    return EXIT_SUCCESS;
}