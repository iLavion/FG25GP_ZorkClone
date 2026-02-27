#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void registerCourtyard(GameState &state)
{
    Room r;
    r.id = "courtyard";
    r.name = "Courtyard";
    r.description = "A wide open area at the center of the estate. A stone fountain stands\n"
                    "in the middle. Guards patrol here. The Grand Hall is north, the Garden\n"
                    "is south, and the Servants' Quarters are east.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::North, "grand_hall"},
        {Direction::South, "garden"},
        {Direction::East, "servants_quarters"}};
    r.travel_time = 5;
    state.rooms[r.id] = r;

    registerRoomActions(
        "courtyard",
        {{"Watch the guards patrol",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You observe the guards making their rounds. Two at the gate,\n";
              std::cout << "one circling the perimeter, and Captain Roderick directing from\n";
              std::cout << "the center. Their patrol takes roughly 20 minutes per cycle.\n";
              int h = gs.hour;
              if (h >= 22 || h < 5)
              {
                  std::cout << "  The night watch is lighter. Only two guards visible.\n";
                  std::cout << "  [i] Late night might be an opportunity for discreet movement.\n";
              }
              else
              {
                  std::cout << "  Security is tight during the day. Be careful.\n";
              }
              advanceTime(gs, 5);
          }},
         {"Practice your deportment",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You walk a slow circuit of the courtyard with perfect posture,\n";
              std::cout << "chin high, hands folded. A lady of the house must always appear\n";
              std::cout << "poised. Passing servants bow respectfully.\n";
              advanceTime(gs, 10);
          }},
         {"Sit by the fountain and think",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit on the cool stone rim of the fountain. Water splashes\n";
              std::cout << "softly as you collect your thoughts. The estate sprawls around\n";
              std::cout << "you, your home, your battlefield.\n\n";
              std::cout << "  Elena's Popularity: " << gs.heroine_popularity << "/100\n";
              if (gs.heroine_popularity >= 60)
                  std::cout << "  [!] Time is running out. Elena grows more influential.\n";
              advanceTime(gs, 5);
          }},
         {"Wash in the fountain",
          [](const GameState &gs)
          { return gs.quest.player_bloodied; },
          [](GameState &gs)
          {
              const Room &room = gs.rooms.at("courtyard");
              bool witnessed = false;
              for (const auto &npc_id : room.npc_ids)
              {
                  if (gs.npcs.count(npc_id) && gs.npcs.at(npc_id).alive)
                  {
                      witnessed = true;
                      std::cout << gs.npcs.at(npc_id).name << " watches as you plunge your arms into the fountain.\n";
                      gs.npcs[npc_id].suspicion = std::min(100, gs.npcs.at(npc_id).suspicion + 25);
                  }
              }
              std::cout << "You lean over the courtyard fountain and frantically scrub your\n";
              std::cout << "hands and sleeves. The water clouds pink before the flow clears it.\n";
              gs.quest.player_bloodied = false;
              if (witnessed)
              {
                  std::cout << colored("  [!] You are clean, but someone saw you washing blood away!", ansi::BRIGHT_YELLOW) << "\n";
              }
              else
              {
                  std::cout << colored("  [i] The bloodstains are gone. You got lucky, no one was watching.", ansi::GREEN) << "\n";
              }
              advanceTime(gs, 5);
          }}});
}