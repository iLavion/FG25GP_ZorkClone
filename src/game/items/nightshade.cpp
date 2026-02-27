#include "game.hpp"

void registerNightshade(GameState &state)
{
    Item item;
    item.id = "nightshade";
    item.name = "Nightshade Berries";
    item.description = "Beautiful but deadly berries growing in a shadowy corner of the garden.\n"
                       "Even a small amount could be lethal if ingested.";
    item.inspect_text =
        "Clusters of glossy black berries on a sprawling vine, hidden in the\n"
        "shadowy corner where the garden wall meets the hedge. Belladonna,\n"
        "deadly nightshade. Beautiful to look at, lethal to consume.\n"
        "Even touching them makes your fingertips tingle. A few crushed berries\n"
        "in the right cup could end someone's story forever.\n"
        "Gardener Thorne grows them \"for pest control.\" Of course he does.";
    item.pickup_text =
        "You carefully pluck the nightshade berries, wrapping them in a leaf.\n"
        "Your hands tremble slightly. There is no innocent reason to carry these.";
    item.is_suspicious = true;
    item.is_poison = true;
    state.items[item.id] = item;
}
