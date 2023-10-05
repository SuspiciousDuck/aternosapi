# aternosapi
An API I made in C++ to manage Aternos hosted Minecraft servers.
# Building
Requirements: <br>
[libcpr](https://github.com/libcpr/cpr): Used to send posts and requests to aternos. <br>
[QuickJSpp](https://github.com/ftk/quickjspp): Used to evaluate AJAX_TOKEN. Too lazy to put a different solution. <br>
[cryptopp-cmake](https://github.com/abdes/cryptopp-cmake): Used to encrypt MD5, required to log in. <br>
[cmake](https://cmake.org/): Used to build the project. <br>
[libxml2](https://github.com/GNOME/libxml2): Used to parse server list. <br>
[json](https://github.com/nlohmann/json): Used for json parsing. <br>
```console
$ git clone "https://github.com/SuspiciousDuck/aternosapi"
$ cd aternosapi
$ mkdir build
$ cmake -B./build
$ cmake --install ./build --prefix /usr
```
# Usage
Include the library in your main file. <br>
```c++
#include <aternosapi/Aternos.hpp>
```
Then, create an Aternos object and then login with your credentials.
```c++
Aternos aternos;
aternos.login("username", "password");
```
After this, you're all set. For example, you can use functions like `getServers` and `queryServer` in order to get a list of all the servers or get a specific Server object.
```c++
aternos.getServers(); // Returns vector of Aternos::Server objects.
aternos.queryServer("servername"); // Returns a std::optional<Aternos::Server> object.
```
# Example Program
```c++
#include <aternosapi/Aternos.hpp>
#include <iostream>

int main() {
    Aternos aternos;
    auto result = aternos.login("username", "password");
    if (!result.success) { std::cerr << result.reason << "\n"; return 1; }
    for (auto server: aternos.getServers()) {
        std::cout << server.name << "\n";
    }
    auto server = aternos.queryServer("server");
    if (!server.has_value()) return 1;
    std::cout << aternos.serverStatus(server.value()) << "\n";
    return 0;
}
```