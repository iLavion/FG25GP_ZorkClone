#include "game.hpp"
#include <iostream>

void registerGarden(GameState &state)
{
    Room r;
    r.id = "garden";
    r.name = "Garden";
    r.description = "A sprawling garden with rose bushes, fountains, and hidden pathways.\n"
                    "Gardener Thorne tends the hedges here. Whispers say he knows secrets\n"
                    "about passages beneath the estate. The Courtyard is north. A winding\n"
                    "path downhill leads to the Village.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::North, "courtyard"},
        {Direction::Down, "village_town_square"}};
    r.travel_time = 8;
    state.rooms[r.id] = r;

    state.rooms["garden"].item_ids.push_back("apple");
    state.rooms["garden"].item_ids.push_back("nightshade");

    registerRoomActions(
        "garden",
        {{"Sit by the fountain",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit on the stone bench beside the fountain. The sound\n";
              std::cout << "of trickling water is soothing. A passing servant curtsies.\n";
              advanceTime(gs, 10);
          }},
         {"Search the hidden pathways",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You wander through the hedge maze. The pathways twist and\n";
              std::cout << "turn, but you notice worn stones leading toward the cellar\n";
              std::cout << "entrance. Thorne must use these often.\n";
          }}});
}