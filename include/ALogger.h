#pragma once
#ifndef _ALogger_
#define _ALogger_

#include <string>
#include <vector>
#include <list>

//absract class for the logger object (logger in the case of observer pattern is a subscriber/observer)
class ALogger
{
public:
    virtual void Update(string msg) = 0;
};

#endif