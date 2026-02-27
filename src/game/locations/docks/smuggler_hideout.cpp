#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerDocksSmugglerHideout(GameState &state)
{
    Room r;
    r.id = "docks_smuggler_hideout";
    r.name = "Smuggler Hideout";
    r.description = "A concealed space behind a false wall in the last warehouse. Lanterns\n"
                    "cast an amber glow over stacked contraband, sea charts with secret\n"
                    "routes, and a table where shady deals are struck. The Warehouses are west.";
    r.area_id = "docks";
    r.exits = {{Direction::West, "docks_warehouses"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_smuggler_hideout",
        {{"Examine the contraband",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Crates of untaxed wine, bolts of stolen silk, and small locked\n";
              std::cout << "boxes that rattle when shaken. One box is labeled with a cipher.\n";
              std::cout << "  " << colored("[!] This place is extremely dangerous for a noblewoman.", ansi::BRIGHT_RED) << "\n";
              gs.player.suspicion += 4;
              std::cout << "  Suspicion +4\n";
              advanceTime(gs, 5);
          }},
         {"Study the escape routes on the sea charts",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The charts show hidden coves and safe harbors along the coast.\n";
              std::cout << "One route is circled in red, a quick passage out of the kingdom.\n";
              std::cout << "  Useful if things go very wrong, or very right.\n";
              advanceTime(gs, 5);
          }}});
}
