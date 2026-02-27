#include "game.hpp"
#include <iostream>

void registerNobleCarriageLane(GameState &state)
{
    Room r;
    r.id = "noble_carriage_lane";
    r.name = "Carriage Lane";
    r.description = "A wide, tree-lined boulevard where polished carriages roll past elegant\n"
                    "townhouses. Gas lanterns illuminate marble facades. Noble families display\n"
                    "their wealth openly here. The Salon House is north, the Masquerade Hall\n"
                    "south, the Rival Mansion east, and the Diplomat Residence west. A grand\n"
                    "road leads uphill to the Royal Palace, and downhill to the City Market.";
    r.area_id = "noble_quarter";
    r.exits = {
        {Direction::North, "noble_salon"},
        {Direction::South, "noble_masquerade_hall"},
        {Direction::East, "noble_rival_gate"},
        {Direction::West, "noble_diplomat"},
        {Direction::Up, "palace_outer_courtyard"},
        {Direction::Down, "city_apothecary"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_carriage_lane",
        {{"Survey the passing carriages",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You observe the carriages rolling past. House crests on the doors\n";
              std::cout << "tell you who is visiting whom. Political alliances are made and\n";
              std::cout << "broken on this very street.\n";
              advanceTime(gs, 5);
          }},
         {"Greet the neighboring nobles",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You exchange pleasantries with passing nobles. Smiles that don't\n";
              std::cout << "reach the eyes, compliments laced with barbs. The usual.\n";
              advanceTime(gs, 5);
          }}});
}