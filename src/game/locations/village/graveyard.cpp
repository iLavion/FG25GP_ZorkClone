#include "game.hpp"
#include <iostream>

void registerVillageGraveyard(GameState &state)
{
    Room r;
    r.id = "village_graveyard";
    r.name = "Village Graveyard";
    r.description = "Crooked headstones rise from the damp earth behind the chapel. Moss\n"
                    "and ivy creep over the older graves. A stone angel watches from the\n"
                    "center, its face worn smooth by centuries of rain. The Chapel is west.";
    r.area_id = "village_suburb";
    r.exits = {{Direction::West, "village_chapel"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_graveyard",
        {{"Examine the old headstones",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You trace the faded inscriptions on the oldest stones.\n";
              std::cout << "  \"Here lies Baron Aldwin, friend to kings, foe to tyrants.\"\n";
              std::cout << "  Beneath the moss, you notice a family crest, your family crest.\n";
              std::cout << "  An ancestor, buried among commoners. Curious.\n";
          }},
         {"Search among the graves",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You carefully look around the less-tended plots.\n";
              std::cout << "Between two crumbling stones, something glints in the dirt.\n";
              bool found = false;
              for (const auto &id : gs.rooms.at("village_graveyard").item_ids)
              {
                  if (id == "old_locket")
                  {
                      found = true;
                  }
              }
              if (!found)
              {
                  gs.rooms["village_graveyard"].item_ids.push_back("old_locket");
                  std::cout << "  You uncover an old locket half-buried in the soil.\n";
              }
              else
              {
                  std::cout << "  Nothing else catches your eye.\n";
              }
              advanceTime(gs, 5);
          }}});
}
