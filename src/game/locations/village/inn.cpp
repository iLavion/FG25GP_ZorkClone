#include "game.hpp"
#include <iostream>

void registerVillageInn(GameState &state)
{
    Room r;
    r.id = "village_inn";
    r.name = "Inn Common Room";
    r.description = "A warm, rowdy common room thick with pipe smoke and laughter. A crackling\n"
                    "hearth dominates one wall while travelers and locals sit elbow-to-elbow\n"
                    "at long wooden tables. A staircase leads up to the guest rooms.\n"
                    "The Town Square is west.";
    r.area_id = "village_suburb";
    r.exits = {
        {Direction::West, "village_town_square"},
        {Direction::Up, "village_inn_rooms"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_inn",
        {{"Order a drink at the bar",
          [](const GameState &gs)
          {
              return gs.quest.action_cooldowns.count("inn_drink") == 0;
          },
          [](GameState &gs)
          {
              std::cout << "The innkeeper slides a tankard of spiced cider across the counter.\n";
              std::cout << "  \"On the house for a lady of your standing,\" he says with a wink.\n";
              gs.player.hunger = std::min(100, gs.player.hunger + 5);
              std::cout << "  Hunger +5\n";
              gs.quest.action_cooldowns["inn_drink"] = 1;
              advanceTime(gs, 5);
          }},
         {"Eavesdrop on the travelers",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit near a group of road-weary merchants.\n";
              std::cout << "  \"...the Prince has been seen with that commoner girl again.\"\n";
              std::cout << "  \"Elena? She's the talk of every tavern from here to the capital.\"\n";
              advanceTime(gs, 8);
          }}});
}