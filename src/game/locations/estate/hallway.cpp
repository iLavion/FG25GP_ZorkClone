#include "game.hpp"
#include <iostream>

void registerHallway(GameState &state)
{
    Room r;
    r.id = "hallway";
    r.name = "Hallway";
    r.description = "The second floor landing of the estate. A long corridor lined with oil\n"
                    "paintings of your ancestors. A grand staircase descends to the Grand Hall\n"
                    "below. Your Bedroom is east, the Guest Room is west, and the Sibling's\n"
                    "Room is to the north.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::Down, "grand_hall"},
        {Direction::East, "bedroom"},
        {Direction::West, "guest_room"},
        {Direction::North, "siblings_room"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "hallway",
        {{"Examine the ancestor portraits",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You study the oil paintings lining the corridor. Generations of\n";
              std::cout << "your family stare back, stern dukes, graceful duchesses, and the\n";
              std::cout << "occasional black sheep whose portrait hangs slightly crooked.\n";
              std::cout << "You share your great-grandmother's eyes. She was feared, too.\n";
          }},
         {"Listen at a nearby door",
          nullptr,
          [](GameState &gs)
          {
              bool heard = false;
              for (const auto &room_id : {std::string("bedroom"), std::string("guest_room"),
                                          std::string("siblings_room")})
              {
                  if (!gs.rooms.count(room_id))
                  {
                      continue;
                  }
                  for (const auto &npc_id : gs.rooms.at(room_id).npc_ids)
                  {
                      if (gs.npcs.count(npc_id) && gs.npcs.at(npc_id).alive)
                      {
                          std::cout << "  You hear movement from the "
                                    << gs.rooms.at(room_id).name << ", "
                                    << gs.npcs.at(npc_id).name << " seems to be there.\n";
                          heard = true;
                      }
                  }
              }
              if (!heard)
              {
                  std::cout << "The hallway is quiet. No sounds from the nearby rooms.\n";
              }
              advanceTime(gs, 3);
          }},
         {"Straighten your appearance",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You pause at a wall mirror and adjust your hair and dress.\n";
              std::cout << "A villainess must always look immaculate.\n";
              advanceTime(gs, 1);
          }},
         {"Visit the Guest Room",
          nullptr,
          [](GameState &gs)
          {
              advanceTime(gs, 1);
              gs.player.current_room = "guest_room";
              gs.player.room_state = "standing";
              const auto &room = gs.rooms.at("guest_room");
              std::cout << "\nYou slip through the side door to the Guest Room.\n\n";
              std::cout << "[ " << room.name << " ]  "
                        << timeToString(gs.hour, gs.minute) << "\n";
              std::cout << room.description << "\n";
              if (!room.npc_ids.empty())
              {
                  std::cout << "\nPeople here:";
                  for (const auto &npc_id : room.npc_ids)
                  {
                      if (gs.npcs.count(npc_id))
                          std::cout << "\n  - " << gs.npcs.at(npc_id).name
                                    << " (" << gs.npcs.at(npc_id).title << ")";
                  }
                  std::cout << "\n";
              }
              if (!room.item_ids.empty())
              {
                  std::cout << "\nItems here:";
                  for (const auto &item_id : room.item_ids)
                  {
                      if (gs.items.count(item_id))
                          std::cout << "\n  - " << gs.items.at(item_id).name;
                  }
                  std::cout << "\n";
              }
          }}});
}