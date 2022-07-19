#ifndef _Logger_
#define _Logger_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "ALogger.h"

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
    //add write to file here
    cout << msg << endl;
}

#endif