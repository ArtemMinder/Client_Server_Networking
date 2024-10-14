#include "AESEncryptor.h"
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

AESEncryptor::AESEncryptor() {
    using namespace CryptoPP;

    // Generate a random key and IV for AES encryption
    AutoSeededRandomPool prng;

    key.resize(AES::DEFAULT_KEYLENGTH);
    iv.resize(AES::BLOCKSIZE);

    prng.GenerateBlock(key.data(), key.size());
    prng.GenerateBlock(iv.data(), iv.size());
}

std::vector<char> AESEncryptor::encrypt(const std::vector<char>& data) {
    using namespace CryptoPP;

    std::string cipher;
    CFB_Mode<AES>::Encryption encryption(key.data(), key.size(), iv.data());

    // Cast data to byte* (unsigned char*) to avoid type mismatch
    StringSource ss(reinterpret_cast<const byte*>(data.data()), data.size(), true,
        new StreamTransformationFilter(encryption, new StringSink(cipher))
    );

    return std::vector<char>(cipher.begin(), cipher.end());
}

std::vector<char> AESEncryptor::decrypt(const std::vector<char>& data) {
    using namespace CryptoPP;

    std::string recovered;
    CFB_Mode<AES>::Decryption decryption(key.data(), key.size(), iv.data());

    // Cast data to byte* (unsigned char*) to avoid type mismatch
    StringSource ss(reinterpret_cast<const byte*>(data.data()), data.size(), true,
        new StreamTransformationFilter(decryption, new StringSink(recovered))
    );

    return std::vector<char>(recovered.begin(), recovered.end());
}
