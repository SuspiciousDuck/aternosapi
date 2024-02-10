#include <aternosapi/Aternos.hpp>
#include <iostream>

// USAGE: ./(executable) username password
// RETURNS: list of available servers
// EXAMPLE: ./build/test foo bar

int main(int argc, char** argv) {
    Aternos aternos;
    auto result = aternos.login(argv[1], argv[2]);
    if (!result.success) { std::cerr << result.reason << "\n"; return 1; }
    for (auto server: aternos.getServers()) {
        std::cout << server.name << "\n";
    }
    return 0;
}