#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerCityBlackMarket(GameState &state)
{
    Room r;
    r.id = "city_black_market";
    r.name = "Black Market Den";
    r.description = "A low-ceilinged basement reeking of damp and tallow candles. Hooded\n"
                    "figures barter over contraband laid out on rough wooden tables: forged\n"
                    "documents, stolen jewels, vials of dubious origin. A fence sits in the\n"
                    "corner, appraising goods with a jeweler's loupe. The Alleyways are north.";
    r.area_id = "city_market_district";
    r.exits = {{Direction::North, "city_alleyways"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_black_market",
        {{"Browse the contraband",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You scan the shadowy tables:\n";
              std::cout << "  - Forged noble seals (useful for fake letters)\n";
              std::cout << "  - A vial labeled " << colored("\"Sweet Dreams\"", ansi::BRIGHT_RED) << "\n";
              std::cout << "  - Lockpicks of various sizes\n";
              std::cout << "  - A dagger with a hidden compartment in the hilt\n";
              gs.player.suspicion += 3;
              std::cout << "  Suspicion +3 (being seen here is dangerous)\n";
              advanceTime(gs, 5);
          }},
         {"Speak with the fence",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The fence looks you up and down, then grins.\n";
              std::cout << "  \"Noble hands, noble coin. What does a lady of the court\n";
              std::cout << "  need from the likes of me?\"\n";
              std::cout << "  \"I can get you documents, alibis, or... remove problems.\"\n";
              gs.player.suspicion += 2;
              std::cout << "  Suspicion +2\n";
              advanceTime(gs, 5);
          }}});
}
