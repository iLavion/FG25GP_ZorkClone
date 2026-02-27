#include "game.hpp"
#include <iostream>

void registerAcademyDuelingGround(GameState &state)
{
    Room r;
    r.id = "academy_dueling_ground";
    r.name = "Dueling Ground";
    r.description = "A sandy arena ringed by wooden fences. Practice swords and shields lean\n"
                    "against racks. Students spar under the watchful eye of a fencing master,\n"
                    "blades clashing and boots scuffing in the dust. The Courtyard is west.";
    r.area_id = "academy";
    r.exits = {{Direction::West, "academy_courtyard"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "academy_dueling_ground",
        {{"Watch the sparring matches",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Two students circle each other, practice swords raised.\n";
              std::cout << "The taller one lunges, parried neatly. The crowd cheers.\n";
              std::cout << "  Dueling is considered a noble art, watching shows interest.\n";
              advanceTime(gs, 10);
          }},
         {"Challenge a rival to a duel",
          [](const GameState &gs)
          {
              return gs.player.energy >= 10;
          },
          [](GameState &gs)
          {
              std::cout << "You step into the ring and take up a practice sword.\n";
              std::cout << "Gasps ripple through the onlookers, the duke's daughter, dueling?\n";
              std::cout << "  The fencing master nods approvingly. \"Form is everything.\"\n";
              gs.player.energy = std::max(0, gs.player.energy - 10);
              std::cout << "  Energy -10\n";
              advanceTime(gs, 15);
          }}});
}