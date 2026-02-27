#include "game.hpp"

void registerWine(GameState &state)
{
    Item item;
    item.id = "wine";
    item.name = "Bottle of Wine";
    item.description = "An expensive vintage from the cellar.";
    item.inspect_text =
        "A bottle of Redmont Reserve, vintage 1187, one of the finest wines\n"
        "in Father's collection. The label is handwritten by the vintner himself.\n"
        "The dark glass conceals liquid the color of rubies. Worth more than\n"
        "most servants earn in a month. Could be drunk for pleasure, offered\n"
        "as a gift to curry favor, or... used to mask the taste of something else.";
    item.pickup_text = "You carefully take the wine bottle. Father would not approve.";
    item.edible = true;
    item.hunger_restore = 5;
    item.is_consumable = true;
    state.items[item.id] = item;
}
