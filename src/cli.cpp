#include "cli.hpp"
#include "utilities/string.hpp"
#include <iostream>

void procInput(Game& game, std::string_view input) {
    std::string cleaned = to_lower(to_trim(input));

    if (cleaned.empty()) return;

    if (cleaned == "quit" || cleaned == "exit") {
        stopGame(game, std::string(cleaned));
        return;
    }
    else if (cleaned == "help" || cleaned == "commands") {
        std::cout << "Available commands: quit, help" << std::endl;
        return;
    }

    std::cout << "I don't know what you mean by: " << input << "\n";
}