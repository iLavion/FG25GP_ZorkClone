#include "game.hpp"
#include <iostream>

void registerBarracksCells(GameState &state)
{
    Room r;
    r.id = "barracks_cells";
    r.name = "Holding Cells";
    r.description = "Iron-barred cells line a damp corridor. A few prisoners sit in the gloom,\n"
                    "some sullen, some desperate. A guard patrols the walkway, keys jangling.\n"
                    "The Front Desk is east, the Interrogation Room south.";
    r.area_id = "guard_barracks";
    r.exits = {
        {Direction::East, "barracks_front_desk"},
        {Direction::South, "barracks_interrogation"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_cells",
        {{"Speak with a prisoner",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "A ragged man presses against the bars.\n";
              std::cout << "  \"My lady, I have information. Get me out and I'll tell you\n";
              std::cout << "  everything about Elena's benefactors.\"\n";
              std::cout << "  He could be lying, or he could be the lead you need.\n";
              advanceTime(gs, 5);
          }},
         {"Bribe the cell guard",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You slip a few coins to the guard.\n";
              std::cout << "  \"I didn't see nothing, my lady.\" He turns his back.\n";
              advanceTime(gs, 3);
          }}});
}