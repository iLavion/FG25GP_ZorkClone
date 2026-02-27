#include "game.hpp"

void registerGoldRing(GameState &state)
{
    Item item;
    item.id = "gold_ring";
    item.name = "Gold Ring";
    item.description = "A valuable gold ring. Good for bribes.";
    item.inspect_text =
        "A heavy gold signet ring bearing the crest of a minor noble house, not\n"
        "your family's. Perhaps it belonged to a guest who stayed long ago.\n"
        "The gold is pure and warm to the touch. Worth a small fortune to\n"
        "the right person, or a powerful bargaining chip in the right conversation.";
    item.pickup_text = "You pocket the gold ring. Its weight is reassuring.";
    state.items[item.id] = item;
}
