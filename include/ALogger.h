#ifndef _ALogger_
#define _ALogger_

#include <string>
#include <vector>
#include <list>

class ALogger
{
public:
    virtual void Update(string msg) = 0;
};

#endif