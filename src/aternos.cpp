#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "Aternos.hpp"
#include "Javascript.hpp"
#include "Encryption.hpp"
#include "Requests.hpp"
#include "WebParser.hpp"

bool operator==(const Aternos::Server& lhs, const Aternos::Server& rhs) {
    bool result = true;
    if (lhs.name != rhs.name) { result = false; }
    if (lhs.id != rhs.id) { result = false; }
    return result;
}

Aternos::Aternos() {
    cpr::Header headers = {{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}};
    cpr::Response response = cpr::Get(cpr::Url{"https://aternos.org/go"},headers);

    legitAjax(response.text);
    generateAjaxToken();
    LOGINURL = buildURL("/ajax/account/login");
    genCookies();
}

std::optional<Aternos::Server> Aternos::queryServer(std::string query) {
    for (auto& server: Servers) {
        if (server.name == query) {
            return server;
        }
    }
    getServers();
    for (auto& server: Servers) {
        if (server.name == query) {
            return server;
        }
    }
    return std::nullopt;
}

std::string Aternos::serverAddress(Aternos::Server server) {
    if (!server.ip.empty()) { return server.ip; }
    enterServerSession(server);
    cpr::Response r = rq.request(buildURL("/ajax/server/get-status"),true);
    nlohmann::json j = nlohmann::json::parse(r.text)["data"];
    std::string result = nlohmann::to_string(j["displayAddress"])+":"+nlohmann::to_string(j["port"]);
    result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());
    server.ip = result;
    return result;
}

std::string Aternos::serverStatus(Aternos::Server server) {
    enterServerSession(server);
    cpr::Response r = rq.request(buildURL("/ajax/server/get-status"),true);
    nlohmann::json j = nlohmann::json::parse(r.text)["data"];
    std::string status = j["label"];
    std::replace(status.begin(), status.end(), '\"', '\0');
    return status;
}

void Aternos::enterServerSession(Aternos::Server server) {
    SERVER=server.id;
    genCookies();
}

std::vector<std::string> Aternos::serverPlayers(Aternos::Server server) { std::vector<std::string> result;
    enterServerSession(server);
    cpr::Response r = rq.request(buildURL("/ajax/server/get-status"),true);
    nlohmann::json j = nlohmann::json::parse(r.text)["data"];
    result.push_back(nlohmann::to_string(j["players"]));
    if (result[0] != "0") {
        for (auto& name: j["playerlist"]) {
            result.push_back(name);
        }
    }
    return result;
}

bool Aternos::startServer(Aternos::Server server) {
    enterServerSession(server);
    cpr::Response r = rq.request(buildURL("/ajax/server/start"),true);
    nlohmann::json j = nlohmann::json::parse(r.text);
    return j["success"];
}

bool Aternos::stopServer(Aternos::Server server) {
    enterServerSession(server);
    cpr::Response r = rq.request(buildURL("/ajax/server/stop"),true);
    nlohmann::json j = nlohmann::json::parse(r.text);
    return j["success"];
}

std::vector<Aternos::Server> Aternos::getServers() {
    std::string html = rq.request("https://aternos.org/servers",true).text;
    WebParser webparser{html};
    std::optional<xmlNodeSetPtr> nodes = webparser.EvalXPath("//*[contains(concat(\" \",normalize-space(@class),\" \"),\" servercard \")]");
    if (nodes != nullptr) {
        for (int i = 0; i < xmlXPathNodeSetGetLength((xmlNodeSetPtr&)nodes); ++i) {
            xmlNodePtr node = ((xmlNodeSetPtr&)nodes)->nodeTab[i];
            Server server;
            server.name = (char*)xmlGetProp(node, (xmlChar*)"title");
            auto child = node->children;
            while (child != nullptr) {
                if (xmlHasProp(child, (xmlChar*)"data-id") != nullptr) { server.id = (char*)xmlGetProp(child, (xmlChar*)"data-id"); break; }
                else { child = child->next; }
            }
            bool temp = false;
            for (auto Server:Servers) { if (temp == false and Server==server) { temp = true; } }
            if (temp == false) { Servers.emplace_back(server); }
        }
    }
    webparser.cleanWebParser();
    return Servers;
}

void Aternos::legitAjax(std::string html) { std::string result = getStringBetweenSymbols(FindLineWithString(html, "window[\"AJAX_TOKEN\"]"), '?', ':');
    Javascript javascript;
    AJAX_TOKEN = javascript.eval(result);
}

void Aternos::generateAjaxToken() {
    const std::string key = encrypt.Base36Encode(encrypt.Mathrandom());
    const std::string value = encrypt.Base36Encode(encrypt.Mathrandom());
    gen_token = key+":"+value;
}

void Aternos::genCookies() {
    std::string key = gen_token.substr(0, gen_token.find(':')),
    value = gen_token.substr(gen_token.find(':') + 1);
    rq.cookies = "ATERNOS_SEC_"+key+"="+value+"; ";
    if (!SESSION.empty()) { rq.cookies += "ATERNOS_SESSION="+SESSION+"; "; }
    if (!SERVER.empty()) { rq.cookies += "ATERNOS_SERVER="+SERVER+"; "; }
}

std::string Aternos::buildURL(std::string url) {
    std::string result = url+"?TOKEN="+AJAX_TOKEN+"&SEC="+gen_token;
    return "https://aternos.org"+result;
}

Aternos::loginResponse Aternos::login(std::string user, std::string pass) { std::string password = encrypt.MD5(pass);
    cpr::Response r = rq.MultiPart(LOGINURL, {{"username", user}, {"password", password}}, true);
    for (auto& cookie: r.cookies) {
        if (cookie.GetName().find("SESSION") != std::string::npos) {
            SESSION = cookie.GetValue();
            genCookies();
        }
    }
    nlohmann::json j = nlohmann::json::parse(r.text);
    Aternos::loginResponse result;
    result.success = j["success"];
    if (!result.success) { result.reason = j["error"]; }
    return result;
}

std::string Aternos::FindLineWithString(const std::string& input, const std::string& searchString) {
    std::istringstream iss(input);
    std::string line;
    while (std::getline(iss, line)) if (line.find(searchString) != std::string::npos) return line;
    return "";
}

std::string Aternos::getStringBetweenSymbols(const std::string& input, char symbol1, char symbol2) {
    size_t startPos = input.find(symbol1), endPos = input.find(symbol2);
    if (startPos == std::string::npos || endPos == std::string::npos) return ""; startPos++;
    size_t length = endPos - startPos;
    return input.substr(startPos, length);
}