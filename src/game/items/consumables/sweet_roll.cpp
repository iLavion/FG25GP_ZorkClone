#include "game.hpp"

void registerSweetRoll(GameState &state)
{
    Item item;
    item.id = "sweet_roll";
    item.name = "Sweet Roll";
    item.description = "A glazed pastry roll from the bakery, still warm.";
    item.inspect_text =
        "A soft, golden roll drizzled with honey glaze and sprinkled with\n"
        "cinnamon. The baker makes them fresh every morning. The kind of\n"
        "simple pleasure that a duke's daughter rarely indulges in publicly,\n"
        "but secretly adores.";
    item.pickup_text = "You wrap the sweet roll in a napkin and pocket it.";
    item.edible = true;
    item.hunger_restore = 15;
    item.is_consumable = true;
    state.items[item.id] = item;
}
