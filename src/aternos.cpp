#include <string>
#include <iostream>
#include <cpr/cpr.h>
#include <random>
#include "Aternos.hpp"
#include "Javascript.hpp"
#include "Encryption.hpp"

Aternos::Aternos() {
    cpr::Header headers = {{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}};
    cpr::Response response = cpr::Get(cpr::Url{"https://aternos.org/go"},headers);

    legitAjax(response.text);
    generateAjaxToken();
    buildURL();
    genCookies();
}

cpr::Response Aternos::request(std::string url) {
    cpr::Response response = cpr::Get(cpr::Url{"https://aternos.org"+url},
                                      cpr::Header{{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}},
                                      cpr::Header{{"Cookie", cookies}});
    return response;
}

void Aternos::legitAjax(std::string html) { std::string result = getStringBetweenSymbols(FindLineWithString(html, "window[\"AJAX_TOKEN\"]"), '?', ':');
    Javascript javascript;
    AJAX_TOKEN = javascript.eval(result);
}

void Aternos::generateAjaxToken() {
    const std::string key = Encryption().Base36Encode(Encryption().Mathrandom()),
    value = Encryption().Base36Encode(Encryption().Mathrandom());
    gen_token = key+":"+value;
}

void Aternos::genCookies() { std::string key = gen_token.substr(0, gen_token.find(':')), value = gen_token.substr(gen_token.find(':') + 1); cookies = "ATERNOS_SEC_"+key+"="+value+";"; }

void Aternos::buildURL() {
    std::string result = "/ajax/account/login?SEC=";
    result += gen_token + "&TOKEN="+AJAX_TOKEN;
    LOGINURL = "https://aternos.org"+result;
}

bool Aternos::login(std::string user, std::string pass) { std::string password = Encryption().MD5(pass);
    cpr::Response r = cpr::Post(cpr::Url{LOGINURL},
                   cpr::Body{"user="+user+"&password="+password},
                   cpr::Header{{"Cookie", cookies}},
                   cpr::Header{{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}});
    cookies = r.cookies[0].GetName()+"="+r.cookies[0].GetValue()+";";
    return r.status_code == 200;
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