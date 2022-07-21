#pragma once
#ifndef _Command_
#define _Command_

//abstract class for the command pattern. concrete commands inherit from here
class Command
{
public:
    virtual void execute()=0;
};
#endif