#include "game.hpp"
#include <iostream>

void registerAcademyCourtyard(GameState &state)
{
    Room r;
    r.id = "academy_courtyard";
    r.name = "Academy Courtyard";
    r.description = "A wide courtyard where students gather between classes. A bronze statue\n"
                    "of the academy's founder stands at the center. Young nobles chat in\n"
                    "clusters while commoner students keep a respectful distance. The Main\n"
                    "Gate is south, the Lecture Hall north, the Dueling Ground east, and\n"
                    "the Dormitory west.";
    r.area_id = "academy";
    r.exits = {
        {Direction::South, "academy_main_gate"},
        {Direction::North, "academy_lecture_hall"},
        {Direction::East, "academy_dueling_ground"},
        {Direction::West, "academy_dormitory"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_courtyard",
        {{"Observe the students",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You watch the students from a bench. Noble sons and daughters\n";
              std::cout << "form their usual cliques. A group of commoner students huddle\n";
              std::cout << "near the fountain, talking excitedly about their studies.\n";
              if (gs.heroine_popularity >= 20)
              {
                  std::cout << "  Several students mention Elena by name, with admiration.\n";
              }
              advanceTime(gs, 5);
          }},
         {"Make your presence known",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You walk through the courtyard with deliberate poise. Students\n";
              std::cout << "step aside and bow. The duke's daughter commands respect here.\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 2);
              std::cout << "  Reputation +2\n";
              advanceTime(gs, 3);
          }}});
}
