#include "game.hpp"
#include <iostream>

void registerCityBookshop(GameState &state)
{
    Room r;
    r.id = "city_bookshop";
    r.name = "Bookshop";
    r.description = "Towering bookshelves lean at precarious angles, crammed with leather-bound\n"
                    "volumes. Dust motes float in the light from a single high window. A\n"
                    "scholarly owner sits behind stacks of unsorted manuscripts. The Central\n"
                    "Plaza is south, the Courier Office east, and the Bakery north.";
    r.area_id = "city_market_district";
    r.exits = {
        {Direction::South, "city_central_plaza"},
        {Direction::East, "city_courier"},
        {Direction::North, "city_bakery"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_bookshop",
        {{"Search for useful texts",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You browse the shelves, running a gloved finger along the spines.\n";
              std::cout << "  \"The Art of Court Intrigue,\" \"Poisons of the Eastern Realms,\"\n";
              std::cout << "  \"A History of Fallen Houses.\" All potentially useful.\n";
              advanceTime(gs, 5);
          }},
         {"Ask about Elena's reading habits",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The scholar adjusts his spectacles.\n";
              std::cout << "  \"The young lady Elena? Oh, she comes often. Reads philosophy,\n";
              std::cout << "  ethics, treatises on governance. Ambitious taste for a commoner.\"\n";
              std::cout << "  Interesting. She's preparing herself for something.\n";
              advanceTime(gs, 5);
          }}});
}
