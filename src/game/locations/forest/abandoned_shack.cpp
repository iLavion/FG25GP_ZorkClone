#include "game.hpp"
#include <iostream>

void registerForestAbandonedShack(GameState &state)
{
    Room r;
    r.id = "forest_abandoned_shack";
    r.name = "Abandoned Shack";
    r.description = "A dilapidated wooden shack with a sagging roof and broken windows.\n"
                    "Inside, a dusty table, a rusted stove, and a moth-eaten bedroll.\n"
                    "Someone lived here once. Empty bottles and scattered papers suggest\n"
                    "a hermit or fugitive. The Woodland Path is west, a Hidden Cave north.";
    r.area_id = "forest_edge";
    r.exits = {
        {Direction::West, "forest_woodland_path"},
        {Direction::North, "forest_hidden_cave"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "forest_abandoned_shack",
        {{"Search the shack",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You rifle through the debris. Under the bedroll, a leather\n";
              std::cout << "journal with water-damaged pages. The handwriting is frantic:\n";
              std::cout << "  \"...they know what I found. The truth about the girl. Must\n";
              std::cout << "  hide the evidence before they silence me...\"\n";
              std::cout << "  The remaining pages are too damaged to read.\n";
              advanceTime(gs, 8);
          }},
         {"Check the stove",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "Ash and charred paper fragments. Someone burned documents here\n";
              std::cout << "recently, the ash is still soft. Whatever was destroyed, they\n";
              std::cout << "didn't want anyone reading it.\n";
          }}});
}
