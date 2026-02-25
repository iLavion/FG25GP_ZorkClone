#include "game.hpp"
#include <iostream>

void setupGame(Game& game) {
    game.isRunning = false;
}

void startGame(Game& game) {
    game.isRunning = true;
    std::cout << "\nFG25GP_ZorkClone: The Villainess of the Empire\n";
    std::cout << "Copyright (c) 2026 Lavion\n";
    std::cout << "Licensed under the MIT License\n";
    std::cout << "Version " << VILLAINESS_VERSION << "\n\n";
}

void stopGame(Game& game, const std::string&) {
    std::cout << "Goodbye world...";
    game.isRunning = false;
}
