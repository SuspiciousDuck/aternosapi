#pragma once
#include <cpr/cpr.h>
#include <string>

class Requests {
    public:
    Requests();
    cpr::Response request(std::string, bool);
    cpr::Response post(std::string, std::string, bool);
    cpr::Response MultiPart(std::string, cpr::Multipart, bool);
    std::string cookies;
    private:
    void absorbCookies(cpr::Cookies);
};