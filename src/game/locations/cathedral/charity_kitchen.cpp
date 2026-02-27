#include "game.hpp"
#include <iostream>

void registerCathedralCharityKitchen(GameState &state)
{
    Room r;
    r.id = "cathedral_charity_kitchen";
    r.name = "Charity Kitchen";
    r.description = "A steamy kitchen where church volunteers ladle soup into wooden bowls\n"
                    "for the poor. The aroma of barley stew fills the air. Commoners line\n"
                    "up at a serving counter, grateful and humble. The Side Chapel is east.";
    r.area_id = "cathedral";
    r.exits = {{Direction::East, "cathedral_side_chapel"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "cathedral_charity_kitchen",
        {{"Help serve the poor",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You take up a ladle and serve soup to the line of commoners.\n";
              std::cout << "Their grateful faces soften your heart, if only briefly.\n";
              std::cout << "  Word of your charity will spread through the village.\n";
              gs.player.reputation = std::min(100, gs.player.reputation + 4);
              gs.heroine_popularity = std::max(0, gs.heroine_popularity - 1);
              std::cout << "  Reputation +4, Elena Popularity -1\n";
              advanceTime(gs, 20);
          }},
         {"Gather information from commoners",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "While serving, you listen to the chatter of the poor.\n";
              std::cout << "  \"Elena gave us blankets last week. Such a kind soul.\"\n";
              std::cout << "  \"I heard she's looking for her real parents, though.\"\n";
              std::cout << "  Real parents? So the orphan story might be a fabrication.\n";
              advanceTime(gs, 10);
          }}});
}
