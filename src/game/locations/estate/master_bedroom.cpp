#include "game.hpp"
#include <iostream>
#include <algorithm>

void registerMasterBedroom(GameState &state)
{
    Room r;
    r.id = "master_bedroom";
    r.name = "Master Bedroom";
    r.description = "The Duke and Duchess's private chambers. A massive four-poster bed\n"
                    "dominates the room, draped in deep blue velvet. A crackling fireplace\n"
                    "warms the space, and a portrait of your late mother hangs above the\n"
                    "mantle. The scent of pipe tobacco and dried lavender lingers. The\n"
                    "Hallway is north.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::North, "hallway"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "master_bedroom",
        {{"Examine Mother's portrait",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "The painting shows a woman with warm, brown eyes and a gentle smile.\n";
              std::cout << "Duchess Elara Aldric, your mother, who passed when Rosalind was still\n";
              std::cout << "young. She holds a single white rose, the Aldric family crest behind\n";
              std::cout << "her. Father kept this room exactly as she left it.\n";
          }},
         {"Search the dresser",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("master_bedroom");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(), "duke_aldric") == room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "You quietly rummage through the dresser drawers...\n";
              std::cout << "Old letters from Mother, a faded military medal, and a small\n";
              std::cout << "portrait of the family when you were all children.\n";
              std::cout << "At the bottom, you find a sealed envelope addressed to the Crown.\n";
              std::cout << "Father has been corresponding with the Royal Court about Elena.\n";
              gs.quest.elena_letters_found = true;
              advanceTime(gs, 5);
          }},
         {"Sit by the fireplace",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You settle into the armchair by the fire. The warmth seeps into\n";
              std::cout << "your bones. For a moment, you can pretend the world outside this\n";
              std::cout << "room does not exist, no Elena, no schemes, no politics.\n";
              gs.player.energy = std::min(100, gs.player.energy + 5);
              std::cout << "  Energy +5 (resting by the fire)\n";
              advanceTime(gs, 10);
          }},
         {"Check on Father",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("master_bedroom");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(), "duke_aldric") != room.npc_ids.end();
          },
          [](GameState &gs)
          {
              if (gs.npcs.count("duke_aldric") && gs.npcs.at("duke_aldric").alive)
              {
                  int h = gs.hour;
                  if (h >= 22 || h < 6)
                  {
                      std::cout << "Father is asleep. His breathing is slow and steady. The\n";
                      std::cout << "weight of the dukedom leaves him, just for these hours.\n";
                  }
                  else
                  {
                      std::cout << "Father is resting in his chair by the fire, reviewing a\n";
                      std::cout << "few last documents before returning to his study.\n";
                  }
              }
              else
              {
                  std::cout << "The room is painfully still. Father's chair sits empty.\n";
                  std::cout << "The fire has gone cold.\n";
              }
          }}});
}
