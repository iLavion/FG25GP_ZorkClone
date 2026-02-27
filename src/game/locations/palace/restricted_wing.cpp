#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerPalaceRestrictedWing(GameState &state)
{
    Room r;
    r.id = "palace_restricted_wing";
    r.name = "Restricted Wing";
    r.description = "A hushed corridor of locked doors and velvet ropes. Royal artifacts,\n"
                    "state secrets, and forbidden archives are kept here under heavy guard.\n"
                    "The air itself feels dangerous. Stairs lead down to the Grand Staircase.";
    r.area_id = "royal_palace";
    r.exits = {{Direction::Down, "palace_grand_staircase"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_restricted_wing",
        {{"Try a locked door",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You test a door handle. Locked, as expected. But you notice\n";
              std::cout << "the lock is old and simple. With the right tools...\n";
              std::cout << "  " << colored("[!] Being caught here would be disastrous.", ansi::BRIGHT_RED) << "\n";
              advanceTime(gs, 5);
          }},
         {"Examine the displayed artifacts",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Behind glass cases: a crown from a deposed dynasty, a treaty\n";
              std::cout << "written in blood, and a genealogy chart that traces the royal\n";
              std::cout << "bloodline back twelve generations. You notice a name that seems\n";
              std::cout << "out of place near the bottom of the chart.\n";
              advanceTime(gs, 8);
          }}});
}