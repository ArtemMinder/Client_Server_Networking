#include "Buffer.h"

void Buffer::write(const std::vector<char>& data) 
{
    std::lock_guard<std::mutex> lock(mtx_);
    data_ = data;
}

std::vector<char> Buffer::read() 
{
    std::lock_guard<std::mutex> lock(mtx_);
    return data_;
}
