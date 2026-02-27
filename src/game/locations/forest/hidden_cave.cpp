#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerForestHiddenCave(GameState &state)
{
    Room r;
    r.id = "forest_hidden_cave";
    r.name = "Hidden Cave";
    r.description = "A narrow cave mouth concealed behind hanging vines. Inside, the ceiling\n"
                    "drips with moisture and the darkness swallows your lantern light after\n"
                    "a few paces. Someone has used this as a hideaway, a bedroll and supplies\n"
                    "are stacked against the wall. The Abandoned Shack is south.";
    r.area_id = "forest_edge";
    r.exits = {{Direction::South, "forest_abandoned_shack"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "forest_hidden_cave",
        {{"Search the supplies",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Among the supplies: dried rations, a tinderbox, rope, and a\n";
              std::cout << "sealed letter addressed to no one.\n";
              std::cout << "  The letter reads: " << colored("\"The girl is not who she claims.", ansi::BRIGHT_YELLOW) << "\n";
              std::cout << "  " << colored("Her real name is not Elena. Find the records in the crypt.\"", ansi::BRIGHT_YELLOW) << "\n";
              advanceTime(gs, 10);
          }},
         {"Rest in the cave",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit on the bedroll, hidden from the world. No one would\n";
              std::cout << "think to look for you here. For a moment, the weight of your\n";
              std::cout << "scheming fades in the quiet darkness.\n";
              gs.player.energy = std::min(100, gs.player.energy + 10);
              std::cout << "  Energy +10\n";
              advanceTime(gs, 15);
          }}});
}
