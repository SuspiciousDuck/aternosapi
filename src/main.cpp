#include <iostream>
#include <string>
#include <vector>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/tree.h>
#include "Aternos.hpp"

std::vector<std::string> getServers(Aternos& aternos) { std::vector<std::string> result = {};
    
    return result;
}

int main() {
    std::cout << "Initializing...\n";
    Aternos aternos;
    bool success = aternos.login("username", "password");
    if (!success) { std::cout << "Failed to log in\n"; return 1; }
    std::cout << "Logged in successfully\n";

    getServers(aternos);

    return 0;
}