#include "game.hpp"
#include <iostream>

void registerPalaceGrandStaircase(GameState &state)
{
    Room r;
    r.id = "palace_grand_staircase";
    r.name = "Palace Grand Staircase";
    r.description = "A breathtaking marble staircase with gold-leafed banisters sweeps upward\n"
                    "beneath a domed ceiling painted with angels. Courtiers ascend and descend\n"
                    "in measured steps, each movement a performance. The Outer Courtyard is\n"
                    "south, the Audience Chamber north, the Ballroom east, the Servants'\n"
                    "Corridor west, and stairs lead up to the Restricted Wing.";
    r.area_id = "royal_palace";
    r.exits = {
        {Direction::South, "palace_outer_courtyard"},
        {Direction::North, "palace_audience_chamber"},
        {Direction::East, "palace_ballroom"},
        {Direction::West, "palace_servants_corridor"},
        {Direction::Up, "palace_restricted_wing"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_grand_staircase",
        {{"Make a grand entrance",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You descend the staircase slowly, chin raised, back straight.\n";
              std::cout << "Heads turn. Whispers ripple through the courtiers below.\n";
              std::cout << "  \"The duke's daughter. She carries herself like a queen.\"\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 3);
              std::cout << "  Reputation +3\n";
              advanceTime(gs, 5);
          }},
         {"Observe the courtiers",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You pause on the landing and study the flow of people.\n";
              std::cout << "Alliances are visible in who walks with whom, and who pointedly\n";
              std::cout << "avoids whom. You note several nobles speaking with Elena's\n";
              std::cout << "known supporters.\n";
              advanceTime(gs, 5);
          }}});
}
