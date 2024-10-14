#pragma once

#include "IBuffer.h"
#include <vector>
#include <mutex>

class Buffer : public IBuffer
{
public:
    void write(const std::vector<char>& data) override;
    std::vector<char> read() override;

private:
    std::vector<char> data_;
    std::mutex mtx_;
};
