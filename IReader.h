#pragma once

#include "IBuffer.h"

class IReader 
{
public:
    virtual ~IReader() = default;
    virtual void readFromBuffer(IBuffer& buffer) = 0;
};