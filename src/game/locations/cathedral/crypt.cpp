#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerCathedralCrypt(GameState &state)
{
    Room r;
    r.id = "cathedral_crypt";
    r.name = "Cathedral Crypt";
    r.description = "Cold, damp corridors lined with stone sarcophagi. The air is thick and\n"
                    "still. Torches in iron brackets cast long shadows across the carved\n"
                    "faces of long-dead bishops and saints. Something about this place feels\n"
                    "older than the cathedral above. Stairs lead up to the Nave.";
    r.area_id = "cathedral";
    r.exits = {{Direction::Up, "cathedral_nave"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    state.rooms["cathedral_crypt"].item_ids.push_back("sealed_scroll");

    registerRoomActions(
        "cathedral_crypt",
        {{"Search the sarcophagi",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You examine the carved stone coffins. Most are sealed tight,\n";
              std::cout << "but one in the far corner has a loose lid.\n";
              std::cout << "  Inside, alongside ancient bones, you find a sealed scroll.\n";
              std::cout << "  " << colored("[i] Use PICKUP to take the scroll.", ansi::CYAN) << "\n";
              advanceTime(gs, 10);
          }},
         {"Look for hidden passages",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You tap along the walls, listening for hollow spots.\n";
              std::cout << "Near the oldest sarcophagus, a section of wall sounds different.\n";
              std::cout << "  A hidden passage? You'd need tools or strength to open it.\n";
              advanceTime(gs, 8);
          }}});
}