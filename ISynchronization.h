#pragma once

class ISynchronization 
{
public:
    virtual ~ISynchronization() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void notify() = 0;
};