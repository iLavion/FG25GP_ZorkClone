#include "game.hpp"
#include <iostream>

void registerNobleRivalGate(GameState &state)
{
    Room r;
    r.id = "noble_rival_gate";
    r.name = "Rival Mansion Gate";
    r.description = "Wrought-iron gates topped with sharp finials guard the entrance to a\n"
                    "rival noble family's estate. Guards in house colors stand at attention.\n"
                    "The crest above the gate belongs to the Whitmore family, old rivals of\n"
                    "your house. Carriage Lane is west, the Rival Garden north.";
    r.area_id = "noble_quarter";
    r.exits = {
        {Direction::West, "noble_carriage_lane"},
        {Direction::North, "noble_rival_garden"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_rival_gate",
        {{"Observe the guard rotation",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You note the guards' patrol patterns. They change shifts every\n";
              std::cout << "two hours. The gate is left less guarded during the changeover.\n";
              advanceTime(gs, 10);
          }}});
}
