#include "game.hpp"
#include <iostream>

void registerDocksMainPier(GameState &state)
{
    Room r;
    r.id = "docks_main_pier";
    r.name = "Main Pier";
    r.description = "A long wooden pier stretching into the harbor. Salt spray mists the air\n"
                    "as merchant ships creak at their moorings. Dockworkers haul crates while\n"
                    "sailors call out in rough voices. The Warehouses are south, a Ship is\n"
                    "docked east, the Harbor Master's Office north. The City Alleyways are west.";
    r.area_id = "docks";
    r.exits = {
        {Direction::South, "docks_warehouses"},
        {Direction::East, "docks_ship_deck"},
        {Direction::North, "docks_harbor_master"},
        {Direction::West, "city_alleyways"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_main_pier",
        {{"Watch the ships come and go",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lean against a post and watch the harbor. Merchant vessels,\n";
              std::cout << "fishing boats, and one sleek privateer at anchor. The sea offers\n";
              std::cout << "freedom, but also danger.\n";
              advanceTime(gs, 5);
          }},
         {"Ask the dockworkers about trade",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "A burly dockworker wipes sweat from his brow.\n";
              std::cout << "  \"Trade's been odd lately. Someone's been buying up medical\n";
              std::cout << "  supplies in bulk. Shipping them inland. Don't know who.\"\n";
              advanceTime(gs, 5);
          }}});
}
