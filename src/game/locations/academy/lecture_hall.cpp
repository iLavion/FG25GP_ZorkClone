#include "game.hpp"
#include <iostream>

void registerAcademyLectureHall(GameState &state)
{
    Room r;
    r.id = "academy_lecture_hall";
    r.name = "Lecture Hall";
    r.description = "Tiered wooden benches face a podium where a professor lectures on\n"
                    "history and statecraft. Maps and diagrams cover the walls. Students\n"
                    "scribble notes with feather quills. The Courtyard is south, the\n"
                    "Heroine's Classroom is east, and stairs lead up to the Archive.";
    r.area_id = "academy";
    r.exits = {
        {Direction::South, "academy_courtyard"},
        {Direction::East, "academy_heroine_classroom"},
        {Direction::Up, "academy_archive"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_lecture_hall",
        {{"Attend the lecture",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You take a seat in the back row. The professor drones on about\n";
              std::cout << "the fall of the Aldoran Dynasty, a cautionary tale about noble\n";
              std::cout << "families who lost their power to popular uprisings.\n";
              std::cout << "  The parallels to your own situation are not lost on you.\n";
              advanceTime(gs, 15);
          }},
         {"Speak with the professor afterward",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The professor recognizes you at once.\n";
              std::cout << "  \"Lady Seraphina! Your family's history is rich with lessons.\"\n";
              std::cout << "  \"Knowledge is the sharpest weapon a noblewoman can wield.\"\n";
              advanceTime(gs, 5);
          }}});
}