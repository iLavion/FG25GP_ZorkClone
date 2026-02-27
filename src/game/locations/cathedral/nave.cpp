#include "game.hpp"
#include <iostream>

void registerCathedralNave(GameState &state)
{
    Room r;
    r.id = "cathedral_nave";
    r.name = "Cathedral Nave";
    r.description = "Towering stone columns support a vaulted ceiling lost in shadow. Stained\n"
                    "glass windows cast pools of colored light across the worn pews. The scent\n"
                    "of incense and old stone fills the air. A priest tends the candles near\n"
                    "the altar. The Confessional is east, the Side Chapel north, the Clergy\n"
                    "Office west, and stairs descend to the Crypt. The Village Chapel is south.";
    r.area_id = "cathedral";
    r.exits = {
        {Direction::East, "cathedral_confessional"},
        {Direction::North, "cathedral_side_chapel"},
        {Direction::West, "cathedral_clergy_office"},
        {Direction::Down, "cathedral_crypt"},
        {Direction::South, "village_chapel"}};
    r.travel_time = 3;
    state.rooms[r.id] = r;

    registerRoomActions(
        "cathedral_nave",
        {{"Pray at the altar",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You kneel before the grand altar. The flickering candlelight\n";
              std::cout << "dances across golden icons. In this sacred silence, the weight\n";
              std::cout << "of your schemes feels heavier.\n";
              gs.player.suspicion = std::max(0, gs.player.suspicion - 3);
              std::cout << "  Suspicion -3 (appearing devout)\n";
              advanceTime(gs, 8);
          }},
         {"Admire the stained glass",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "The windows depict scenes of saints and sinners. One panel shows\n";
              std::cout << "a noblewoman casting down a false prophet. You find it inspiring.\n";
          }}});
}
