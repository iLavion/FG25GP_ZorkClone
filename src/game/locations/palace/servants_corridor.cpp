#include "game.hpp"
#include <iostream>

void registerPalaceServantsCorridor(GameState &state)
{
    Room r;
    r.id = "palace_servants_corridor";
    r.name = "Servants' Corridor";
    r.description = "A narrow, plain corridor used by palace servants. Whitewashed walls\n"
                    "and bare stone floors contrast sharply with the opulence beyond. Trays\n"
                    "of food and linens are carried past in a constant stream. The Grand\n"
                    "Staircase is east, the Palace Garden south.";
    r.area_id = "royal_palace";
    r.exits = {
        {Direction::East, "palace_grand_staircase"},
        {Direction::South, "palace_garden"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_servants_corridor",
        {{"Blend in with the servants",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You keep your head down and walk with purpose. The servants\n";
              std::cout << "are too busy to question a well-dressed woman in their corridor.\n";
              std::cout << "You overhear talk of the royal schedule and guard rotations.\n";
              advanceTime(gs, 5);
          }},
         {"Search for useful information",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "A duty roster is pinned to the wall. You memorize the guard\n";
              std::cout << "schedule for the restricted wing: shift changes at midnight\n";
              std::cout << "and midday, with a 10-minute gap between rotations.\n";
              advanceTime(gs, 5);
          }}});
}