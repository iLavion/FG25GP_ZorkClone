#include "game.hpp"
#include <iostream>

void registerForestWoodlandPath(GameState &state)
{
    Room r;
    r.id = "forest_woodland_path";
    r.name = "Woodland Path";
    r.description = "A narrow dirt path winding between ancient oaks and birches. Dappled\n"
                    "sunlight filters through the canopy. Birdsong and the rustle of leaves\n"
                    "fill the air. The deeper forest beckons north toward a clearing, and\n"
                    "an abandoned shack is visible east. The Tailor Shop in the village is\n"
                    "south.";
    r.area_id = "forest_edge";
    r.exits = {
        {Direction::North, "forest_hunting_clearing"},
        {Direction::East, "forest_abandoned_shack"},
        {Direction::South, "village_tailor"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "forest_woodland_path",
        {{"Gather herbs along the path",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You kneel beside the path, picking useful herbs. Chamomile,\n";
              std::cout << "feverfew, and a few suspect mushrooms that could be medicinal\n";
              std::cout << "or poisonous, depending on the dose.\n";
              advanceTime(gs, 10);
          }},
         {"Listen to the forest",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You stand still and listen. Birdsong, a distant woodpecker,\n";
              std::cout << "the creak of branches. Then, faintly, human voices deeper in\n";
              std::cout << "the woods. Someone else is out here.\n";
              advanceTime(gs, 5);
          }}});
}
