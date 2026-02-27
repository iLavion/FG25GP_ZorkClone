#include "game.hpp"

void registerBookPersuasion(GameState &state)
{
    Item item;
    item.id = "book_persuasion";
    item.name = "The Art of Rhetoric";
    item.description = "A classic treatise on persuasion, manipulation, and debate.";
    item.inspect_text =
        "\"The Art of Rhetoric\" by Lord Chancellor Voss, required reading for\n"
        "every aspiring politician in the Empire. Its pages are dense with\n"
        "techniques: mirroring, deflection, the strategic use of silence,\n"
        "emotional anchoring. Some call it a manual for honest debate.\n"
        "Others call it a handbook for liars. Both are correct.";
    item.pickup_text = "You take the book. Words can be sharper than any blade.";
    item.readable = true;
    item.skill_grant = "persuasion";
    item.xp_grant = 15;
    state.items[item.id] = item;
}
