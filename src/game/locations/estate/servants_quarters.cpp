#include "game.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

static std::string hourToTime(int h)
{
    std::string s = (h < 10 ? "0" : "") + std::to_string(h) + ":00";
    return s;
}

void registerServantsQuarters(GameState &state)
{
    Room r;
    r.id = "servants_quarters";
    r.name = "Servants' Quarters";
    r.description = "Modest rooms where the estate staff lives. The air smells of soap and\n"
                    "linen. You can sometimes overhear valuable gossip here.\n"
                    "The Courtyard is west.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::West, "courtyard"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    state.rooms["servants_quarters"].item_ids.push_back("rope");

    registerRoomActions(
        "servants_quarters",
        {{"Check the duty roster",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "\n--- Estate Duty Roster ---\n";
              std::vector<std::string> servant_ids = {
                  "butler_graves", "maid_clara", "captain_roderick",
                  "chef_marcel", "gardener_thorne"};
              for (const auto &npc_id : servant_ids)
              {
                  if (!gs.npcs.count(npc_id))
                  {
                      continue;
                  }
                  const auto &npc = gs.npcs.at(npc_id);
                  std::cout << "\n  " << npc.name << " (" << npc.title << "):\n";

                  std::vector<std::pair<int, std::string>> sorted_sched(
                      npc.schedule.begin(), npc.schedule.end());
                  std::sort(sorted_sched.begin(), sorted_sched.end());

                  for (const auto &[hour, room_id] : sorted_sched)
                  {
                      std::string room_name = room_id;
                      if (gs.rooms.count(room_id))
                          room_name = gs.rooms.at(room_id).name;
                      std::cout << "    " << hourToTime(hour) << " - " << room_name << "\n";
                  }
              }
              std::cout << "\n  [i] Schedules may shift slightly for early risers and night owls.\n";
              std::cout << "\n";
          }},
         {"Eavesdrop on gossip",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("servants_quarters");
              return !room.npc_ids.empty();
          },
          [](GameState &gs)
          {
              std::cout << "You press yourself against the wall and listen...\n\n";
              if (!gs.quest.elena_dead && gs.heroine_popularity >= 30)
              {
                  std::cout << "  \"Did you hear? The Prince sent another letter to Elena!\"\n";
                  std::cout << "  \"She's been spending time in the library, studying our\n";
                  std::cout << "   family's history. What's a commoner need that for?\"\n";
              }
              if (gs.quest.rumors_spread)
              {
                  std::cout << "  \"They say Elena isn't really a commoner, some say\n";
                  std::cout << "   she's got debts, or worse...\"\n";
              }
              if (gs.quest.chef_bribed)
              {
                  std::cout << "  \"Chef Marcel's been acting strange. Extra seasoning\n";
                  std::cout << "   in certain dishes, they say...\"\n";
              }
              if (!gs.quest.rumors_spread && !gs.quest.chef_bribed &&
                  gs.heroine_popularity < 30)
              {
                  std::cout << "  \"Quiet day, innit? The new guest seems pleasant enough.\"\n";
                  std::cout << "  \"Aye, though Lady Seraphina's been eyeing her...\"\n";
              }
              advanceTime(gs, 5);
          }},
         {"Rest on a spare cot",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit on one of the spare cots. Not exactly befitting a\n";
              std::cout << "duke's daughter, but the simple blankets are surprisingly\n";
              std::cout << "comfortable after a long day of scheming.\n";
              gs.player.energy = std::min(100, gs.player.energy + 5);
              std::cout << "  Energy +5 (a brief rest)\n";
              advanceTime(gs, 15);
          }}});
}