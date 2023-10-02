#include <iostream>
#include <string>
#include "Aternos.hpp"

int main() {
    std::cout << "Initializing...\n";
    Aternos aternos;
    auto response = aternos.login("username", "password");
    if (!response.success) { std::cout << "Failed to log in: "+response.reason+"\n"; return 1; }
    std::cout << "Logged in successfully\n";
    auto server = aternos.queryServer("servername");
    if (server.has_value()) {
        auto result  = aternos.serverPlayers(server.value());
        for (auto& value: result) {
            std::cout << value << "\n";
        }
    }
    return 0;
}