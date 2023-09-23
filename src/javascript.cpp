#include <string>
#include <algorithm>
#include "Javascript.hpp"

std::string Javascript::eval(const std::string& g) { std::string code = g;
    std::replace(code.begin(), code.end(), '"', '\''); // remove double quote conflicts
    code = "console.log("+code+");";
    std::string command = "node -e \"" +  code + "\"";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "";
    char buffer[128]; std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) result += buffer;
    pclose(pipe);
    std::replace(result.begin(), result.end(), '\n', '\0');
    return result;
}