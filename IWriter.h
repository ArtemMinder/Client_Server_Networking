#pragma once

#include "IBuffer.h"

class IWriter 
{
public:
    virtual ~IWriter() = default;
    virtual void writeToBuffer(IBuffer& buffer) = 0;
};