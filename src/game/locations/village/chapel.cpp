#include "game.hpp"
#include <iostream>

void registerVillageChapel(GameState &state)
{
    Room r;
    r.id = "village_chapel";
    r.name = "Village Chapel";
    r.description = "A modest stone chapel with a steeply pitched roof. Candles flicker\n"
                    "in iron sconces and the scent of incense lingers. A kindly priest\n"
                    "tends the altar. The Town Square is south, the Graveyard east, and a\n"
                    "path north leads to the grand Cathedral.";
    r.area_id = "village_suburb";
    r.exits = {
        {Direction::South, "village_town_square"},
        {Direction::East, "village_graveyard"},
        {Direction::North, "cathedral_nave"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_chapel",
        {{"Pray at the altar",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You kneel before the simple altar and clasp your hands.\n";
              std::cout << "The silence is calming. Whatever schemes await, a moment\n";
              std::cout << "of peace steadies your nerves.\n";
              gs.player.suspicion = std::max(0, gs.player.suspicion - 2);
              std::cout << "  Suspicion -2 (pious behavior looks innocent)\n";
              advanceTime(gs, 5);
          }},
         {"Speak with the priest",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The elderly priest turns to you with a warm smile.\n";
              std::cout << "  \"My child, the heavens see all. Walk with grace.\"\n";
              std::cout << "He seems willing to talk further.\n";
              std::cout << "  [i] Use TALK to begin a proper conversation.\n";
              advanceTime(gs, 2);
          }}});
}
