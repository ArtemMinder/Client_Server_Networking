#include "Writer.h"

void Writer::WriteToBuffer(IBuffer& buffer) {
    std::vector<char> data(8, 'A');  // Example data
    buffer.Write(data);
}
