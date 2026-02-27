#include "game.hpp"
#include <iostream>

void registerVillageTailor(GameState &state)
{
    Room r;
    r.id = "village_tailor";
    r.name = "Tailor Shop";
    r.description = "Bolts of fabric in every color line the walls of this cramped shop.\n"
                    "A bespectacled tailor works diligently at a sewing table, pins held\n"
                    "between pursed lips. Mannequins display the latest village fashions.\n"
                    "The Town Square is east. A trail west leads toward the forest.";
    r.area_id = "village_suburb";
    r.exits = {
        {Direction::East, "village_town_square"},
        {Direction::West, "forest_woodland_path"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_tailor",
        {{"Browse the disguises",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You examine the racks of clothing. A servant's dress, a\n";
              std::cout << "merchant's cloak, even a nun's habit. With the right outfit,\n";
              std::cout << "you could move through the common quarters unnoticed.\n";
              std::cout << "  [i] Use PICKUP to take a disguise if available.\n";
              advanceTime(gs, 3);
          }},
         {"Chat with the tailor",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The tailor peers at you over his spectacles.\n";
              std::cout << "  \"A noblewoman in my humble shop? I'm honored.\"\n";
              std::cout << "  \"I hear things, you know. People talk while being fitted.\"\n";
              std::cout << "  [i] Use TALK to have a proper conversation.\n";
              advanceTime(gs, 2);
          }}});
}
