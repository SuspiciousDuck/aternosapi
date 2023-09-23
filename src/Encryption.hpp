#pragma once
#include <string>

class Encryption {
    public:
    Encryption();
    std::string MD5(const std::string&);
    std::string Base36Encode(double value);
    double Mathrandom();
};