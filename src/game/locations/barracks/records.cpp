#include "game.hpp"
#include <iostream>

void registerBarracksRecords(GameState &state)
{
    Room r;
    r.id = "barracks_records";
    r.name = "Records Office";
    r.description = "Filing cabinets line every wall, stuffed with criminal records,\n"
                    "investigation reports, and incident logs. A clerk sorts papers with\n"
                    "meticulous care. The musty smell of old ink permeates the air.\n"
                    "The Front Desk is south.";
    r.area_id = "guard_barracks";
    r.exits = {{Direction::South, "barracks_front_desk"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_records",
        {{"Search for Elena's records",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You flip through the files under 'E.' Elena's folder is thin,\n";
              std::cout << "no criminal record, but there's a note from a constable:\n";
              std::cout << "  \"Background check requested. Origins unverifiable.\"\n";
              std::cout << "  Someone else has been asking questions about her past.\n";
              gs.player.suspicion += 2;
              std::cout << "  Suspicion +2 (poking through official records)\n";
              advanceTime(gs, 10);
          }},
         {"Look for blackmail material",
          [](const GameState &gs)
          {
              return gs.player.suspicion < 50;
          },
          [](GameState &gs)
          {
              std::cout << "You search for files on nobles who might be compromised.\n";
              std::cout << "Several sealed folders catch your eye, marked \"Confidential.\"\n";
              std::cout << "  Opening them here would be reckless. You'd need privacy.\n";
              gs.player.suspicion += 3;
              std::cout << "  Suspicion +3\n";
              advanceTime(gs, 8);
          }}});
}
