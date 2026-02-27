#include "game.hpp"
#include <iostream>

void registerBarracksInterrogation(GameState &state)
{
    Room r;
    r.id = "barracks_interrogation";
    r.name = "Interrogation Room";
    r.description = "A stark room with a single table, two chairs, and a flickering lantern.\n"
                    "The walls are bare stone, designed to make occupants feel small and\n"
                    "trapped. Confessions are extracted here, willingly or otherwise.\n"
                    "The Holding Cells are north.";
    r.area_id = "guard_barracks";
    r.exits = {{Direction::North, "barracks_cells"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_interrogation",
        {{"Examine the room",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Scratch marks on the table. Stains on the floor that might be\n";
              std::cout << "wine or might be blood. A cold draft seeps through the stones.\n";
              std::cout << "  This room was built to break people.\n";
              advanceTime(gs, 3);
          }}});
}
