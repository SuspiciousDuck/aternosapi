#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <string>
#include "aternosapi/Encryption.hpp"

Encryption::Encryption() { srand((time(0))); }

std::string Encryption::MD5(const std::string& input) {
    CryptoPP::Weak1::MD5 hash;
    std::string md5Hash;
    CryptoPP::StringSource(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(md5Hash))));
    for(int i = 0; md5Hash[i]; i++){
        md5Hash[i] = tolower(md5Hash[i]);
    }
    return md5Hash;
}

std::string Encryption::Base36Encode(double value) {
    const std::string characters = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::string result;
    long long intValue = static_cast<long long>(value * 1e17);
    while (intValue > 0) {
        result += characters[intValue % 36];
        intValue /= 36;
    }
    return result+"00000";
}

double Encryption::Mathrandom() { return static_cast<double>(rand()) / RAND_MAX; }