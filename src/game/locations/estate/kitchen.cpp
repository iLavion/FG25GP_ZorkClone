#include "game.hpp"
#include <iostream>

void registerKitchen(GameState &state)
{
    Room r;
    r.id = "kitchen";
    r.name = "Kitchen";
    r.description = "A bustling room filled with the aroma of roasted meats and fresh bread.\n"
                    "Copper pots hang from the ceiling. Chef Marcel rules here with an iron ladle.\n"
                    "The Dining Room is to the south. Stairs lead down to the Cellar.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::South, "dining_room"},
        {Direction::Down, "cellar"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["kitchen"].item_ids.push_back("bread");
    state.rooms["kitchen"].item_ids.push_back("knife");
    state.rooms["kitchen"].item_ids.push_back("tea_set");

    registerRoomActions(
        "kitchen",
        {{"Sample from the cooking pot",
          [](const GameState &gs)
          {
              return gs.quest.action_cooldowns.count("kitchen_pot") == 0;
          },
          [](GameState &gs)
          {
              std::cout << "You dip a silver spoon into the simmering pot. A rich broth\n";
              std::cout << "fills your mouth, herbs, venison, a hint of wine.\n";
              gs.player.hunger = std::min(100, gs.player.hunger + 10);
              gs.player.turns_without_eating = 0;
              std::cout << "  Hunger restored slightly. (+10)\n";
              gs.quest.action_cooldowns["kitchen_pot"] = 1;
          }},
         {"Inspect the pantry",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "The pantry is well-stocked: preserved meats, jars of honey,\n";
              std::cout << "dried herbs, fine flour, and an impressive wine collection.\n";
              std::cout << "You notice a locked cabinet labeled \"Medicinal Supplies.\"\n";
              std::cout << "  [i] Perhaps someone with alchemy knowledge could open it.\n";
          }},
         {"Check tea preparations",
          [](const GameState &gs)
          {
              return gs.quest.elena_arrived_dinner;
          },
          [](GameState &gs)
          {
              if (gs.quest.poisoned_tea)
              {
                  std::cout << "The poisoned tea sits innocently on the counter, ready\n";
                  std::cout << "to be served. Your hands tremble slightly.\n";
              }
              else
              {
                  std::cout << "The tea service is being prepared. The finest porcelain,\n";
                  std::cout << "imported tea leaves, honey cakes on the side.\n";
                  std::cout << "  [i] This would be the perfect opportunity to add something...\n";
              }
          }}});
}
