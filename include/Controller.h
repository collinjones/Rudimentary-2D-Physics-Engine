#ifndef _Controller_
#define _Controller_

#include <vector>
#include "Command.h"


class Controller
{
    public:
       const int NUMCOMMANDS = 7;
       vector<Command*> userCommands;

       Controller()
       {

//           for (int k = 0; k<NUMCOMMANDS; k++)
//           {
//                userCommands[k] = noCommand;
//           }
       }

       void setCommand (int slot, Command* userCommand)
       {
            userCommands[slot] = userCommand;
       }

       void buttonPushed(int slot)
       {
            userCommands[slot]->execute();
       }
    private:

};
#endif