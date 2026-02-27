#include "game.hpp"
#include <iostream>

void registerAcademyArchive(GameState &state)
{
    Room r;
    r.id = "academy_archive";
    r.name = "Archive Room";
    r.description = "Dusty shelves of historical records, old attendance logs, and sealed\n"
                    "documents fill this dimly lit room. A restricted section is roped off\n"
                    "with a faded \"Authorized Personnel Only\" sign. Stairs lead down to\n"
                    "the Lecture Hall and up to the Rooftop Garden.";
    r.area_id = "academy";
    r.exits = {
        {Direction::Down, "academy_lecture_hall"},
        {Direction::Up, "academy_rooftop_garden"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_archive",
        {{"Search the public records",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You leaf through old enrollment records and grade sheets.\n";
              std::cout << "Elena's file shows top marks in every subject. Annoyingly perfect.\n";
              std::cout << "  But you also notice inconsistencies in her family records.\n";
              std::cout << "  Her listed birthplace doesn't match census data.\n";
              advanceTime(gs, 10);
          }},
         {"Attempt to access the restricted section",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You duck under the rope when no one is looking.\n";
              std::cout << "  Sealed documents bearing royal insignia sit on a shelf.\n";
              std::cout << "  One folder is labeled: \"Student Disciplinary Actions, Sealed.\"\n";
              std::cout << "  This could contain blackmail material.\n";
              advanceTime(gs, 8);
          }}});
}