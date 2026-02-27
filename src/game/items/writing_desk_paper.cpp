#include "game.hpp"

void registerWritingDeskPaper(GameState &state)
{
    Item item;
    item.id = "writing_desk_paper";
    item.name = "Fine Stationery";
    item.description = "Elegant paper and quill on your writing desk. Perfect for formal letters.";
    item.inspect_text =
        "Sheets of cream-colored vellum embossed with the ducal family's watermark.\n"
        "A silver-nibbed quill rests beside a pot of midnight-blue ink.\n"
        "The stationery carries faint traces of your perfume from years of\n"
        "correspondence. Every letter you write on this paper carries authority.";
    item.pickup_text = "You gather the stationery and writing supplies.";
    item.readable = false;
    state.items[item.id] = item;
}
