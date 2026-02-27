#include "game.hpp"
#include <iostream>

void registerPalaceBallroom(GameState &state)
{
    Room r;
    r.id = "palace_ballroom";
    r.name = "Palace Ballroom";
    r.description = "An enormous ballroom with crystal chandeliers, mirrored walls, and a\n"
                    "gleaming parquet floor. An orchestra balcony overlooks the dance floor.\n"
                    "Grand balls held here shape the social landscape of the kingdom.\n"
                    "The Grand Staircase is west.";
    r.area_id = "royal_palace";
    r.exits = {{Direction::West, "palace_grand_staircase"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_ballroom",
        {{"Imagine the next grand ball",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You stand in the center of the empty ballroom. Crystal light\n";
              std::cout << "from the chandeliers scatters across the mirrors. At the next\n";
              std::cout << "royal ball, Elena will be here. And so will you.\n";
              std::cout << "  The question is: who will the Prince ask to dance?\n";
              advanceTime(gs, 5);
          }},
         {"Check the orchestra balcony",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You climb to the orchestra balcony. From here, you can see the\n";
              std::cout << "entire ballroom. An excellent vantage point for observation,\n";
              std::cout << "or for arranging an accidental chandelier mishap.\n";
              gs.player.suspicion += 1;
              std::cout << "  Suspicion +1 (plotting is written on your face)\n";
              advanceTime(gs, 5);
          }}});
}
