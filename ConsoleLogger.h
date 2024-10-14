#pragma once

#include "ILogger.h"
#include <iostream>

class ConsoleLogger : public ILogger 
{
public:
    void log(const std::string& message) override
    {
        std::cout << message << std::endl;
    }
};