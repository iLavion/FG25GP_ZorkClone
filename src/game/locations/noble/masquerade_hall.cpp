#include "game.hpp"
#include <iostream>

void registerNobleMasqueradeHall(GameState &state)
{
    Room r;
    r.id = "noble_masquerade_hall";
    r.name = "Masquerade Hall";
    r.description = "A grand ballroom reserved for masked events. Ornate chandeliers hang\n"
                    "from a painted ceiling depicting celestial scenes. Masks of every style\n"
                    "line display cases near the entrance. Here, identity is fluid and\n"
                    "secrets flow freely. Carriage Lane is north.";
    r.area_id = "noble_quarter";
    r.exits = {{Direction::North, "noble_carriage_lane"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_masquerade_hall",
        {{"Try on a mask",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You select an elegant silver mask with feathered edges.\n";
              std::cout << "Behind it, you could be anyone, a merchant's wife, a foreign\n";
              std::cout << "dignitary, or nobody at all. Freedom in anonymity.\n";
              advanceTime(gs, 3);
          }},
         {"Explore the empty ballroom",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Your footsteps echo across the polished floor. The hall is\n";
              std::cout << "between events, quiet and expectant. You notice a servants'\n";
              std::cout << "passage hidden behind a heavy curtain near the orchestra pit.\n";
              advanceTime(gs, 5);
          }}});
}
