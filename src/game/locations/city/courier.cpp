#include "game.hpp"
#include <iostream>

void registerCityCourier(GameState &state)
{
    Room r;
    r.id = "city_courier";
    r.name = "Courier Office";
    r.description = "A tidy office with cubbyholes stuffed with scrolls and sealed letters.\n"
                    "A harried clerk sorts mail behind a wooden counter while messenger\n"
                    "boys wait on a bench, legs swinging. The Bookshop is west.";
    r.area_id = "city_market_district";
    r.exits = {{Direction::West, "city_bookshop"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_courier",
        {{"Check for letters addressed to you",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The clerk rifles through a stack of correspondence.\n";
              std::cout << "  \"Nothing for the duke's household today, my lady.\"\n";
              std::cout << "  Though you notice a sealed letter addressed to Elena\n";
              std::cout << "  sitting conspicuously on the counter.\n";
              advanceTime(gs, 3);
          }},
         {"Intercept Elena's correspondence",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You wait until the clerk turns away, then deftly palm the\n";
              std::cout << "letter addressed to Elena. Your heart races.\n";
              gs.quest.elena_letters_found = true;
              advanceTime(gs, 2);
          }}});
}