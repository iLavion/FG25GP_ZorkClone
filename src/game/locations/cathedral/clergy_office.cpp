#include "game.hpp"
#include <iostream>

void registerCathedralClergyOffice(GameState &state)
{
    Room r;
    r.id = "cathedral_clergy_office";
    r.name = "Clergy Office";
    r.description = "A wood-paneled office smelling of old parchment and beeswax. A bishop's\n"
                    "desk is piled with church records, ledgers, and sealed correspondence.\n"
                    "A painting of the first High Priest watches from above. The Nave is east.";
    r.area_id = "cathedral";
    r.exits = {{Direction::East, "cathedral_nave"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "cathedral_clergy_office",
        {{"Examine the church records",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You flip through the leather-bound ledgers. Donations, baptisms,\n";
              std::cout << "marriages, and funerals for every family in the region.\n";
              std::cout << "  Elena's baptismal record is missing. Curious, for someone\n";
              std::cout << "  who claims to be from this parish.\n";
              advanceTime(gs, 8);
          }},
         {"Offer a generous donation",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You leave a pouch of gold coins on the desk with a note:\n";
              std::cout << "  \"For the cathedral's good works, from the Duke's household.\"\n";
              advanceTime(gs, 3);
          }}});
}