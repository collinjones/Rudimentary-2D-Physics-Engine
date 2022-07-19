#ifndef _ConcreteCommands_
#define _ConcreteCommands_

#include <stdlib.h>     /* srand, rand */
#include "Command.h"
#include "vec2.h"
#include "shapeFactory.h"
#include "Simulation.h"

class NoCommand : public Command
{
    public:
        void execute(){;
        }
};

//class GravOff : public Command
//{
//public:
//    Simulation simulation;
//    GravOff(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        Vec2 acc(0,0.0);
//        simulation->setGravity(acc);
//        simulation->setGravOn(false);
//    }
//};

//class GravON : public Command
//{
//public:
//    Simulation simulation;
//
//    GravON(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        Vec2 acc(0,0.1);
//        simulation.setGravity(acc);
//        simulation.setGravOn(true);
//    }
//};
//
//class createNormCircle : public Command
//{
//public:
//    Simulation simulation;
//    shapeFactory* shapeFact = new shapeFactory();
//    createNormCircle(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        int random = rand()%3+3;
//        Vec2 vel(0,0);
//        Vec2 pos(200, 200);
//
//        simulation.addToCirc(shapeFact->createCircle(pos, vel, random));
//    }
//};
//class createAttracter : public Command
//{
//public:
//    Simulation simulation;
//    shapeFactory* shapeFact = new shapeFactory();
//    createAttracter(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        int random = rand()%3+3;
//        Vec2 vel(0,0);
//        Vec2 pos(200, 200);
//
//        simulation.addToCirc(shapeFact->createCircle(pos, vel, random,true));
//    }
//};
//class createRepeler : public Command
//{
//public:
//    Simulation simulation;
//    shapeFactory* shapeFact = new shapeFactory();
//    createRepeler(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        int random = rand()%3+3;
//        Vec2 vel(0,0);
//        Vec2 pos(200, 200);
//
//        simulation.addToCirc(shapeFact->createCircle(pos, vel, random,false));
//    }
//};
//
//class createLine : public Command
//{
//public:
//    Simulation simulation;
//
//    createLine(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        SDL_ShowWindow( simulation.getWindow() );
//        SDL_RaiseWindow( simulation.getWindow() );
//        SDL_SetWindowGrab(simulation.getWindow(), SDL_TRUE);
//        simulation.EventHandler(true,1,simulation);
//        SDL_SetWindowGrab(simulation.getWindow(), SDL_FALSE);
//    }
//};
//
//class createBox : public Command
//{
//public:
//    Simulation simulation;
//
//    createBox(Simulation mySimulation)
//    {
//        this.simulation = mySimulation;
//    }
//
//    void execute()
//    {
//        SDL_ShowWindow( simulation.getWindow() );
//        SDL_RaiseWindow( simulation.getWindow()  );
//        simulation.EventHandler(true,2,simulation);
//    }
//};
#endif
