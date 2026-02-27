#include "game.hpp"
#include <iostream>

void registerCathedralSideChapel(GameState &state)
{
    Room r;
    r.id = "cathedral_side_chapel";
    r.name = "Side Chapel";
    r.description = "A quiet alcove with votive candles flickering before a painted icon.\n"
                    "Small offerings of flowers and coins are left by the faithful. Carved\n"
                    "into the stone wall, barely visible, are symbols that predate the\n"
                    "cathedral itself. The Nave is south, the Charity Kitchen west.";
    r.area_id = "cathedral";
    r.exits = {
        {Direction::South, "cathedral_nave"},
        {Direction::West, "cathedral_charity_kitchen"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "cathedral_side_chapel",
        {{"Examine the ancient carvings",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You trace the worn symbols with your fingertips. They predate\n";
              std::cout << "the cathedral by centuries, pagan marks from the old faith.\n";
              std::cout << "  One symbol resembles a serpent eating its own tail.\n";
              std::cout << "  Beneath it, scratched in a newer hand: \"Truth lies below.\"\n";
              advanceTime(gs, 5);
          }},
         {"Light a votive candle",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You light a small candle and place it among the others.\n";
              std::cout << "The warm glow joins dozens of tiny flames, each one a prayer.\n";
              advanceTime(gs, 2);
          }}});
}