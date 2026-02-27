#include "game.hpp"
#include <iostream>

void registerAcademyRooftopGarden(GameState &state)
{
    Room r;
    r.id = "academy_rooftop_garden";
    r.name = "Rooftop Garden";
    r.description = "A hidden garden atop the academy building. Potted plants, wooden benches,\n"
                    "and a breathtaking view of the city spread below. Few students know about\n"
                    "this place, making it ideal for private meetings. Stairs lead down to the\n"
                    "Archive.";
    r.area_id = "academy";
    r.exits = {{Direction::Down, "academy_archive"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_rooftop_garden",
        {{"Enjoy the view",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lean against the stone railing. The city sprawls below:\n";
              std::cout << "the market district's colorful awnings, the cathedral spire,\n";
              std::cout << "the distant glint of the palace. So much at stake.\n";
              gs.player.energy = std::min(100, gs.player.energy + 5);
              std::cout << "  Energy +5 (a moment of peace)\n";
              advanceTime(gs, 5);
          }},
         {"Search for hidden notes",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You check beneath the benches and behind the flower pots.\n";
              std::cout << "Students use this place for secret rendezvous, there might\n";
              std::cout << "be notes or letters left behind.\n";
              advanceTime(gs, 5);
          }}});
}
