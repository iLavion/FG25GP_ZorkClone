#include "game.hpp"
#include <iostream>

void registerCityBakery(GameState &state)
{
    Room r;
    r.id = "city_bakery";
    r.name = "Bakery";
    r.description = "The warm, yeasty aroma of fresh bread and pastries fills this cheerful\n"
                    "shop. Golden loaves cool on wire racks while the baker kneads dough with\n"
                    "flour-dusted arms. A display case shows iced cakes and honey buns.\n"
                    "The Bookshop is south.";
    r.area_id = "city_market_district";
    r.exits = {{Direction::South, "city_bookshop"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["city_bakery"].item_ids.push_back("sweet_roll");

    registerRoomActions(
        "city_bakery",
        {{"Sample the baker's wares",
          [](const GameState &gs)
          {
              return gs.quest.action_cooldowns.count("bakery_sample") == 0;
          },
          [](GameState &gs)
          {
              std::cout << "The baker offers you a warm honey bun with a beaming smile.\n";
              std::cout << "  \"For such a fine lady, no charge!\"\n";
              gs.player.hunger = std::min(100, gs.player.hunger + 15);
              gs.player.turns_without_eating = 0;
              std::cout << "  Hunger +15\n";
              gs.quest.action_cooldowns["bakery_sample"] = 1;
              advanceTime(gs, 3);
          }}});
}
