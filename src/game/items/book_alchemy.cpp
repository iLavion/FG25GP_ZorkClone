#include "game.hpp"

void registerBookAlchemy(GameState &state)
{
    Item item;
    item.id = "book_alchemy";
    item.name = "Introduction to Alchemy";
    item.description = "A thick tome on herbal concoctions, tinctures, and... poisons.";
    item.inspect_text =
        "\"Introduction to Alchemy\" by Magister Hywell of the Eastern Academy.\n"
        "Leather-bound, with gilt pages and meticulous illustrations of plants,\n"
        "distillation apparatus, and chemical reactions. Chapters cover healing\n"
        "salves, sleeping draughts, truth serums, and, buried in the appendix,\n"
        "a detailed section on lethal compounds. Someone has dog-eared that page.";
    item.pickup_text = "You slide the heavy tome under your arm. Knowledge is the deadliest weapon.";
    item.readable = true;
    item.skill_grant = "alchemy";
    item.xp_grant = 15;
    state.items[item.id] = item;
}
