#include "game.hpp"
#include <iostream>

void registerNobleRivalGarden(GameState &state)
{
    Room r;
    r.id = "noble_rival_garden";
    r.name = "Rival Mansion Garden";
    r.description = "A manicured garden with sculpted hedges and a marble gazebo. Hushed\n"
                    "conversations take place beneath the arbor. This is where the Whitmores\n"
                    "conduct their private dealings, away from prying eyes. The Rival\n"
                    "Mansion Gate is south.";
    r.area_id = "noble_quarter";
    r.exits = {{Direction::South, "noble_rival_gate"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_rival_garden",
        {{"Hide and eavesdrop",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You duck behind a hedge and listen. Two voices drift from the\n";
              std::cout << "gazebo, hushed and urgent.\n";
              std::cout << "  \"...if we support Elena's bid at court, we weaken the Duke.\"\n";
              std::cout << "  \"Agreed. She's our best weapon against that family.\"\n";
              std::cout << "  So the Whitmores are backing Elena. This changes things.\n";
              advanceTime(gs, 10);
          }},
         {"Search for evidence",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You carefully search the gazebo when no one is near.\n";
              std::cout << "Under a loose stone, a folded letter with a broken seal.\n";
              std::cout << "  It details a financial arrangement between the Whitmores\n";
              std::cout << "  and Elena's benefactors. Proof of conspiracy.\n";
              advanceTime(gs, 8);
          }}});
}