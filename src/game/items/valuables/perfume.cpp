#include "game.hpp"

void registerPerfume(GameState &state)
{
    Item item;
    item.id = "perfume";
    item.name = "Lavender Perfume";
    item.description = "Expensive perfume. Could be a gift... or a tool.";
    item.inspect_text =
        "A crystal flacon of lavender perfume, imported from the southern provinces.\n"
        "The stopper is shaped like a tiny rose. When opened, the scent is intoxicating,\n"
        "floral, with undertones of honey and something subtly hypnotic.\n"
        "A single dab can make anyone more receptive to your words.\n"
        "Your mother wore this scent. Now it is yours to wield.";
    item.pickup_text = "You slip the perfume flacon into your pocket. It feels like a weapon.";
    state.items[item.id] = item;
}
