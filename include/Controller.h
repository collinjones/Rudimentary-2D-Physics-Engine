#pragma once
#ifndef _Controller_
#define _Controller_

#include <vector>

#include "Command.h"

class Controller
{
    public:
       Command* userCommands[7];

       Controller()
       {
       }

       void setCommand (int slot, Command* commandToAdd)
       {
            userCommands[slot] = commandToAdd;
       }

       void buttonPushed(int slot)
       {
            userCommands[slot]->execute();
       }
    private:

};
#endif