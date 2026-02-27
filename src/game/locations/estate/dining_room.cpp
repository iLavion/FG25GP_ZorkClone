#include "game.hpp"
#include <iostream>

void registerDiningRoom(GameState &state)
{
    Room r;
    r.id = "dining_room";
    r.name = "Dining Room";
    r.description = "An elegant table set for the family. Fine china and crystal glasses await\n"
                    "the next meal. The Grand Hall is west, the Kitchen is north.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::West, "grand_hall"},
        {Direction::North, "kitchen"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["dining_room"].item_ids.push_back("pastry");

    registerRoomActions(
        "dining_room",
        {{"Examine the dinner preparations",
          nullptr,
          [](GameState &gs)
          {
              int h = gs.hour;
              if (h >= 18 && h < 20)
              {
                  std::cout << "The table is set for dinner. Crystal glasses gleam in the\n";
                  std::cout << "candlelight. Place settings for the family... and one for Elena.\n";
              }
              else if (h >= 11 && h < 14)
              {
                  std::cout << "Lunch is being served. Simple but elegant, a clear soup,\n";
                  std::cout << "roast vegetables, and fresh bread from the kitchen.\n";
              }
              else
              {
                  std::cout << "The table stands empty between meals. Pristine china and\n";
                  std::cout << "polished silverware await the next gathering.\n";
              }
          }},
         {"Rearrange the seating",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You subtly rearrange the place cards, putting Elena at the\n";
              std::cout << "far end of the table, away from Father and the seats of honor.\n";
              std::cout << "A small power move, but it sends a message.\n";
              gs.heroine_popularity = std::max(0, gs.heroine_popularity - 1);
              gs.player.suspicion += 1;
              std::cout << "  Elena's Popularity -1, Suspicion +1\n";
          }},
         {"Wait for mealtime",
          [](const GameState &gs)
          {
              int h = gs.hour;
              return (h >= 6 && h < 8) || (h >= 11 && h < 13) || (h >= 18 && h < 20);
          },
          [](GameState &gs)
          {
              std::cout << "You take your seat and wait for the meal to begin...\n";
              advanceTime(gs, 30);
              std::cout << "Time passes as the meal is served. You eat and converse.\n";
              gs.player.hunger = std::min(100, gs.player.hunger + 30);
              gs.player.turns_without_eating = 0;
              std::cout << "  Hunger +30 (full meal)\n";
          }}});
}
