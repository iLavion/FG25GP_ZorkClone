#include "game.hpp"
#include <iostream>

void registerDocksFishMarket(GameState &state)
{
    Room r;
    r.id = "docks_fish_market";
    r.name = "Fish Market";
    r.description = "A noisy open-air market reeking of brine and fresh catch. Fishmongers\n"
                    "shout prices over rows of glistening fish laid on ice. Commoners haggle\n"
                    "fiercely. Cheap food and cheaper gossip abound.\n"
                    "The Harbor Master Office is east.";
    r.area_id = "docks";
    r.exits = {{Direction::East, "docks_harbor_master"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_fish_market",
        {{"Buy some cheap food",                                                  
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You purchase a skewer of grilled fish. Not refined dining, but\n";
              std::cout << "filling and oddly satisfying.\n";
              gs.player.hunger = std::min(100, gs.player.hunger + 20);
              gs.player.turns_without_eating = 0;
              std::cout << "  Hunger +20\n";
              advanceTime(gs, 5);
          }},
         {"Listen to the fishermen gossip",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The fishermen talk loud enough for the whole market to hear.\n";
              std::cout << "  \"Something's off about the waters lately. Strange ships at night.\"\n";
              std::cout << "  \"Smugglers, I tell you. And someone important is behind it.\"\n";
              advanceTime(gs, 5);
          }}});
}
