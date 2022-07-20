#pragma once
#ifndef _ConcreteCommands_
#define _ConcreteCommands_

#include <stdlib.h>     /* srand, rand */
#include "Command.h"
#include "vec2.h"
#include "shapeFactory.h"
//#include "Simulation.h"

class NoCommand : public Command
{
    public:
        void execute(){;
        }
};

class GravOff : public Command
{
public:
    GravOff(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        Vec2 acc(0,0.0);
        simulation->setGravityOff();
        simulation->setGravOn(false);
    }
private:
     Simulation* simulation;
};

class GravON : public Command
{
public:
    GravON(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
    cout<<"here ";
        Vec2 acc(0,0.1);
        simulation->setGravityOn();
        simulation->setGravOn(true);
    }
private:
     Simulation* simulation;
};

class createNormCircle : public Command
{
public:
    createNormCircle(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        SDL_ShowWindow( simulation->getWindow() );
        SDL_RaiseWindow( simulation->getWindow() );
        simulation->EventHandler(true,3,3);
    }
private:
     Simulation* simulation;
     shapeFactory* shapeFact = new shapeFactory();
};

class createAttracter : public Command
{
public:
    createAttracter(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        SDL_ShowWindow( simulation->getWindow() );
        SDL_RaiseWindow( simulation->getWindow() );
        simulation->EventHandler(true,3,1);
    }
private:
     Simulation* simulation;
     shapeFactory* shapeFact = new shapeFactory();
};

class createRepeler : public Command
{
public:
    createRepeler(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        SDL_ShowWindow( simulation->getWindow() );
        SDL_RaiseWindow( simulation->getWindow() );
        simulation->EventHandler(true,3,2);
    }
private:
     Simulation* simulation;
     shapeFactory* shapeFact = new shapeFactory();
};

class createLine : public Command
{
public:
    createLine(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        SDL_ShowWindow( simulation->getWindow() );
        SDL_RaiseWindow( simulation->getWindow() );
        simulation->EventHandler(true,1,-1);
    }
private:
     Simulation* simulation;
};
class createBox : public Command
{
public:
    createBox(Simulation* mySimulation) : simulation (mySimulation)
    {
    }

    void execute()
    {
        SDL_ShowWindow( simulation->getWindow() );
        SDL_RaiseWindow( simulation->getWindow()  );
        simulation->EventHandler(true,2,-1);
    }
private:
     Simulation* simulation;
};
#endif
