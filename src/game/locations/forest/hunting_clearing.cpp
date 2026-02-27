#include "game.hpp"
#include <iostream>

void registerForestHuntingClearing(GameState &state)
{
    Room r;
    r.id = "forest_hunting_clearing";
    r.name = "Hunting Clearing";
    r.description = "A sunlit glade where hunters have made camp. A circle of stones marks\n"
                    "an old fire pit, and animal tracks cross the soft earth. Deer droppings\n"
                    "suggest game is plentiful. The Woodland Path is south, the Old Ruins east.";
    r.area_id = "forest_edge";
    r.exits = {
        {Direction::South, "forest_woodland_path"},
        {Direction::East, "forest_old_ruins"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "forest_hunting_clearing",
        {{"Search the hunter's camp",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The campsite has been used recently. Charred wood, a forgotten\n";
              std::cout << "waterskin, and boot prints heading deeper into the woods.\n";
              std::cout << "  Whoever camps here does so regularly.\n";
              advanceTime(gs, 5);
          }},
         {"Follow the animal tracks",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You follow the deer tracks into the underbrush. They lead to\n";
              std::cout << "a stream, then vanish. But near the water, you notice a worn\n";
              std::cout << "trail leading east toward crumbling stonework, the old ruins.\n";
              advanceTime(gs, 8);
          }}});
}
