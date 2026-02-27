#include "game.hpp"
#include <iostream>

void registerVillageTownSquare(GameState &state)
{
    Room r;
    r.id = "village_town_square";
    r.name = "Town Square";
    r.description = "The heart of the village suburb. A weathered notice board stands beside\n"
                    "a cobblestone well. Merchants hawk their wares from creaking stalls while\n"
                    "villagers gossip by the old oak tree. The Chapel is north, the Small Market\n"
                    "south, the Inn east, and the Tailor's shop west. A winding path leads\n"
                    "uphill toward the Ducal Estate.";
    r.area_id = "village_suburb";
    r.exits = {
        {Direction::North, "village_chapel"},
        {Direction::South, "village_market"},
        {Direction::East, "village_inn"},
        {Direction::West, "village_tailor"},
        {Direction::Up, "garden"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "village_town_square",
        {{"Read the notice board",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You scan the weathered notices pinned to the board:\n";
              std::cout << "  - \"Seeking able workers for the harvest. Inquire at the Inn.\"\n";
              std::cout << "  - \"Lost: one grey tabby cat, answers to 'Lord Whiskers.'\"\n";
              if (gs.heroine_popularity >= 30)
              {
                  std::cout << "  - \"The Lady Elena hosts a charity tea this weekend!\"\n";
                  std::cout << "  You feel your jaw tighten.\n";
              }
              advanceTime(gs, 2);
          }},
         {"Listen to the village gossip",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You linger near the old oak tree where villagers chatter.\n";
              if (gs.heroine_popularity >= 40)
              {
                  std::cout << "  \"That Elena girl, she's been invited to the royal court!\"\n";
                  std::cout << "  \"A commoner at court? Times are changing...\"\n";
              }
              else
              {
                  std::cout << "  \"The duke's daughter was seen in the village again.\"\n";
                  std::cout << "  \"Rare sight, that. Must be up to something.\"\n";
              }
              gs.player.suspicion += 1;
              std::cout << "  Suspicion +1 (a noblewoman eavesdropping draws attention)\n";
              advanceTime(gs, 5);
          }}});
}
