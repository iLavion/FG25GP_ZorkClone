#include "game.hpp"

void registerDocksMainPier(GameState &state);
void registerDocksWarehouses(GameState &state);
void registerDocksSmugglerHideout(GameState &state);
void registerDocksShipDeck(GameState &state);
void registerDocksHarborMaster(GameState &state);
void registerDocksFishMarket(GameState &state);

void buildDocks(GameState &state)
{
    Area area;
    area.id = "docks";
    area.name = "The Docks";
    area.rooms = {
        "docks_main_pier", "docks_warehouses", "docks_smuggler_hideout",
        "docks_ship_deck", "docks_harbor_master", "docks_fish_market"};
    state.areas[area.id] = area;

    registerDocksMainPier(state);
    registerDocksWarehouses(state);
    registerDocksSmugglerHideout(state);
    registerDocksShipDeck(state);
    registerDocksHarborMaster(state);
    registerDocksFishMarket(state);
}
