#include <iostream>
#include <string>
#include "Aternos.hpp"

int main() {
    std::cout << "Initializing...\n";
    Aternos aternos;
    auto response = aternos.login("username", "password");
    if (!response.success) { std::cout << "Failed to log in: "+response.reason+"\n"; return 1; }
    std::cout << "Logged in successfully\n";
    return 0;
}