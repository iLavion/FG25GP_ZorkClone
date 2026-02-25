#pragma once

#include <string>

struct Game {
    bool isRunning;
};

void setupGame(Game& game);
void startGame(Game& game);
void stopGame(Game& game, const std::string& args);
