#include "game.hpp"

void registerRope(GameState &state)
{
    Item item;
    item.id = "rope";
    item.name = "Coil of Rope";
    item.description = "Sturdy rope. Many uses, not all of them innocent.";
    item.inspect_text =
        "A coil of thick hemp rope, well-oiled and maintained. The kind used\n"
        "to haul supplies, bind cargo, or secure horses. In the servants'\n"
        "quarters, it serves practical purposes. In your hands, it could\n"
        "serve to move something heavy, or someone, through narrow passages\n"
        "where no one would think to look.";
    item.pickup_text = "You sling the rope over your shoulder. Heavy, but useful.";
    state.items[item.id] = item;
}
