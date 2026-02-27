#include "game.hpp"

void registerBread(GameState &state)
{
    Item item;
    item.id = "bread";
    item.name = "Fresh Bread";
    item.description = "A warm loaf from the kitchen.";
    item.inspect_text =
        "A golden-crusted loaf, still warm from Chef Marcel's stone oven.\n"
        "The crust crackles when you press it. Steam escapes from within,\n"
        "carrying the scent of rosemary and butter. Simple fare, but the\n"
        "kind that sustains you through a long day of scheming.";
    item.pickup_text = "You wrap the warm bread in a cloth napkin and tuck it away.";
    item.edible = true;
    item.hunger_restore = 25;
    item.is_consumable = true;
    state.items[item.id] = item;
}
