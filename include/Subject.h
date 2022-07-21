#pragma once
#ifndef _SUBJECT_
#define _SUBJECT_
//code adapted from: https://www.codeproject.com/articles/328365/understanding-and-implementing-observer-pattern-2
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Logger.h"
/*
 * class that is part of the observer pattern. Writes
 * messages to the console and an external file.
*/
class Subject {
    public:
        vector<Logger> listOfSubs;
        void Attach(Logger loggers);
        void Notify(string msg);
};

void Subject::Attach(Logger loggers)
{
    listOfSubs.push_back(loggers);
}
//for date https://www.tutorialspoint.com/how-to-get-current-time-and-date-in-cplusplus

void Subject::Notify(string msg)
{
    time_t now = time(0);
    char *date = ctime(& now);
    ofstream outputFiles;
    outputFiles.open("results.txt" ,std::ofstream::out | std::ofstream::app );

    for(size_t k = 0; k < listOfSubs.size(); ++k)
        {
            listOfSubs[k].Update(msg);
            outputFiles<<msg<<" @ "<<date<< "\n";
        }
}

#endif