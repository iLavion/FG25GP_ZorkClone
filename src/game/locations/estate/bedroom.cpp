#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void registerBedroom(GameState &state)
{
    Room r;
    r.id = "bedroom";
    r.name = "Villainess's Bedroom";
    r.description = "Your lavish private chambers on the second floor east wing. A canopy bed\n"
                    "draped in crimson silk dominates the room. A vanity mirror, wardrobe, and\n"
                    "a writing desk sit nearby. The Hallway is west, and your Balcony is east.";
    r.area_id = "ducal_estate";
    r.exits = {{Direction::West, "hallway"}, {Direction::East, "balcony"}};
    r.allows_sleep = true;
    r.travel_time = 1;

    r.state_descriptions["in_bed"] =
        "You lie in your lavish canopy bed draped in crimson silk.\n"
        "The morning sun filters through the curtains, casting long golden\n"
        "shadows across the marble floor. A vanity mirror, wardrobe, and\n"
        "writing desk sit nearby. The Hallway is west, your Balcony east.";
    r.state_descriptions["sitting_desk"] =
        "You are sitting at your writing desk. Quill, ink, and fine stationery\n"
        "await your hand.";

    state.rooms[r.id] = r;

    state.rooms["bedroom"].item_ids.push_back("perfume");
    state.rooms["bedroom"].item_ids.push_back("gold_ring");
    state.rooms["bedroom"].item_ids.push_back("writing_desk_paper");

    registerRoomActions(
        "bedroom",
        {{"Get out of bed",
          [](const GameState &gs)
          { return gs.player.room_state == "in_bed"; },
          [](GameState &gs)
          {
              gs.player.room_state = "standing";
              std::cout << "You throw back the silk covers and rise from the bed.\n";
              std::cout << "The cool morning air greets you as your feet touch the marble floor.\n";
          }},
         {"Get in bed",
          [](const GameState &gs)
          { return gs.player.room_state == "standing"; },
          [](GameState &gs)
          {
              gs.player.room_state = "in_bed";
              std::cout << "You pull back the covers and slip into bed.\n";
          }},
         {"Fall back asleep",
          [](const GameState &gs)
          { return gs.player.room_state == "in_bed"; },
          [](GameState &gs)
          {
              print_narrative("You pull the covers over your head and drift back to sleep...", 500);
              print_narrative("...", 800);
              gs.player.energy = std::min(100, gs.player.energy + 20);
              gs.player.turns_without_sleeping = 0;
              advanceTime(gs, 120);
              std::cout << "You stir awake again. It is now "
                        << timeToString(gs.hour, gs.minute) << ".\n\n";
              std::cout << colored("  Energy: " + std::to_string(gs.player.energy) + "/100", ansi::GREEN) << "\n";
              gs.heroine_popularity = std::min(100, gs.heroine_popularity + 1);
              std::cout << colored("  [i] Time has passed. Elena's influence may have grown.", ansi::CYAN) << "\n";
          }},
         {"Call for the attendants",
          [](const GameState &gs)
          { return gs.player.room_state == "in_bed"; },
          [](GameState &gs)
          {
              print_pause(colored("\"Clara!\"", ansi::BRIGHT_GREEN) + " you call out from bed.\n\n", 500);
              advanceTime(gs, 5);

              if (gs.npcs.count("maid_clara") && gs.npcs.at("maid_clara").alive)
              {
                  NPC &clara = gs.npcs.at("maid_clara");
                  if (gs.rooms.count(clara.current_room))
                  {
                      auto &old_ids = gs.rooms[clara.current_room].npc_ids;
                      old_ids.erase(
                          std::remove(old_ids.begin(), old_ids.end(), std::string("maid_clara")),
                          old_ids.end());
                  }
                  clara.current_room = "bedroom";
                  clara.pinned_until = (gs.hour * 60 + gs.minute) + 60;
                  auto &bed_npcs = gs.rooms["bedroom"].npc_ids;
                  if (std::find(bed_npcs.begin(), bed_npcs.end(), "maid_clara") == bed_npcs.end())
                  {
                      bed_npcs.push_back("maid_clara");
                  }

                  gs.player.room_state = "standing";
                  print_narrative("Shortly, Clara hurries in with a curtsy.", 400);
                  std::cout << colored("Clara: ", ansi::YELLOW) << "\"Good morning, my lady! What do you need?\"\n";
                  delay_ms(300);
                  print_narrative("You rise from bed as she enters.");
                  std::cout << "\n";
                  std::cout << colored("  [i] Clara is now here. Use TALK CLARA to speak with her.", ansi::CYAN) << "\n\n";
              }
              else
              {
                  std::cout << "No one answers. The attendants seem to be unavailable.\n";
              }
          }},
         {"Examine the vanity mirror",
          [](const GameState &gs)
          {
              return gs.player.room_state == "standing" &&
                     gs.player.current_room == "bedroom";
          },
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You gaze into the ornate vanity mirror. " << gs.player.name << " stares back,\n";
              std::cout << "beautiful, cunning, and determined. Today will be different.\n";
          }},
         {"Sit at the writing desk",
          [](const GameState &gs)
          {
              return gs.player.room_state == "standing" &&
                     gs.player.current_room == "bedroom";
          },
          [](GameState &gs)
          {
              gs.player.room_state = "sitting_desk";
              std::cout << "You settle into the chair at your writing desk. Quill, ink, and\n";
              std::cout << "fine stationery await your hand.\n\n";
              std::cout << colored("  [i] Use the WRITE command to pen a letter.", ansi::CYAN) << "\n\n";
              advanceTime(gs, 2);
          }},
         {"Read a book",
          [](const GameState &gs)
          { return gs.player.room_state == "sitting_desk"; },
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You pick up a book of poetry and lose yourself in verse for a while.\n";
              advanceTime(gs, 30);
          }},
         {"Get up from the chair",
          [](const GameState &gs)
          { return gs.player.room_state == "sitting_desk"; },
          [](GameState &gs)
          {
              gs.player.room_state = "standing";
              std::cout << "You rise from the chair, ready for your next move.\n";
          }}});
}
