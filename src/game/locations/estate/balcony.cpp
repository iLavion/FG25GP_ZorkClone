#include "game.hpp"
#include <iostream>

void registerBalcony(GameState &state)
{
    Room r;
    r.id = "balcony";
    r.name = "Balcony";
    r.description = "An elevated overlook from your bedroom. The evening breeze carries the\n"
                    "scent of roses from the garden below. A good place to think... or scheme.\n"
                    "Your Bedroom is to the west.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::West, "bedroom"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "balcony",
        {{"Survey the estate below",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lean against the railing and survey the courtyard and gardens.\n";
              bool saw_someone = false;
              for (const auto &room_id : {std::string("courtyard"), std::string("garden")})
              {
                  if (!gs.rooms.count(room_id))
                  {
                      continue;
                  }
                  for (const auto &npc_id : gs.rooms.at(room_id).npc_ids)
                  {
                      if (gs.npcs.count(npc_id))
                      {
                          std::cout << "  You spot " << gs.npcs.at(npc_id).name
                                    << " in the " << gs.rooms.at(room_id).name << ".\n";
                          saw_someone = true;
                      }
                  }
              }
              if (!saw_someone)
              {
                  std::cout << "The grounds seem quiet at this hour.\n";
              }
          }},
         {"Enjoy the view",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You take a deep breath and enjoy the panoramic view of the estate.\n";
              std::cout << "The rolling hills beyond the walls remind you of childhood summers.\n";
          }}});
}
