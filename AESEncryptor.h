#pragma once

#include "IEncryptor.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>


class AESEncryptor : public IEncryptor {
public:
    AESEncryptor();

    std::vector<char> encrypt(const std::vector<char>& data) override;
    std::vector<char> decrypt(const std::vector<char>& data) override;

private:
    std::vector<unsigned char> key;
    std::vector<unsigned char> iv;
};
