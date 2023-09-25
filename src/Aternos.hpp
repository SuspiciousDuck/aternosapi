#pragma once
#include <string>
#include <cpr/cpr.h>
#include "Encryption.hpp"

class Aternos {
    public:
    Aternos();
    bool login(std::string, std::string);
    std::vector<std::string> getServers();
    cpr::Response request(std::string);
    private:
    std::string FindLineWithString(const std::string&, const std::string&);
    std::string getStringBetweenSymbols(const std::string&, char symbol1, char);
    void legitAjax(std::string);
    void generateAjaxToken();
    void genCookies();
    void buildURL();
    std::string AJAX_TOKEN;
    std::string gen_token;
    std::string LOGINURL;
    std::string cookies;
    Encryption encrypt;
};