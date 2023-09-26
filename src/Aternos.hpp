#pragma once
#include <string>
#include <cpr/cpr.h>
#include "Encryption.hpp"

class Aternos {
    public:
    struct Server {
        std::string name;
        std::string id;
    };
    Aternos();
    bool login(std::string, std::string);
    std::vector<Server> getServers();
    cpr::Response request(std::string);
    private:
    std::string FindLineWithString(const std::string&, const std::string&);
    std::string getStringBetweenSymbols(const std::string&, char symbol1, char);
    void legitAjax(std::string);
    void generateAjaxToken();
    void genCookies();
    void buildURL();
    std::vector<Server> Servers;
    std::string AJAX_TOKEN;
    std::string gen_token;
    std::string LOGINURL;
    std::string cookies;
    Encryption encrypt;
};