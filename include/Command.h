#ifndef _Command_
#define _Command_
#include "Simulation.h"
class Command
{
public:
//    Command(Simulation sim)
//    {
//    }
    virtual void execute()=0;
};
#endif