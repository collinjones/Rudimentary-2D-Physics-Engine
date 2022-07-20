#pragma once
#ifndef _Command_
#define _Command_
//#include "Simulation.h"
class Command
{
public:
//Simulation simulation();
//    Command(Simulation sim)
//    {
//        this->simulation = sim;
//    }
    virtual void execute()=0;
};
#endif