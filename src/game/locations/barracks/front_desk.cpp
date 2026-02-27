#include "game.hpp"
#include <iostream>

void registerBarracksFrontDesk(GameState &state)
{
    Room r;
    r.id = "barracks_front_desk";
    r.name = "Barracks Front Desk";
    r.description = "A no-nonsense reception area with stone walls and iron fixtures. A duty\n"
                    "officer sits behind a heavy desk, logging reports. Guards come and go\n"
                    "in purposeful strides. The Records Office is north, Holding Cells west,\n"
                    "Training Yard east. The Diplomat Residence is south.";
    r.area_id = "guard_barracks";
    r.exits = {
        {Direction::North, "barracks_records"},
        {Direction::West, "barracks_cells"},
        {Direction::East, "barracks_training"},
        {Direction::South, "noble_diplomat"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "barracks_front_desk",
        {{"Speak with the duty officer",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "The officer looks up from his ledger.\n";
              std::cout << "  \"Lady Seraphina. What brings the duke's daughter to the\n";
              std::cout << "  barracks? We don't get many noble visitors.\"\n";
              std::cout << "  He seems cooperative but cautious.\n";
              advanceTime(gs, 3);
          }},
         {"Report suspicious activity",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You could file a report about Elena or her associates.\n";
              std::cout << "The guards take noble complaints seriously, but frivolous\n";
              std::cout << "reports damage credibility.\n";
              std::cout << "  [i] This option has consequences. Choose carefully.\n";
              advanceTime(gs, 5);
          }}});
}
