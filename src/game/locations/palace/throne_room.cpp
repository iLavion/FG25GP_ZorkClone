#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerPalaceThroneRoom(GameState &state)
{
    Room r;
    r.id = "palace_throne_room";
    r.name = "Throne Room";
    r.description = "The seat of royal power. A massive gilded throne sits atop a raised\n"
                    "dais, flanked by the kingdom's banners. The room is vast and echoing,\n"
                    "designed to make all who enter feel small. Only the most important\n"
                    "audiences take place here. The Audience Chamber is south.";
    r.area_id = "royal_palace";
    r.exits = {{Direction::South, "palace_audience_chamber"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_throne_room",
        {{"Approach the throne",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You walk the long, echoing path to the base of the dais.\n";
              std::cout << "The empty throne gleams above. One day, the person who sits\n";
              std::cout << "here will decide your fate, or you will decide theirs.\n";
              std::cout << "  " << colored("The weight of your ambition presses down.", ansi::BRIGHT_RED) << "\n";
              advanceTime(gs, 3);
          }},
         {"Examine the royal banners",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "The kingdom's banners hang from the vaulted ceiling. Your family's\n";
              std::cout << "crest is among them, though smaller than the royal standard.\n";
              std::cout << "  A reminder of your place in the hierarchy, high, but not highest.\n";
          }}});
}
