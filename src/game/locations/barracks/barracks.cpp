#include "game.hpp"

void registerBarracksFrontDesk(GameState &state);
void registerBarracksRecords(GameState &state);
void registerBarracksCells(GameState &state);
void registerBarracksInterrogation(GameState &state);
void registerBarracksTraining(GameState &state);
void registerBarracksArmory(GameState &state);

void buildBarracks(GameState &state)
{
    Area area;
    area.id = "guard_barracks";
    area.name = "Guard Barracks";
    area.rooms = {
        "barracks_front_desk", "barracks_records", "barracks_cells",
        "barracks_interrogation", "barracks_training", "barracks_armory"};
    state.areas[area.id] = area;

    registerBarracksFrontDesk(state);
    registerBarracksRecords(state);
    registerBarracksCells(state);
    registerBarracksInterrogation(state);
    registerBarracksTraining(state);
    registerBarracksArmory(state);
}
