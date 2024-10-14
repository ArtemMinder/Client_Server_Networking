#pragma once

#include "IWriter.h"
#include "IBuffer.h"
#include "ConsoleLogger.h"
#include <vector>
#pragma once

#include <string>


class Writer : public IWriter 
{
public:
    Writer() = default;

    void writeToBuffer(IBuffer& buffer) override
    {
        ConsoleLogger logger;
        logger.log("Writing data to buffer...");
        std::vector<char> data = getData();
        buffer.write(data);
        logger.log("Data written successfully");
    }

private:
    std::vector<char> getData() 
    {
        ConsoleLogger logger;
        logger.log("Preparing data for writing...");

        std::string dataStr = "Sample data to be written to the buffer";
        std::vector<char> data(dataStr.begin(), dataStr.end());

        return data;
    }
};