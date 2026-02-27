#include "game.hpp"
#include <iostream>

void registerBarracksArmory(GameState &state)
{
    Room r;
    r.id = "barracks_armory";
    r.name = "Armory";
    r.description = "Racks of swords, pikes, crossbows, and shields fill this secured room.\n"
                    "A weapons master maintains inventory with obsessive precision. Confiscated\n"
                    "items from criminals are stored in a locked cage at the back.\n"
                    "The Training Yard is north.";
    r.area_id = "guard_barracks";
    r.exits = {{Direction::North, "barracks_training"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_armory",
        {{"Browse the confiscated items",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Through the cage bars, you see an assortment of seized goods:\n";
              std::cout << "  daggers, lockpicks, vials of unknown substances, and a stack\n";
              std::cout << "  of forged documents.\n";
              std::cout << "  One document bears Elena's name. Interesting.\n";
              advanceTime(gs, 5);
          }}});
}