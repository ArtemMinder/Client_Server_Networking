#include "Reader.h"
#include <iostream>

void Reader::ReadFromBuffer(IBuffer& buffer) {
    auto data = buffer.Read();
    std::cout.write(data.data(), data.size());
}
