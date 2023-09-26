#include <iostream>
#include <string>
#include "Aternos.hpp"

int main() {
    std::cout << "Initializing...\n";
    Aternos aternos;
    bool success = aternos.login("username", "password");
    if (!success) { std::cout << "Failed to log in\n"; return 1; }
    std::cout << "Logged in successfully\n";
    for (auto server:aternos.getServers()) {
        std::cout << server.name << ", " << server.id << "\n";
        aternos.ServerStatus(server);
    }
    return 0;
}