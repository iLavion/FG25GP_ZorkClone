#include "game.hpp"

void registerVillageTownSquare(GameState &state);
void registerVillageChapel(GameState &state);
void registerVillageGraveyard(GameState &state);
void registerVillageInn(GameState &state);
void registerVillageInnRooms(GameState &state);
void registerVillageTailor(GameState &state);
void registerVillageMarket(GameState &state);
void registerVillageWell(GameState &state);

void buildVillage(GameState &state)
{
    Area area;
    area.id = "village_suburb";
    area.name = "Village Suburb";
    area.rooms = {
        "village_town_square", "village_chapel", "village_graveyard",
        "village_inn", "village_inn_rooms", "village_tailor",
        "village_market", "village_well"};
    state.areas[area.id] = area;

    registerVillageTownSquare(state);
    registerVillageChapel(state);
    registerVillageGraveyard(state);
    registerVillageInn(state);
    registerVillageInnRooms(state);
    registerVillageTailor(state);
    registerVillageMarket(state);
    registerVillageWell(state);
}
