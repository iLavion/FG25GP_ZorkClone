#include "game.hpp"

void registerLetter(GameState &state)
{
    Item item;
    item.id = "letter";
    item.name = "Sealed Letter";
    item.description = "A mysterious letter with a broken seal.";
    item.inspect_text =
        "A folded letter on thick parchment, sealed with crimson wax, though\n"
        "the seal has been broken. The handwriting is elegant but unfamiliar.\n"
        "Addressed to Elena from an anonymous benefactor, it promises \"unwavering\n"
        "support for your ascension to the place you deserve.\" The implications\n"
        "are clear: someone powerful is maneuvering Elena into a position of\n"
        "influence. But who? And why?";
    item.pickup_text = "You fold the letter carefully and tuck it into your bodice. Evidence.";
    state.items[item.id] = item;
}
