#include "game.hpp"
#include <iostream>

void registerCityApothecary(GameState &state)
{
    Room r;
    r.id = "city_apothecary";
    r.name = "Apothecary";
    r.description = "Glass jars of dried herbs, powdered minerals, and strange liquids line\n"
                    "floor-to-ceiling shelves. The air is thick with the scent of lavender\n"
                    "and something sharper beneath it. An alchemist works behind the counter,\n"
                    "mortar and pestle in hand. The Central Plaza is east.";
    r.area_id = "city_market_district";
    r.exits = {{Direction::East, "city_central_plaza"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_apothecary",
        {{"Browse the remedies",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You scan the labeled jars: headache powders, sleeping draughts,\n";
              std::cout << "fever tonics, and various herbal salves.\n";
              std::cout << "  Behind the counter, you notice a locked cabinet with no label.\n";
              std::cout << "  [i] The alchemist might sell you something... special.\n";
              advanceTime(gs, 3);
          }},
         {"Ask about poisons",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lower your voice. \"I need something for... pests.\"\n";
              std::cout << "The alchemist eyes you carefully.\n";
              std::cout << "  \"Pests, you say. I have rat poison and garden treatments.\"\n";
              std::cout << "  \"Anything stronger requires... a more private arrangement.\"\n";
              advanceTime(gs, 5);
          }}});
}