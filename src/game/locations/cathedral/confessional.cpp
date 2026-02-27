#include "game.hpp"
#include <iostream>

void registerCathedralConfessional(GameState &state)
{
    Room r;
    r.id = "cathedral_confessional";
    r.name = "Confessional";
    r.description = "A small wooden booth divided by a latticed screen. Here, sins are spoken\n"
                    "and absolved, or so they say. The privacy makes it useful for more than\n"
                    "just spiritual matters. The Nave is west.";
    r.area_id = "cathedral";
    r.exits = {{Direction::West, "cathedral_nave"}};
    r.travel_time = 1;
    state.rooms[r.id] = r;

    registerRoomActions(
        "cathedral_confessional",
        {{"Confess your sins",
          [](const GameState &gs)
          {
              return gs.quest.action_cooldowns.count("confess_sins") == 0;
          },
          [](GameState &gs)
          {
              std::cout << "You step into the booth and speak to the shadow behind the screen.\n";
              std::cout << "  \"Forgive me, for I have plotted against another.\"\n";
              std::cout << "  \"The heavens hear your confession, child. Go and sin no more.\"\n";
              std::cout << "  You feel a small weight lift from your conscience.\n";
              gs.quest.action_cooldowns["confess_sins"] = 1;
              advanceTime(gs, 10);
          }},
         {"Eavesdrop on the next confession",
          [](const GameState &gs)
          {
              return gs.quest.action_cooldowns.count("confess_eavesdrop") == 0;
          },
          [](GameState &gs)
          {
              std::cout << "You linger inside the booth, hidden in the dark. After a while,\n";
              std::cout << "someone else enters the other side.\n";
              std::cout << "  \"...I've been passing information to the heroine's allies...\"\n";
              std::cout << "  Interesting. Someone in the church is working for Elena.\n";
              gs.quest.action_cooldowns["confess_eavesdrop"] = 1;
              advanceTime(gs, 15);
          }}});
}