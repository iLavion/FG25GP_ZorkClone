#include "game.hpp"

void registerLetterOpener(GameState &state)
{
    Item item;
    item.id = "letter_opener";
    item.name = "Letter Opener";
    item.description = "A pointed letter opener from the study.";
    item.inspect_text =
        "An ornate letter opener with a silver handle shaped like a serpent.\n"
        "The blade is slender but wickedly sharp, Father uses it daily for\n"
        "his correspondence. The serpent's ruby eyes glint in the light.\n"
        "It was a gift from a visiting ambassador. Decorative, but the\n"
        "point could easily pierce flesh. A gentleman's weapon.";
    item.pickup_text =
        "You palm the letter opener from Father's desk. Small, sharp, easily concealed.";
    item.is_weapon = true;
    state.items[item.id] = item;
}
