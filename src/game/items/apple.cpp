#include "game.hpp"

void registerApple(GameState &state)
{
    Item item;
    item.id = "apple";
    item.name = "Red Apple";
    item.description = "A crisp apple from the garden.";
    item.inspect_text =
        "A perfectly ripe red apple, plucked from the estate's prized apple tree.\n"
        "Gardener Thorne tends these trees with obsessive care. The skin is\n"
        "glossy and unblemished, the flesh crisp and sweet when bitten.\n"
        "A humble fruit, but in fairy tales, apples can be poison too.";
    item.pickup_text = "You pluck the apple from the branch. Crisp and cool in your hand.";
    item.edible = true;
    item.hunger_restore = 15;
    item.is_consumable = true;
    state.items[item.id] = item;
}
