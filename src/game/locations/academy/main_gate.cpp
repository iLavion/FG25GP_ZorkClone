#include "game.hpp"
#include <iostream>

void registerAcademyMainGate(GameState &state)
{
    Room r;
    r.id = "academy_main_gate";
    r.name = "Academy Main Gate";
    r.description = "Tall iron gates flanked by stone pillars mark the entrance to the\n"
                    "Royal Academy. A bulletin board displays class schedules and event\n"
                    "notices. A gate guard checks credentials. The Academy Courtyard is\n"
                    "north. The road west leads back to the City General Store.";
    r.area_id = "academy";
    r.exits = {
        {Direction::North, "academy_courtyard"},
        {Direction::West, "city_general_store"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_main_gate",
        {{"Read the bulletin board",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You scan the announcements:\n";
              std::cout << "  - \"Midterm examinations: next week. Study hard!\"\n";
              std::cout << "  - \"Dueling tournament, open to enrolled students.\"\n";
              if (gs.heroine_popularity >= 30)
              {
                  std::cout << "  - \"Elena receives the Dean's Commendation for Excellence.\"\n";
                  std::cout << "  Even here, her name is everywhere.\n";
              }
              advanceTime(gs, 2);
          }}});
}
