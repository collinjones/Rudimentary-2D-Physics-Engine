
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

Controller* createController(Simulation* sim)
{
    Controller* ControlGUI = new Controller();

    GravOff* turnOffGrav = new GravOff(sim);
    GravON* turnOnGrav = new GravON(sim);
    createNormCircle* createANCircle = new createNormCircle(sim);
    createAttracter* createAACircle = new createAttracter(sim);
    createRepeler* createARCircle = new createRepeler(sim);
    createLine* createALine = new createLine(sim);
    createBox* createABox = new createBox(sim);
    SolarSystem* createASolar = new SolarSystem(sim);
    Pachinko* createPachinko = new Pachinko(sim);
    clearTheScreen* clrSc = new clearTheScreen(sim);

    ControlGUI->setCommand(0,turnOnGrav);
    ControlGUI->setCommand(1,turnOffGrav);
    ControlGUI->setCommand(2,createANCircle);
    ControlGUI->setCommand(3,createAACircle);
    ControlGUI->setCommand(4,createARCircle);
    ControlGUI->setCommand(5,createALine);
    ControlGUI->setCommand(6,createABox);
    ControlGUI->setCommand(7,createASolar);
    ControlGUI->setCommand(8,createPachinko);
    ControlGUI->setCommand(9,clrSc);

    return ControlGUI;
}

int WinMain () {
    Simulation* physics_engine = new Simulation();

    // Check for any initialization errors
    if(physics_engine->CheckForErrors()) return EXIT_FAILURE;

    Controller* physics_engine_controller = createController(physics_engine);
    physics_engine->grabController(physics_engine_controller);
    physics_engine->MainLoop(physics_engine);


    return EXIT_SUCCESS;
}