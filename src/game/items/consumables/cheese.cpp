#include "game.hpp"

void registerCheese(GameState &state)
{
    Item item;
    item.id = "cheese";
    item.name = "Aged Cheese";
    item.description = "A wedge of sharp aged cheese from the pantry.";
    item.inspect_text =
        "A firm wedge of cave-aged cheese wrapped in waxed cloth. The rind\n"
        "is dark and cracked, but the interior is pale gold with a sharp,\n"
        "nutty aroma. Chef Marcel keeps this for the family's private use.\n"
        "It pairs well with bread and a bit of wine.";
    item.pickup_text = "You wrap the cheese wedge in its cloth and tuck it away.";
    item.edible = true;
    item.hunger_restore = 20;
    item.is_consumable = true;
    state.items[item.id] = item;
}
