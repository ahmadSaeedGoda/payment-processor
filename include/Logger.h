#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <fmt/core.h>
#include <fmt/format.h>

using namespace std;

class Logger
{
public:
    virtual ~Logger() = default;

    virtual void log(const string &message) = 0;
};

#endif // PRINTER_H
