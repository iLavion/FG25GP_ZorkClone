#include "game.hpp"

void registerSealedScroll(GameState &state)
{
    Item item;
    item.id = "sealed_scroll";
    item.name = "Sealed Scroll";
    item.description = "An ancient scroll sealed with crumbling wax, found among the dead.";
    item.inspect_text =
        "A tightly rolled piece of vellum bound with a ribbon of faded crimson.\n"
        "The wax seal bears an emblem you don't recognize, something older than\n"
        "the cathedral itself. The edges are brittle and yellowed with age.\n"
        "Whatever secrets this scroll holds, they have waited a very long time\n"
        "to be read.";
    item.pickup_text =
        "You carefully lift the scroll from the sarcophagus.\n"
        "The ancient bones seem to shift, as if reluctant to let it go.";
    item.readable = true;
    state.items[item.id] = item;
}
