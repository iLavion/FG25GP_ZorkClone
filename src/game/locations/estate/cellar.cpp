#include "game.hpp"
#include <iostream>

void registerCellar(GameState &state)
{
    Room r;
    r.id = "cellar";
    r.name = "Cellar";
    r.description = "A dank underground storage area. Wine barrels line the walls and\n"
                    "shadows dance in the flickering torchlight. Not many come down here.\n"
                    "Stairs lead up to the Kitchen.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::Up, "kitchen"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    state.rooms["cellar"].item_ids.push_back("wine");
    state.rooms["cellar"].item_ids.push_back("key");
    state.rooms["cellar"].item_ids.push_back("poison_vial");

    registerRoomActions(
        "cellar",
        {{"Search the shadows",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You peer into the dark corners. Cobwebs hang thick between\n";
              std::cout << "old barrels. A draft of cold air hints at a hidden passage\n";
              std::cout << "deeper beneath the estate.\n";
          }},
         {"Examine the wine barrels",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "Rows of aged oak barrels, each labeled with a vintage year.\n";
              std::cout << "Some have been opened recently... curious for a supposedly\n";
              std::cout << "unused cellar.\n";
          }}});
}
