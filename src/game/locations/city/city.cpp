#include "game.hpp"

void registerCityCentralPlaza(GameState &state);
void registerCityApothecary(GameState &state);
void registerCityGeneralStore(GameState &state);
void registerCityBookshop(GameState &state);
void registerCityBakery(GameState &state);
void registerCityAlleyways(GameState &state);
void registerCityBlackMarket(GameState &state);
void registerCityCourier(GameState &state);
void registerCityCasino(GameState &state);

void buildCity(GameState &state)
{
    Area area;
    area.id = "city_market_district";
    area.name = "City Market District";
    area.rooms = {
        "city_central_plaza", "city_apothecary", "city_general_store",
        "city_bookshop", "city_bakery", "city_alleyways",
        "city_black_market", "city_courier", "city_casino"};
    state.areas[area.id] = area;

    registerCityCentralPlaza(state);
    registerCityApothecary(state);
    registerCityGeneralStore(state);
    registerCityBookshop(state);
    registerCityBakery(state);
    registerCityAlleyways(state);
    registerCityBlackMarket(state);
    registerCityCourier(state);
    registerCityCasino(state);
}
