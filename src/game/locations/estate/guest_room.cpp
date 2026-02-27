#include "game.hpp"
#include <iostream>
#include <algorithm>

void registerGuestRoom(GameState &state)
{
    Room r;
    r.id = "guest_room";
    r.name = "Guest Room";
    r.description = "A well-appointed room prepared for visiting nobles. Currently, the\n"
                    "increasingly popular Elena has been given lodging here.\n"
                    "The Hallway is to the east.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::East, "hallway"}};
    r.travel_time = 1;
    state.rooms[r.id] = r;

    state.rooms["guest_room"].item_ids.push_back("diary");

    registerRoomActions(
        "guest_room",
        {{"Search Elena's belongings",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("guest_room");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(),
                               "elena") == room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "You hastily rummage through Elena's travel chest...\n";
              if (!gs.quest.elena_letters_found)
              {
                  std::cout << "You find letters sealed with the Prince's crest, a small\n";
                  std::cout << "portrait of the royal family, and notes on noble lineages.\n";
                  std::cout << "She's been studying your family, and planning her ascent.\n";
                  gs.quest.elena_letters_found = true;
              }
              else
              {
                  std::cout << "You've already seen your fill. The letters, the notes...\n";
                  std::cout << "Elena is more calculated than she lets on.\n";
              }
              gs.player.suspicion += 8;
              std::cout << "  Suspicion +8 (breaking into someone's belongings!)\n";
              advanceTime(gs, 10);
          }},
         {"Leave a \"gift\" for Elena",
          [](const GameState &gs)
          {
              for (const auto &id : gs.player.inventory)
              {
                  if (id == "perfume" || id == "gold_ring" || id == "silver_brooch")
                      return true;
              }
              return false;
          },
          [](GameState &gs)
          {
              std::string gift_id;
              for (const auto &id : gs.player.inventory)
              {
                  if (id == "perfume" || id == "gold_ring" || id == "silver_brooch")
                  {
                      gift_id = id;
                      break;
                  }
              }
              auto it = std::find(gs.player.inventory.begin(),
                                  gs.player.inventory.end(), gift_id);
              if (it != gs.player.inventory.end())
              {
                  gs.player.inventory.erase(it);
              }
              gs.rooms["guest_room"].item_ids.push_back(gift_id);

              std::cout << "You place the " << gs.items.at(gift_id).name
                        << " on Elena's pillow\n";
              std::cout << "with a note: \"A token of friendship. --S\"\n";
              std::cout << "Whether she trusts it or not, appearances matter.\n";
              gs.npcs["elena"].affection += 10;
              gs.player.reputation = std::min(100, gs.player.reputation + 3);
              std::cout << "  Elena's Affection +10, Reputation +3\n";
          }},
         {"Examine the room for clues",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The guest room is immaculate. Fresh flowers on the nightstand,\n";
              std::cout << "fine linens, a writing desk with fresh ink. Elena keeps her\n";
              std::cout << "space meticulously organized, suspiciously so for a 'simple\n";
              std::cout << "commoner.' A faint perfume scent hints at expensive tastes.\n";
              if (gs.quest.elena_letters_found)
              {
                  std::cout << "\nKnowing what you know about her Prince connection, this\n";
                  std::cout << "opulence makes much more sense...\n";
              }
          }}});
}
