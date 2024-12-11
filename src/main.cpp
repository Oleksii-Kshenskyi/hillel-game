#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

#include <fmt/core.h>
#include <fmt/color.h>
#include <nlohmann/json.hpp>

#include "test.h"

// TODO LIST:
// + 1. Minimal loop that on each iteration takes a command from the user and echoes out the result.
// + 2. When the user writes "exit", the application exits.
// + 3. "split" function that splits the received command into several words.

// "show my inventory" => ["show", "my", "inventory"]
std::vector<std::string> split(const std::string& command) {
    std::stringstream ss(command);
    std::vector<std::string> result;
    std::string word;

    while(ss >> word) {
        result.push_back(word);
    }
        
    return result;
}

int main() {
    std::string user_input;
    std::vector<std::string> words;
    do {
        fmt::print("=> ");
        std::getline(std::cin, user_input);
        for(char& ch: user_input) {
            ch = std::tolower(ch);
        }
        words = split(user_input);
    } while(!(words.size() == 1 && words[0] == "exit"));

    fmt::print("Thanks for playing, see you later!\n\n");
    return 0;
}
