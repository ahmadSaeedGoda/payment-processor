#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Logger.h"
#include <iostream>

using namespace std;

class ConsoleLogger : public Logger
{
public:
    void log(const string &message) override
    {
        cout << message << endl;
    }
};

#endif // CONSOLE_LOGGER_H
