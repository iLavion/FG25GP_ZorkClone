#include "game.hpp"
#include <iostream>

void registerDocksHarborMaster(GameState &state)
{
    Room r;
    r.id = "docks_harbor_master";
    r.name = "Harbor Master Office";
    r.description = "A cluttered office overlooking the harbor through a wide window. Shipping\n"
                    "manifests, ledgers, and nautical charts cover every surface. The harbor\n"
                    "master, a meticulous man with ink-stained fingers, manages all port\n"
                    "traffic. The Main Pier is south, the Fish Market west.";
    r.area_id = "docks";
    r.exits = {
        {Direction::South, "docks_main_pier"},
        {Direction::West, "docks_fish_market"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "docks_harbor_master",
        {{"Review shipping manifests",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You ask to see recent manifests. The harbor master obliges,\n";
              std::cout << "happy to assist the duke's daughter.\n";
              std::cout << "  One entry catches your eye: a shipment of \"herbal remedies\"\n";
              std::cout << "  addressed to Elena, arriving from an eastern port.\n";
              advanceTime(gs, 8);
          }},
         {"Inquire about suspicious vessels",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The harbor master strokes his chin thoughtfully.\n";
              std::cout << "  \"There's been a privateer lingering in the harbor. No cargo\n";
              std::cout << "  declared, crew keeps to themselves. Registered under a false\n";
              std::cout << "  name, I suspect.\"\n";
              advanceTime(gs, 5);
          }}});
}
