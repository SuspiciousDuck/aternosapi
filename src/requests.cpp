#include <cpr/multipart.h>
#include <string>
#include <cpr/cpr.h>
#include <regex>
#include "Requests.hpp"

Requests::Requests() {
    cookies = "";
}

cpr::Response Requests::request(std::string url, bool absorb) {
    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Header{{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}},
        cpr::Header{{"Cookie", cookies}});
    if (absorb) {
        Requests::absorbCookies(response.cookies);
    }
    return response;
}

cpr::Response Requests::post(std::string url, std::string data, bool absorb) {
    cpr::Response response = cpr::Post(cpr::Url{url},
        cpr::Body{data},
        cpr::Header{{"Cookie", cookies}},
        cpr::Header{{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}});
    if (absorb) {
        Requests::absorbCookies(response.cookies);
    }
    return response;
}

cpr::Response Requests::MultiPart(std::string url, cpr::Multipart FormData, bool absorb) {
    cpr::Response response = cpr::Post(cpr::Url{url},
        FormData,
        cpr::Header{{"Cookie", cookies}},
        cpr::Header{{"User-Agent","Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0"}});
    if (absorb) {
        Requests::absorbCookies(response.cookies);
    }
    return response;
}

void Requests::absorbCookies(cpr::Cookies rqcookies) {
    for (auto& cookie: rqcookies) {
        std::regex match{"("+cookie.GetName()+"=.*?;)"};
        std::regex_replace(cookies, match, "");
        cookies += cookie.GetName() + "=" + cookie.GetValue() + ";";
    }
}