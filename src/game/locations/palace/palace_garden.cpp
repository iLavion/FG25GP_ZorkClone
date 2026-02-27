#include "game.hpp"
#include <iostream>

void registerPalaceGarden(GameState &state)
{
    Room r;
    r.id = "palace_garden";
    r.name = "Palace Garden";
    r.description = "Immaculate royal gardens with geometrically trimmed hedges, exotic\n"
                    "flowers from distant lands, and a tranquil koi pond. Marble statues\n"
                    "of past monarchs line the gravel paths. A private retreat for intimate\n"
                    "conversations. The Servants' Corridor is north.";
    r.area_id = "royal_palace";
    r.exits = {{Direction::North, "palace_servants_corridor"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_garden",
        {{"Stroll through the gardens",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You walk the pristine gravel paths. Exotic blooms perfume the\n";
              std::cout << "air, jasmine, orchids, roses bred in impossible colors.\n";
              std::cout << "  A peaceful moment in a world of schemes.\n";
              gs.player.energy = std::min(100, gs.player.energy + 5);
              std::cout << "  Energy +5\n";
              advanceTime(gs, 10);
          }},
         {"Wait for a private encounter",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You settle on a bench by the koi pond and wait. The garden\n";
              std::cout << "is a favored spot for secret meetings. If you're patient,\n";
              std::cout << "someone interesting might appear.\n";
              advanceTime(gs, 15);
          }}});
}
