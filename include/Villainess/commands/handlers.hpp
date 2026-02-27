#pragma once

#include "game.hpp"
#include <string>

void cmdLook(GameState &state, const std::string &args);
void cmdGo(GameState &state, const std::string &args);
void cmdTalk(GameState &state, const std::string &args);
void cmdPickup(GameState &state, const std::string &args);
void cmdDrop(GameState &state, const std::string &args);
void cmdUse(GameState &state, const std::string &args);
void cmdInventory(GameState &state, const std::string &args);
void cmdInspect(GameState &state, const std::string &args);
void cmdEat(GameState &state, const std::string &args);
void cmdSleep(GameState &state, const std::string &args);
void cmdPlot(GameState &state, const std::string &args);
void cmdHire(GameState &state, const std::string &args);
void cmdRead(GameState &state, const std::string &args);
void cmdWrite(GameState &state, const std::string &args);
void cmdSearch(GameState &state, const std::string &args);
void cmdKill(GameState &state, const std::string &args);
void cmdStatus(GameState &state, const std::string &args);
void cmdLog(GameState &state, const std::string &args);
void cmdCommands(GameState &state, const std::string &args);
void cmdHelp(GameState &state, const std::string &args);
void cmdUndo(GameState &state, const std::string &args);
