#include "game.hpp"
#include <iostream>

void registerForestOldRuins(GameState &state)
{
    Room r;
    r.id = "forest_old_ruins";
    r.name = "Old Ruins";
    r.description = "Crumbling stone walls and collapsed arches, all that remains of a\n"
                    "structure that predates the kingdom. Moss and ivy claim what time has\n"
                    "not yet destroyed. Faded carvings hint at a forgotten civilization.\n"
                    "The Hunting Clearing is west.";
    r.area_id = "forest_edge";
    r.exits = {{Direction::West, "forest_hunting_clearing"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "forest_old_ruins",
        {{"Examine the ancient carvings",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The carvings depict a coronation scene, a woman anointed by\n";
              std::cout << "priests before kneeling subjects. Beneath it, a genealogy in\n";
              std::cout << "a script you can barely read. One name at the bottom looks\n";
              std::cout << "disturbingly similar to your own family name.\n";
              advanceTime(gs, 8);
          }},
         {"Search beneath the rubble",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You shift loose stones carefully. Under a collapsed pillar,\n";
              std::cout << "you find a small bronze box sealed with wax. It bears the mark\n";
              std::cout << "of the old royal line, predating the current dynasty.\n";
              std::cout << "  Whatever is inside has waited centuries to be found.\n";
              advanceTime(gs, 12);
          }}});
}
