#include "game.hpp"
#include <iostream>

void registerAcademyDormitory(GameState &state)
{
    Room r;
    r.id = "academy_dormitory";
    r.name = "Dormitory Hall";
    r.description = "A long corridor of shared student rooms. The walls are thin and voices\n"
                    "carry. Personal effects, books, letters, and small trinkets, are visible\n"
                    "through half-open doors. The Courtyard is east.";
    r.area_id = "academy";
    r.exits = {{Direction::East, "academy_courtyard"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_dormitory",
        {{"Peek into the student rooms",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You glance through the open doorways as you walk past.\n";
              std::cout << "Messy beds, scattered textbooks, a love letter pinned to a wall.\n";
              std::cout << "Nothing immediately useful, but the gossip potential is rich.\n";
              gs.player.suspicion += 1;
              std::cout << "  Suspicion +1 (snooping in the dormitory)\n";
              advanceTime(gs, 5);
          }},
         {"Listen to student gossip",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "From behind a closed door, you catch muffled voices:\n";
              std::cout << "  \"...Elena turned down Lord Ashworth's proposal. Can you believe it?\"\n";
              std::cout << "  \"She said she's not interested in titles. What commoner says that?\"\n";
              advanceTime(gs, 5);
          }}});
}
