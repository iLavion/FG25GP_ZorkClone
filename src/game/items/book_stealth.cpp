#include "game.hpp"

void registerBookStealth(GameState &state)
{
    Item item;
    item.id = "book_stealth";
    item.name = "Shadows and Silence";
    item.description = "A manual on moving unseen and unheard. Strangely well-worn.";
    item.inspect_text =
        "\"Shadows and Silence: A Practical Guide\", no author listed.\n"
        "The leather cover is worn smooth from frequent handling. Someone in\n"
        "this household has read it many times. Chapters cover silent movement,\n"
        "lock manipulation, disguise techniques, and the art of eavesdropping.\n"
        "A curious book to find in a duke's library. Or perhaps not.";
    item.pickup_text = "You take the well-worn manual. Someone clearly valued its lessons.";
    item.readable = true;
    item.skill_grant = "stealth";
    item.xp_grant = 15;
    state.items[item.id] = item;
}
