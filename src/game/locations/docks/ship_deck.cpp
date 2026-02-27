#include "game.hpp"
#include <iostream>

void registerDocksShipDeck(GameState &state)
{
    Room r;
    r.id = "docks_ship_deck";
    r.name = "Ship Deck";
    r.description = "The deck of a merchant vessel, the Silver Gull. Ropes, barrels, and\n"
                    "furled sails crowd the space. The captain, a weathered woman with a\n"
                    "sharp eye, oversees the loading of cargo. The Main Pier is west.";
    r.area_id = "docks";
    r.exits = {{Direction::West, "docks_main_pier"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_ship_deck",
        {{"Speak with the captain",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The captain tips her hat.\n";
              std::cout << "  \"A noblewoman on my deck? Must be desperate or daring.\"\n";
              std::cout << "  \"I sail in three days. If you need passage, bring coin.\"\n";
              advanceTime(gs, 5);
          }},
         {"Search the cargo hold",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You slip below deck while the crew is busy. The cargo hold\n";
              std::cout << "contains standard trade goods, but hidden beneath a false\n";
              std::cout << "floor you find a compartment, sized for a person.\n";
              std::cout << "  An escape route, or a way to smuggle someone in.\n";
              advanceTime(gs, 8);
          }}});
}