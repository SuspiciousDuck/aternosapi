# aternosapi
An API I made in C++ to manage Minecraft servers.
# Building
Requirements: <br>
[libcpr](https://www.github.com/libcpr/cpr): Used to send posts and requests to aternos. <br>
[NodeJS](https://nodejs.org/en): Used for a niche part in the script, hopefully phased out once a suitable replacement is found. <br>
[cryptopp-cmake](https://github.com/abdes/cryptopp-cmake): Used to encrypt MD5, required to log in. <br>
[cmake](https://cmake.org/): Used to build the project. <br>
```
$ git clone https://github.com/SuspiciousDuck/aternosapi
$ cd aternosapi
$ mkdir build; cd build
$ cmake ..; make -j$(nproc)
```
# Usage
Currently, it's not a proper library, so for now you'll have to edit main.cpp directly. I don't plan on having documentation either, because I don't know how and I'm not confident I would remember to keep it updated.
