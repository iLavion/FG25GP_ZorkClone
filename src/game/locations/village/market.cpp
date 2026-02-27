#include "game.hpp"
#include <iostream>

void registerVillageMarket(GameState &state)
{
    Room r;
    r.id = "village_market";
    r.name = "Small Market";
    r.description = "A row of wooden stalls draped in patched awnings. Farmers sell fresh\n"
                    "produce, a fishmonger shouts prices, and the aroma of baked bread mixes\n"
                    "with the smell of livestock. The Town Square is north, the Village Well\n"
                    "is east, and a road south slopes down toward the City Market District.";
    r.area_id = "village_suburb";
    r.exits = {
        {Direction::North, "village_town_square"},
        {Direction::East, "village_well"},
        {Direction::Down, "city_central_plaza"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["village_market"].item_ids.push_back("fresh_bread");

    registerRoomActions(
        "village_market",
        {{"Browse the food stalls",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You wander past crates of apples, wheels of cheese, and baskets\n";
              std::cout << "of warm bread. The merchants bow when they recognize your station.\n";
              std::cout << "  \"Anything for the duke's daughter, my lady!\"\n";
              advanceTime(gs, 3);
          }},
         {"Inquire about supply shipments",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "A merchant leans in, lowering his voice.\n";
              std::cout << "  \"Shipments from the docks have been... irregular lately.\"\n";
              std::cout << "  \"Someone's buying up all the good stock before it reaches us.\"\n";
              advanceTime(gs, 5);
          }}});
}
