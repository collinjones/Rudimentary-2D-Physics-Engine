#pragma once
#ifndef _Controller_
#define _Controller_

#include <vector>

#include "Command.h"

/*
 * controller class for command pattern. Code used/altered from the book
*/
class Controller
{
    public:
       Command* userCommands[10];

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