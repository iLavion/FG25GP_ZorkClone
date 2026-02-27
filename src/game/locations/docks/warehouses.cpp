#include "game.hpp"
#include <iostream>

void registerDocksWarehouses(GameState &state)
{
    Room r;
    r.id = "docks_warehouses";
    r.name = "Warehouse Row";
    r.description = "A row of large wooden warehouses stacked with crates, barrels, and\n"
                    "sealed cargo. The smell of tar, fish, and exotic spices mingles in the\n"
                    "damp air. Some warehouses seem busier at night than during the day.\n"
                    "The Main Pier is north, the Smuggler Hideout east.";
    r.area_id = "docks";
    r.exits = {
        {Direction::North, "docks_main_pier"},
        {Direction::East, "docks_smuggler_hideout"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_warehouses",
        {{"Inspect the cargo",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You peek into open crates: textiles, grain, wine. Standard trade\n";
              std::cout << "goods. But one crate in the corner bears no shipping label.\n";
              std::cout << "  Its contents are wrapped in oilcloth, suspiciously well-hidden.\n";
              advanceTime(gs, 5);
          }}});
}