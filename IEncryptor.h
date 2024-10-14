#pragma once

#include <string>
#include <vector>

class IEncryptor 
{
public:
    virtual ~IEncryptor() = default;

    virtual std::vector<char> encrypt(const std::vector<char>& data) = 0;
    virtual std::vector<char> decrypt(const std::vector<char>& data) = 0;
};
