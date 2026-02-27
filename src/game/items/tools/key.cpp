#include "game.hpp"

void registerKey(GameState &state)
{
    Item item;
    item.id = "key";
    item.name = "Iron Key";
    item.description = "A heavy iron key. What does it open?";
    item.inspect_text =
        "A heavy iron key, cold to the touch, with an ornate ward pattern.\n"
        "It's old, the metal is darkened with age but shows no rust.\n"
        "The bow is stamped with a tiny mortar-and-pestle symbol, suggesting\n"
        "it opens something related to medicine or alchemy. There must be\n"
        "a locked cabinet somewhere in the estate that this belongs to.";
    item.pickup_text = "You pocket the iron key. It clinks against your other belongings.";
    state.items[item.id] = item;
}
