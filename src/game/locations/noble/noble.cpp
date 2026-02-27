#include "game.hpp"

void registerNobleCarriageLane(GameState &state);
void registerNobleSalon(GameState &state);
void registerNobleRivalGate(GameState &state);
void registerNobleRivalGarden(GameState &state);
void registerNobleDiplomat(GameState &state);
void registerNobleMasqueradeHall(GameState &state);

void buildNobleQuarter(GameState &state)
{
    Area area;
    area.id = "noble_quarter";
    area.name = "Noble Quarter";
    area.rooms = {
        "noble_carriage_lane", "noble_salon", "noble_rival_gate",
        "noble_rival_garden", "noble_diplomat", "noble_masquerade_hall"};
    state.areas[area.id] = area;

    registerNobleCarriageLane(state);
    registerNobleSalon(state);
    registerNobleRivalGate(state);
    registerNobleRivalGarden(state);
    registerNobleDiplomat(state);
    registerNobleMasqueradeHall(state);
}
