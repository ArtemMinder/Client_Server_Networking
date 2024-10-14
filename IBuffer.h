#pragma once

#include <vector>

class IBuffer 
{
public:
    virtual ~IBuffer() = default;
    virtual void write(const std::vector<char>& data) = 0;
    virtual std::vector<char> read() = 0;
};
