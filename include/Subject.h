#ifndef _SUBJECT_
#define _SUBJECT_
//code adapted from: https://www.codeproject.com/articles/328365/understanding-and-implementing-observer-pattern-2
#include <string>
#include <vector>
#include <list>

#include "Logger.h"

class Subject {
    public:
        vector<Logger*> listOfSubs;
        void Attach(Logger *loggers);
        //void Detach(Logger *loggers);
        void Notify(string msg);
};

void Subject::Attach(Logger *loggers)
{
    listOfSubs.push_back(loggers);
}
//void Subject::Detach(Logger *loggers)
//{
//    listOfSubs.erase(std::remove(listOfSubs.begin(), listOfSubs.end(), loggers), listOfSubs.end());
//}
void Subject::Notify(string msg)
{
    for(vector<Logger*>::const_iterator iter = listOfSubs.begin(); iter != listOfSubs.end(); ++iter)
        {
            if(*iter != 0)
            {
                (*iter)->Update(msg);
            }
        }
}
//class ConcreteSub : public Subject
//{
//    public:
//
//};
#endif