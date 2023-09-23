#include <iostream>
#include "Aternos.hpp"

int main() {
    std::cout << "Initializing...\n";
    Aternos aternos;
    bool success = aternos.login("username", "password");
    if (!success) { std::cout << "Failed to log in\n"; return 1; }
    std::cout << "Logged in successfully\n";

    std::cout << aternos.request("/servers").text << "\n";

    return 0;
}