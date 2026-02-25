#include "game.hpp"
#include "cli.hpp"
#include <iostream>

int main() {
    Game game;
    setupGame(game);
    startGame(game);

    std::string input;
    while (game.isRunning) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;
        if (input.empty()) continue;
        procInput(game, input);
    }

    return 0;
}
