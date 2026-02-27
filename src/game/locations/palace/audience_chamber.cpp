#include "game.hpp"
#include <iostream>

void registerPalaceAudienceChamber(GameState &state)
{
    Room r;
    r.id = "palace_audience_chamber";
    r.name = "Audience Chamber";
    r.description = "A formal chamber where the royal family receives petitioners and guests.\n"
                    "Cushioned chairs line the walls and a long table holds refreshments.\n"
                    "The Prince is often seen here, holding court with advisors and nobles.\n"
                    "The Throne Room is north, the Grand Staircase south.";
    r.area_id = "royal_palace";
    r.exits = {
        {Direction::North, "palace_throne_room"},
        {Direction::South, "palace_grand_staircase"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "palace_audience_chamber",
        {{"Request an audience with the Prince",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "A chamberlain takes your request and disappears behind a curtain.\n";
              std::cout << "After a lengthy wait, he returns.\n";
              if (gs.player.reputation >= 50)
              {
                  std::cout << "  \"His Highness will see you. Please proceed.\"\n";
              }
              else
              {
                  std::cout << "  \"His Highness is occupied. Perhaps another time, my lady.\"\n";
              }
              advanceTime(gs, 15);
          }},
         {"Mingle with the petitioners",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You circulate among the waiting nobles and officials.\n";
              std::cout << "Conversations are guarded but revealing. Everyone wants\n";
              std::cout << "something from the crown, and everyone is watching everyone else.\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 1);
              std::cout << "  Reputation +1\n";
              advanceTime(gs, 10);
          }}});
}
