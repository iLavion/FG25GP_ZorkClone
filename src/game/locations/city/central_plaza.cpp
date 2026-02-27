#include "game.hpp"
#include <iostream>

void registerCityCentralPlaza(GameState &state)
{
    Room r;
    r.id = "city_central_plaza";
    r.name = "Central Plaza";
    r.description = "A grand plaza paved with sun-bleached stone. A marble fountain sprays\n"
                    "water into the air while town criers shout the day's news. Merchants,\n"
                    "scholars, and pickpockets all mingle here. The Bookshop is north, the\n"
                    "Alleyways south, the General Store east, and the Apothecary west.\n"
                    "A stairway down leads to the Golden Chalice Casino.\n"
                    "A road uphill leads back toward the Village.";
    r.area_id = "city_market_district";
    r.exits = {
        {Direction::North, "city_bookshop"},
        {Direction::South, "city_alleyways"},
        {Direction::East, "city_general_store"},
        {Direction::West, "city_apothecary"},
        {Direction::Up, "village_market"},
        {Direction::Down, "city_casino"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_central_plaza",
        {{"Listen to the town crier",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The town crier bellows from his wooden platform:\n";
              if (gs.heroine_popularity >= 50)
              {
                  std::cout << "  \"Hear ye! The beloved Elena has been named Patron of the\n";
                  std::cout << "  Orphans' Fund! Long may her kindness shine!\"\n";
                  std::cout << "  The crowd cheers. Your stomach turns.\n";
              }
              else
              {
                  std::cout << "  \"New tariffs on eastern goods! The Duke's council convenes!\"\n";
                  std::cout << "  Mundane news. Nothing about Elena, for now.\n";
              }
              advanceTime(gs, 3);
          }},
         {"Toss a coin in the fountain",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You flick a coin into the fountain. The splash draws a few\n";
              std::cout << "admiring glances from commoners, a noblewoman's generosity\n";
              std::cout << "is always noted.\n";
              advanceTime(gs, 2);
          }}});
}