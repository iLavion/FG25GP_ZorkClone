#pragma once

#include "game.hpp"
#include <string>

std::string findNPCInRoom(const GameState &state, const std::string &name);
std::string findItemInRoom(const GameState &state, const std::string &name);
std::string findItemInInventory(const GameState &state, const std::string &name);
