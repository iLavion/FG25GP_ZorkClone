#include "game.hpp"
#include <iostream>

void registerBarracksTraining(GameState &state)
{
    Room r;
    r.id = "barracks_training";
    r.name = "Training Yard";
    r.description = "An open yard where guards spar with wooden swords and practice\n"
                    "formations. Straw dummies are riddled with arrow holes. The clash of\n"
                    "wood and shouted commands fill the air. The Front Desk is west, the\n"
                    "Armory south.";
    r.area_id = "guard_barracks";
    r.exits = {
        {Direction::West, "barracks_front_desk"},
        {Direction::South, "barracks_armory"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_training",
        {{"Watch the guards train",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You observe the guards at practice. Their discipline is\n";
              std::cout << "impressive. Captain Roderick's training shows.\n";
              std::cout << "  A few guards notice you watching and stand up straighter.\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 1);
              std::cout << "  Reputation +1 (noble presence inspires the troops)\n";
              advanceTime(gs, 10);
          }}});
}
