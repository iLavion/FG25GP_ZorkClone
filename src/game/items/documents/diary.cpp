#include "game.hpp"

void registerDiary(GameState &state)
{
    Item item;
    item.id = "diary";
    item.name = "Elena's Diary";
    item.description = "The heroine's private diary. Full of secrets.";
    item.inspect_text =
        "A leather-bound diary with Elena's name embossed on the cover in\n"
        "simple gold lettering. The pages are filled with neat, careful\n"
        "handwriting, the penmanship of someone who learned to write late\n"
        "but practiced obsessively. Entries detail her daily life at the estate,\n"
        "her growing friendships with the nobility, and her private fears.\n"
        "One entry catches your eye: \"She watches me with those cold eyes.\n"
        "I must be more careful. The Duke's daughter is dangerous.\"";
    item.pickup_text =
        "You snatch Elena's diary. Your heart races, if she finds out\n"
        "you have this, there will be consequences.";
    item.is_suspicious = true;
    item.readable = true;
    state.items[item.id] = item;
}
