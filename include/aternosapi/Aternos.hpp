#pragma once
#include <string>
#include <cpr/cpr.h>
#include <optional>
#include <vector>
#include "aternosapi/Requests.hpp"
#include "aternosapi/Encryption.hpp"

class Aternos {
    public:
    struct Server {
        std::string name;
        std::string id;
        std::string ip;
    };
    struct loginResponse {
        bool success;
        std::string reason;
    };
    Aternos();
    loginResponse login(std::string, std::string);
    std::vector<Server> getServers();
    std::string serverStatus(Server);
    std::string serverAddress(Server);
    std::optional<Server> queryServer(std::string);
    std::vector<std::string> serverPlayers(Server);
    bool startServer(Server);
    bool stopServer(Server);
    private:
    std::string FindLineWithString(const std::string&, const std::string&);
    std::string getStringBetweenSymbols(const std::string&, char, char);
    void legitAjax(std::string);
    void generateAjaxToken();
    void genCookies();
    void enterServerSession(Server);
    std::string buildURL(std::string);
    std::vector<Server> Servers;
    std::string SERVER, SESSION, AJAX_TOKEN, gen_token, LOGINURL;
    Encryption encrypt;
    Requests rq;
};