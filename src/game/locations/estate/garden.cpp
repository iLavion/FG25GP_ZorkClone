#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void registerGarden(GameState &state)
{
    Room r;
    r.id = "garden";
    r.name = "Garden";
    r.description = "A sprawling garden with rose bushes, fountains, and hidden pathways.\n"
                    "Gardener Thorne tends the hedges here. Whispers say he knows secrets\n"
                    "about passages beneath the estate. The Courtyard is north. A winding\n"
                    "path downhill leads to the Village.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::North, "courtyard"},
        {Direction::Down, "village_town_square"}};
    r.travel_time = 8;
    state.rooms[r.id] = r;

    state.rooms["garden"].item_ids.push_back("apple");
    state.rooms["garden"].item_ids.push_back("nightshade");

    registerRoomActions(
        "garden",
        {{"Sit by the fountain",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You sit on the stone bench beside the fountain. The sound\n";
              std::cout << "of trickling water is soothing. A passing servant curtsies.\n";
              advanceTime(gs, 10);
          }},
         {"Search the hidden pathways",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You wander through the hedge maze. The pathways twist and\n";
              std::cout << "turn, but you notice worn stones leading toward the cellar\n";
              std::cout << "entrance. Thorne must use these often.\n";
          }},
         {"Wash in the garden fountain",
          [](const GameState &gs)
          { return gs.quest.player_bloodied; },
          [](GameState &gs)
          {
              const Room &room = gs.rooms.at("garden");
              bool witnessed = false;
              for (const auto &npc_id : room.npc_ids)
              {
                  if (gs.npcs.count(npc_id) && gs.npcs.at(npc_id).alive)
                  {
                      witnessed = true;
                      std::cout << gs.npcs.at(npc_id).name << " pauses their work and stares.\n";
                      gs.npcs[npc_id].suspicion = std::min(100, gs.npcs.at(npc_id).suspicion + 15);
                  }
              }
              std::cout << "You kneel by the garden fountain and wash your hands in the\n";
              std::cout << "cool water. The rose petals floating on the surface turn a\n";
              std::cout << "faint shade of red before drifting away.\n";
              gs.quest.player_bloodied = false;
              if (witnessed)
              {
                  std::cout << colored("  [!] Clean, but " + std::to_string(room.npc_ids.size()) + " person(s) may have noticed.", ansi::BRIGHT_YELLOW) << "\n";
              }
              else
              {
                  std::cout << colored("  [i] The blood washes away among the rose petals. No one saw.", ansi::GREEN) << "\n";
              }
              advanceTime(gs, 5);
          }}});
}