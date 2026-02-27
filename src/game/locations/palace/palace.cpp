#include "game.hpp"

void registerPalaceOuterCourtyard(GameState &state);
void registerPalaceGrandStaircase(GameState &state);
void registerPalaceThroneRoom(GameState &state);
void registerPalaceAudienceChamber(GameState &state);
void registerPalaceBallroom(GameState &state);
void registerPalaceServantsCorridor(GameState &state);
void registerPalaceRestrictedWing(GameState &state);
void registerPalaceGarden(GameState &state);

void buildPalace(GameState &state)
{
    Area area;
    area.id = "royal_palace";
    area.name = "The Royal Palace";
    area.rooms = {
        "palace_outer_courtyard", "palace_grand_staircase", "palace_throne_room",
        "palace_audience_chamber", "palace_ballroom", "palace_servants_corridor",
        "palace_restricted_wing", "palace_garden"};
    state.areas[area.id] = area;

    registerPalaceOuterCourtyard(state);
    registerPalaceGrandStaircase(state);
    registerPalaceThroneRoom(state);
    registerPalaceAudienceChamber(state);
    registerPalaceBallroom(state);
    registerPalaceServantsCorridor(state);
    registerPalaceRestrictedWing(state);
    registerPalaceGarden(state);
}
