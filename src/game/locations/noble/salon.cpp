#include "game.hpp"
#include <iostream>

void registerNobleSalon(GameState &state)
{
    Room r;
    r.id = "noble_salon";
    r.name = "Salon House";
    r.description = "An opulent drawing room where noble ladies gather for tea and scheming.\n"
                    "Velvet settees, gilded mirrors, and a harpist in the corner create an\n"
                    "atmosphere of refined elegance. Here, gossip is currency and alliances\n"
                    "are traded over porcelain cups. Carriage Lane is south.";
    r.area_id = "noble_quarter";
    r.exits = {{Direction::South, "noble_carriage_lane"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "noble_salon",
        {{"Join the tea circle",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You settle into a velvet chair and accept a cup of jasmine tea.\n";
              std::cout << "The ladies eye you with interest. The duke's daughter is always\n";
              std::cout << "welcome, and always watched.\n";
              std::cout << "  \"Have you heard about Elena's latest kindness?\" one asks sweetly.\n";
              std::cout << "  The room falls silent, waiting for your reaction.\n";
              advanceTime(gs, 10);
          }},
         {"Spread rumors about Elena",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lean in with a conspiratorial whisper.\n";
              std::cout << "  \"I've heard the most troubling things about Elena's past...\"\n";
              std::cout << "  The ladies lean closer, hungry for scandal.\n";
              gs.heroine_popularity = std::max(0, gs.heroine_popularity - 2);
              gs.quest.rumors_spread = true;
              std::cout << "  Elena Popularity -2\n";
              advanceTime(gs, 15);
          }}});
}