#include "game.hpp"

void registerSleepingDraught(GameState &state)
{
    Item item;
    item.id = "sleeping_draught";
    item.name = "Sleeping Draught";
    item.description = "A powerful sedative. A few drops will knock someone out for hours.";
    item.inspect_text =
        "A small bottle of milky-white liquid with a faintly sweet aroma.\n"
        "The label reads \"Somnium Concentrate, FOR MEDICINAL USE ONLY.\"\n"
        "Three drops in a drink causes deep, dreamless sleep for six to eight\n"
        "hours. The entire bottle could put someone under for days.\n"
        "Found in the kitchen's locked medicinal cabinet. Someone knew\n"
        "exactly what they were storing here.";
    item.pickup_text = "You take the sleeping draught. A tool of subtlety, not violence.";
    item.is_suspicious = true;
    item.is_consumable = true;
    state.items[item.id] = item;
}
