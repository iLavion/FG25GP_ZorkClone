#include "game.hpp"
#include <iostream>

void registerVillageInnRooms(GameState &state)
{
    Room r;
    r.id = "village_inn_rooms";
    r.name = "Inn Guest Rooms";
    r.description = "A narrow corridor of small but tidy guest rooms. The floorboards creak\n"
                    "with every step. Thin walls mean voices carry easily, useful for those\n"
                    "with keen ears. The staircase leads down to the common room.";
    r.area_id = "village_suburb";
    r.exits = {{Direction::Down, "village_inn"}};
    r.allows_sleep = true;
    r.travel_time = 1;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_inn_rooms",
        {{"Rest in your rented room",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lie down on the narrow bed. The mattress is lumpy but\n";
              std::cout << "serviceable. You can hear muffled laughter from below.\n";
              std::cout << "  [i] Use SLEEP to rest properly.\n";
          }},
         {"Listen through the walls",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You press your ear to the thin wall. Fragments of conversation\n";
              std::cout << "drift through:\n";
              std::cout << "  \"...smugglers at the docks have what you need...\"\n";
              std::cout << "  \"...keep it quiet, the guard captain has ears everywhere...\"\n";
              gs.player.suspicion += 1;
              std::cout << "  Suspicion +1\n";
              advanceTime(gs, 5);
          }}});
}
