#include "game.hpp"

void registerSilverBrooch(GameState &state)
{
    Item item;
    item.id = "silver_brooch";
    item.name = "Silver Brooch";
    item.description = "An elegant brooch. Worth a decent sum.";
    item.inspect_text =
        "A silver brooch shaped like a crescent moon, set with a tiny sapphire.\n"
        "Fine craftsmanship, possibly dwarven-made, from the northern mines.\n"
        "It catches the light beautifully. Someone left it here after the last\n"
        "grand ball. Could serve as a gift, a bribe, or simply a treasure to keep.";
    item.pickup_text = "You pin the silver brooch inside your cloak. A useful trinket.";
    state.items[item.id] = item;
}
