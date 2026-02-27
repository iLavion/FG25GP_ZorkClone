#include "game.hpp"
#include <iostream>
#include <algorithm>

void registerFathersStudy(GameState &state)
{
    Room r;
    r.id = "fathers_study";
    r.name = "Father's Study";
    r.description = "A dignified room with a massive oak desk, maps on the walls, and the\n"
                    "smell of pipe tobacco. Duke Aldric conducts estate affairs here.\n"
                    "The Library is east.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::East, "library"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["fathers_study"].item_ids.push_back("letter_opener");

    registerRoomActions(
        "fathers_study",
        {{"Peek at Father's documents",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("fathers_study");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(), "duke_aldric") == room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "You quickly scan the papers on Father's desk...\n";
              std::cout << "A letter from the Royal Court mentions Elena by name:\n";
              std::cout << "  \"...the Prince requests that Elena be given every courtesy.\n";
              std::cout << "   Her presence at Court is anticipated for the season's end.\"\n\n";
              std::cout << "So the Crown is behind her rise. This is worse than you thought.\n";
              gs.quest.elena_letters_found = true;
              gs.player.suspicion += 5;
              std::cout << "  Suspicion +5 (snooping in the Duke's study)\n";
              advanceTime(gs, 5);
          }},
         {"Examine the estate maps",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "The walls are covered in detailed maps of the estate grounds,\n";
              std::cout << "surrounding territories, and trade routes. Red pins mark key\n";
              std::cout << "locations. You notice a faded line that might indicate a\n";
              std::cout << "passage from the cellar to beyond the estate walls.\n";
          }},
         {"Request an audience with Father",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("fathers_study");
              return std::find(room.npc_ids.begin(), room.npc_ids.end(),
                               "duke_aldric") != room.npc_ids.end();
          },
          [](GameState &gs)
          {
              std::cout << "\"Father, may I have a word?\"\n";
              std::cout << "  [i] Use TALK DUKE to have a full conversation.\n";
          }}});
}
