#include "Synchronization.h"

void Synchronization::lock() 
{
    mtx_.lock();
}

void Synchronization::unlock()
{
    mtx_.unlock();
}

void Synchronization::notify() 
{
    ready_ = true;
    cv_.notify_all();
}
