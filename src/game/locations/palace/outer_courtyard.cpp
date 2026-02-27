#include "game.hpp"
#include <iostream>

void registerPalaceOuterCourtyard(GameState &state)
{
    Room r;
    r.id = "palace_outer_courtyard";
    r.name = "Palace Outer Courtyard";
    r.description = "An imposing courtyard paved with white marble. Royal guards in gleaming\n"
                    "armor stand at attention beside ornamental fountains. The palace looms\n"
                    "ahead, its towers piercing the sky. The Grand Staircase is north.\n"
                    "The road back to the Noble Quarter leads downhill.";
    r.area_id = "royal_palace";
    r.exits = {
        {Direction::North, "palace_grand_staircase"},
        {Direction::Down, "noble_carriage_lane"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_outer_courtyard",
        {{"Present yourself to the guards",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You announce your name and title. The guards consult a list,\n";
              std::cout << "then nod and step aside.\n";
              std::cout << "  \"The duke's daughter is always welcome. Proceed.\"\n";
              advanceTime(gs, 3);
          }}});
}