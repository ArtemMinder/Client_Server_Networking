#pragma once

#include "IReader.h"
#include "IBuffer.h"
#include "ConsoleLogger.h"
#include <vector>

class Reader : public IReader 
{
public:
    Reader() = default;

    void readFromBuffer(IBuffer& buffer) override 
    {
        ConsoleLogger logger;
        logger.log("Reading data from buffer...");
        std::vector<char> data = buffer.read();
        logger.log("Data read successfully");
        processData(data);
    }

private:
    void processData(const std::vector<char>& data) 
    {
        ConsoleLogger logger;
        logger.log("Processing read data...");

        std::string result(data.begin(), data.end());
        logger.log("Processed data: " + result);
    }
};