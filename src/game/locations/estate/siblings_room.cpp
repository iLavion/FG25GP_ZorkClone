#include "game.hpp"
#include <iostream>
#include <algorithm>

void registerSiblingsRoom(GameState &state)
{
    Room r;
    r.id = "siblings_room";
    r.name = "Sibling's Room";
    r.description = "Shared quarters for Lord Cedric and Lady Rosalind. Toys and books are\n"
                    "scattered about, Rosalind's dolls next to Cedric's fencing gloves.\n"
                    "The Hallway is to the south.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::South, "hallway"}};
    r.travel_time = 1;
    state.rooms[r.id] = r;

    registerRoomActions(
        "siblings_room",
        {{"Look through Cedric's things",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("siblings_room");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(),
                               "cedric") == room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "You rifle through Cedric's desk. Training notes, a sketch\n";
              std::cout << "of a sword technique... and a pressed flower.\n";
              std::cout << "Wait, there's a note in Elena's handwriting:\n";
              std::cout << "  \"Dear Cedric, thank you for showing me the garden.\n";
              std::cout << "   Your kindness means more than you know. --E\"\n\n";
              std::cout << "So Elena has been getting close to your brother...\n";
              gs.player.suspicion += 3;
              std::cout << "  Suspicion +3 (searching a family member's room)\n";
          }},
         {"Play with Rosalind's dolls",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("siblings_room");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(),
                               "rosalind") != room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "You sit down with Rosalind and play with her dolls.\n";
              std::cout << "\"This one is you, sister!\" She beams, holding up a doll\n";
              std::cout << "in a red dress. \"And this one is Elena! They're friends!\"\n";
              std::cout << "You manage a smile, but your grip on the doll tightens.\n";
              gs.npcs["rosalind"].affection += 5;
              std::cout << "  Rosalind's Affection +5\n";
              advanceTime(gs, 15);
          }},
         {"Examine Cedric's fencing equipment",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "Fencing gloves, a practice foil, and a training dummy in the\n";
              std::cout << "corner. Cedric takes his swordsmanship seriously. You recall\n";
              std::cout << "he won the youth tournament three years running.\n";
              std::cout << "  [i] A sister who fences might be useful someday...\n";
          }}});
}
