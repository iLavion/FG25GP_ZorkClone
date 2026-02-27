#include "game.hpp"

void registerBookNobility(GameState &state)
{
    Item item;
    item.id = "book_nobility";
    item.name = "Noble Lineages of the Empire";
    item.description = "An exhaustive record of every noble house, their rights, and their feuds.";
    item.inspect_text =
        "\"Noble Lineages of the Empire, Seventh Edition\", a massive reference\n"
        "tome bound in burgundy leather. Every great house is catalogued here:\n"
        "their crests, territories, rivalries, marriages, and scandals.\n"
        "Your own family, House Aldric, has three full pages. Elena's common\n"
        "origins are conspicuously absent. Knowledge of these bloodlines\n"
        "is power in the court.";
    item.pickup_text = "You heft the heavy volume. Bloodlines and politics, your kind of reading.";
    item.readable = true;
    item.skill_grant = "knowledge";
    item.xp_grant = 15;
    state.items[item.id] = item;
}
