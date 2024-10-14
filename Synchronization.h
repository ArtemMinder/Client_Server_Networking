#pragma once

#include "ISynchronization.h"
#include <mutex>
#include <condition_variable>

class Synchronization : public ISynchronization 
{
public:
    void lock() override;
    void unlock() override;
    void notify() override;

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    bool ready_ = false;
};
