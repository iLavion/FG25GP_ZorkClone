#include "game.hpp"
#include <iostream>

void registerCityGeneralStore(GameState &state)
{
    Room r;
    r.id = "city_general_store";
    r.name = "General Store";
    r.description = "A cluttered shop packed with tools, rope, lanterns, nails, and every\n"
                    "practical good a person could need. The shopkeeper, a broad-shouldered\n"
                    "woman, keeps a sharp eye on her wares. The Central Plaza is west, and\n"
                    "a road east leads toward the Academy.";
    r.area_id = "city_market_district";
    r.exits = {
        {Direction::West, "city_central_plaza"},
        {Direction::East, "academy_main_gate"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_general_store",
        {{"Browse the supplies",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Coils of rope, iron lanterns, canvas sacks, and sturdy boots.\n";
              std::cout << "Everything an adventurer or schemer might need.\n";
              std::cout << "  [i] Use PICKUP to take items if available.\n";
              advanceTime(gs, 3);
          }}});
}
