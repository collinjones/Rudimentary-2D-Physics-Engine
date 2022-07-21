#pragma once
#ifndef _Logger_
#define _Logger_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "ALogger.h"
/*
 * the concrete logger class. It uses the singleton patter (the private constructer, lazy instantiation, and
 * unique getter. The logger is also part of the observer pattern (the observer/subscriber). The subject
 * is the publisher/subject.
*/
class Logger : public ALogger
{
public:
    void Update(string msg);
    //code from https://stackoverflow.com/questions/19130021/how-to-declare-an-static-instance-of-a-class-in-c
    static Logger &getInstance() {static Logger uniqueLogger; return uniqueLogger;}
private:
    Logger()
    {;}
};
void Logger::Update(string msg)
{
    cout << msg << endl;
}

#endif