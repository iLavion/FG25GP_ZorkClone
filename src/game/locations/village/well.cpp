#include "game.hpp"
#include <iostream>

void registerVillageWell(GameState &state)
{
    Room r;
    r.id = "village_well";
    r.name = "Village Well";
    r.description = "A deep stone well surrounded by a low wall. Women gather here to draw\n"
                    "water and exchange whispers. The well's echo carries voices strangely,\n"
                    "as if the stones themselves listen. The Small Market is west.";
    r.area_id = "village_suburb";
    r.exits = {{Direction::West, "village_market"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_well",
        {{"Listen to the washerwomen gossip",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You linger by the well as women scrub laundry on the stones.\n";
              std::cout << "  \"...the heroine Elena gave coin to the poorhouse again.\"\n";
              std::cout << "  \"She's too good to be true, that one. Mark my words.\"\n";
              std::cout << "  At least not everyone is fooled.\n";
              advanceTime(gs, 5);
          }},
         {"Drop a coin and make a wish",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You toss a silver coin into the dark water below.\n";
              std::cout << "It glints once before vanishing into the depths.\n";
              std::cout << "  \"Let Elena's star fall before mine rises,\" you whisper.\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 1);
              std::cout << "  Reputation +1 (showing humility at the well)\n";
              advanceTime(gs, 2);
          }}});
}
