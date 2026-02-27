#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerCityAlleyways(GameState &state)
{
    Room r;
    r.id = "city_alleyways";
    r.name = "Alleyways";
    r.description = "Narrow, twisting passages between crumbling brick buildings. Refuse piles\n"
                    "line the walls and rats scurry in the shadows. This is not a place for\n"
                    "a lady of noble birth. The Central Plaza is north, the Black Market Den\n"
                    "lurks south, and a passage east leads to the Docks.";
    r.area_id = "city_market_district";
    r.exits = {
        {Direction::North, "city_central_plaza"},
        {Direction::South, "city_black_market"},
        {Direction::East, "docks_main_pier"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_alleyways",
        {{"Keep to the shadows",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You pull your hood low and move carefully through the gloom.\n";
              std::cout << "A figure leans against a wall, watching you pass.\n";
              std::cout << "  \"Looking for something, milady? Everyone comes here looking\n";
              std::cout << "  for something.\"\n";
              gs.player.suspicion += 2;
              std::cout << "  Suspicion +2 (a noblewoman in the alleys is conspicuous)\n";
              advanceTime(gs, 3);
          }},
         {"Search for hidden passages",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You feel along the soot-stained walls. Behind a loose brick,\n";
              std::cout << "you find a scrap of paper with hastily scrawled directions.\n";
              std::cout << "  " << colored("\"Third warehouse, knock twice, ask for the Raven.\"", ansi::DIM) << "\n";
              advanceTime(gs, 5);
          }}});
}
