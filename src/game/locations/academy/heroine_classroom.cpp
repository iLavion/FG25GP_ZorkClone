#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerAcademyHeroineClassroom(GameState &state)
{
    Room r;
    r.id = "academy_heroine_classroom";
    r.name = "Heroine's Classroom";
    r.description = "A small, well-kept classroom with desks arranged in neat rows. Elena's\n"
                    "desk is near the window, covered with orderly notes and a small vase\n"
                    "of wildflowers. Her classmates speak of her with undisguised admiration.\n"
                    "The Lecture Hall is west.";
    r.area_id = "academy";
    r.exits = {{Direction::West, "academy_lecture_hall"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_heroine_classroom",
        {{"Examine Elena's desk",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You approach the desk by the window. Neat handwriting fills\n";
              std::cout << "her notebooks, philosophy, ethics, even political theory.\n";
              std::cout << "  A folded note peeks from between pages.\n";
              std::cout << "  " << colored("[i] Use PICKUP to take the note if you dare.", ansi::CYAN) << "\n";
              advanceTime(gs, 3);
          }},
         {"Sabotage her study materials",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You subtly rearrange her notes out of order and smudge a\n";
              std::cout << "key diagram. Small acts of sabotage, but they add up.\n";
              gs.heroine_popularity = std::max(0, gs.heroine_popularity - 1);
              std::cout << "  Elena Popularity -1\n";
              advanceTime(gs, 5);
          }}});
}