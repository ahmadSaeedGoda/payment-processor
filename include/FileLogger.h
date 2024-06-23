#ifndef FILE_Logger_H
#define FILE_Logger_H

#include "Logger.h"
#include <fstream>
#include <iostream>

using namespace std;

class FileLogger : public Logger
{
public:
    explicit FileLogger(const string &filename)
    {
        logFile.open(filename, ios::app);
    }

    ~FileLogger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void log(const string &message) override
    {
        if (logFile.is_open())
        {
            logFile << message << endl;
        }
    }

private:
    ofstream logFile;
};

#endif // FILE_Logger_H
