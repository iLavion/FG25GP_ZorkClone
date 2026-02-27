#include "game.hpp"
#include <iostream>

void registerNobleDiplomat(GameState &state)
{
    Room r;
    r.id = "noble_diplomat";
    r.name = "Diplomat Residence";
    r.description = "An elegant townhouse flying a foreign flag. The interior is decorated\n"
                    "with exotic tapestries and unfamiliar art. A foreign ambassador resides\n"
                    "here, a useful contact for those who think beyond local politics.\n"
                    "Carriage Lane is east. The Guard Barracks lie north.";
    r.area_id = "noble_quarter";
    r.exits = {
        {Direction::East, "noble_carriage_lane"},
        {Direction::North, "barracks_front_desk"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_diplomat",
        {{"Request an audience with the ambassador",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The ambassador receives you in a sitting room fragrant with\n";
              std::cout << "foreign spices. He speaks carefully, weighing every word.\n";
              std::cout << "  \"Duke's daughter, your family's situation is... known abroad.\"\n";
              std::cout << "  \"Perhaps we can help each other.\"\n";
              advanceTime(gs, 10);
          }},
         {"Examine the foreign correspondence",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "While the ambassador is distracted, you glance at the letters\n";
              std::cout << "on his desk. Most are in a foreign script, but one is in your\n";
              std::cout << "language, addressed to Elena.\n";
              advanceTime(gs, 5);
          }}});
}