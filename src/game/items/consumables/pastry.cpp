#include "game.hpp"

void registerPastry(GameState &state)
{
    Item item;
    item.id = "pastry";
    item.name = "Cream Pastry";
    item.description = "A delicate pastry on the dining table.";
    item.inspect_text =
        "A flaky pastry filled with vanilla cream and topped with a crystallized\n"
        "violet. Chef Marcel's signature dessert, he makes them fresh each morning\n"
        "for the family. The cream is still cool. The scent alone is heavenly.\n"
        "A small indulgence before the day's schemes begin.";
    item.pickup_text = "You delicately wrap the pastry in a linen napkin.";
    item.edible = true;
    item.hunger_restore = 20;
    item.is_consumable = true;
    state.items[item.id] = item;
}
