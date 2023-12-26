# WARNING
### Use at your own risk
This project is against the Aternos TOS as stated in **Section 5.2e: Abuse and limitations**: "Automatically accessing our website or automating actions on our website." You're free to use this project, but be aware **YOUR ACCOUNT CAN BE DELETED**. Currently, this project doesn't do anything at all to circumvent detection, so if you use this frequently, your account **WILL** be banned.
# aternosapi
An API I made in C++ to manage Aternos hosted Minecraft servers.
# Building
Dependencies: <br>
[cmake](https://cmake.org/): Used to build the project. <br>
[quickjs](https://github.com/bellard/quickjs): Used to evaluate AJAX_TOKEN. Too lazy to put a different solution. <br>
[libcpr](https://github.com/libcpr/cpr): Used to send posts and requests to aternos. <br>
[cryptopp-cmake](https://github.com/abdes/cryptopp-cmake): Used to encrypt MD5, required to log in. <br>
[libxml2](https://gitlab.gnome.org/GNOME/libxml2): Used to parse server list. <br>
[json](https://github.com/nlohmann/json): Used for json parsing.
```bash
git clone "https://github.com/SuspiciousDuck/aternosapi"
cd aternosapi
mkdir build
cmake -B./build
cmake --build ./build -j$(nproc)
sudo cmake --install ./build
```
# Usage
Include the library in your main file. <br>
```c++
#include <aternosapi/Aternos.hpp>
```
Then, initialize an Aternos object and then login with your credentials. Optionally, you can check if the login succeeded.
```c++
Aternos aternos;
aternos.login("username", "password"); // Returns login success and fail message
```
After this, you're all set. For example, you can use functions like `getServers` and `queryServer` in order to get a list of all the servers or retrieve a specific server.
```c++
aternos.getServers(); // Returns vector of Aternos::Server objects.
aternos.queryServer("servername"); // Returns std::optional<Aternos::Server>.
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
# Current features:
* Login to a specific account
* Retrieve all the servers an account has access to
* Get a specific server by name
* Request data from a specific server, like status, address, player count and names
* Can do server actions, like starting and stopping a server
# CMake
Currently I haven't made a FindAternos file, so `find_package()` doesn't work. <br>
### find_library() example
```cmake
# Assuming aternosapi was installed
find_library(aternos_lib NAMES libaternosapi.so PATH_SUFFIXES "aternosapi" REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${aternos_lib})
```