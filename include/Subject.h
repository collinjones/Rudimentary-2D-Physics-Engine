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

class Subject {
    public:
        vector<Logger> listOfSubs;
        void Attach(Logger loggers);
        //void Detach(Logger *loggers);
        void Notify(string msg);
//        ofstream outputFiles;
};

void Subject::Attach(Logger loggers)
{

//    if (outputFiles.is_open())
//    {
//        cout<<"here";
//    }

    listOfSubs.push_back(loggers);
}
//void Subject::Detach(Logger *loggers)
//{
//    listOfSubs.erase(std::remove(listOfSubs.begin(), listOfSubs.end(), loggers), listOfSubs.end());
//}
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
//class ConcreteSub : public Subject
//{
//    public:
//
//};
#endif