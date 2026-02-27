#include "game.hpp"
#include <iostream>

void registerGrandHall(GameState &state)
{
    Room r;
    r.id = "grand_hall";
    r.name = "Grand Hall";
    r.description = "The heart of the estate. Chandeliers glitter overhead and a marble floor\n"
                    "stretches wide. A grand staircase leads up to the second floor Hallway.\n"
                    "The Dining Room is east, the Courtyard is south, and the Library is west.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::Up, "hallway"},
        {Direction::East, "dining_room"},
        {Direction::South, "courtyard"},
        {Direction::West, "library"}};
    r.travel_time = 4;
    state.rooms[r.id] = r;

    state.rooms["grand_hall"].item_ids.push_back("silver_brooch");

    registerRoomActions(
        "grand_hall",
        {{"Admire the chandelier",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You gaze up at the crystal chandelier, a three-hundred-year-old\n";
              std::cout << "heirloom that casts rainbow prisms across the marble floor.\n";
              std::cout << "A symbol of your family's enduring power.\n";
              std::cout << "  The sight strengthens your resolve.\n";
          }},
         {"Eavesdrop on conversations",
          [](const GameState &gs)
          {
              const auto &room = gs.rooms.at("grand_hall");
              return room.npc_ids.size() >= 2;
          },
          [](GameState &gs)
          {
              std::cout << "You linger near a pillar and catch snippets of conversation...\n";
              const auto &room = gs.rooms.at("grand_hall");
              bool juicy = false;
              for (const auto &npc_id : room.npc_ids)
              {
                  if (npc_id == "elena" && gs.npcs.count("elena") && gs.npcs.at("elena").alive)
                  {
                      std::cout << "  Elena is speaking in hushed tones about the Prince.\n";
                      std::cout << "  \"...his letters grow more insistent. I must be careful...\"\n";
                      gs.quest.overheard_secret = true;
                      juicy = true;
                  }
              }
              if (!juicy)
              {
                  std::cout << "  The staff discusses mundane estate matters. Nothing useful.\n";
              }
              advanceTime(gs, 5);
          }},
         {"Greet the staff",
          [](const GameState &gs)
          {
              return !gs.rooms.at("grand_hall").npc_ids.empty();
          },
          [](GameState &gs)
          {
              std::cout << "You nod graciously to those present. A proper lady acknowledges\n";
              std::cout << "her household. They bow or curtsy in response.\n";
          }}});
}