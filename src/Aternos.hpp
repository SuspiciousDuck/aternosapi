#pragma once
#include <string>
#include <cpr/cpr.h>
#include <optional>
#include "Encryption.hpp"

class Aternos {
    public:
    struct Server {
        std::string name;
        std::string id;
    };
    struct loginResponse {
        bool success;
        std::string reason;
    };
    Aternos();
    loginResponse login(std::string, std::string);
    std::vector<Server> getServers();
    cpr::Response request(std::string);
    cpr::Response post(std::string, std::string);
    std::string ServerStatus(Server);
    std::string ServerAddress(Server);
    std::optional<Server> queryServer(std::string);
    private:
    std::string FindLineWithString(const std::string&, const std::string&);
    std::string getStringBetweenSymbols(const std::string&, char, char);
    void legitAjax(std::string);
    void generateAjaxToken();
    void genCookies();
    void enterServerSession(Server);
    std::string buildURL(std::string);
    std::vector<Server> Servers;
    std::string SERVER, SESSION, AJAX_TOKEN, gen_token, LOGINURL, cookies;
    Encryption encrypt;
};