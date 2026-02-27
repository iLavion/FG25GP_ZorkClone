#include "game.hpp"

void registerPoisonVial(GameState &state)
{
    Item item;
    item.id = "poison_vial";
    item.name = "Mysterious Vial";
    item.description = "A small vial with dark liquid. Smells bitter.";
    item.inspect_text =
        "A small glass vial stoppered with cork and sealed with black wax.\n"
        "The liquid inside is dark as ink and viscous. When you tilt it, it\n"
        "moves slowly, like syrup. A faint bitter scent escapes even through\n"
        "the seal. No label, no markings, someone hid this here deliberately.\n"
        "A few drops in a drink would be undetectable. A full dose... fatal.";
    item.pickup_text =
        "You take the mysterious vial with trembling fingers.\n"
        "This changes everything. You are now carrying death in your pocket.";
    item.is_suspicious = true;
    item.is_poison = true;
    item.is_concealable = true;
    state.items[item.id] = item;
}
