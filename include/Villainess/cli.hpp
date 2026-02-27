#pragma once

#include <string>
#include "game.hpp"

void procInput(Game &game, const std::string &input);
void registerCommands(Game &game);
void procDialogueInput(Game &game, const std::string &input);
