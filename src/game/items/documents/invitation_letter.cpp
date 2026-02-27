#include "game.hpp"

void registerInvitationLetter(GameState &state)
{
    Item item;
    item.id = "invitation_letter";
    item.name = "Invitation Letter";
    item.description = "A formal tea invitation addressed to Elena, in your handwriting.";
    item.inspect_text =
        "A letter penned in your finest hand on ducal stationery:\n\n"
        "  \"Dear Elena,\n"
        "   I would be honored if you would join me for afternoon tea.\n"
        "   It would give us a chance to know each other better.\n"
        "   With warm regards,\n"
        "   Lady Seraphina\"\n\n"
        "The ink is still fresh, the words carefully chosen to seem warm\n"
        "and genuine. Not a single crossed-out word. You practiced this\n"
        "three times before committing to paper. The perfect trap.";
    item.pickup_text = "You fold the invitation and seal it with wax.";
    state.items[item.id] = item;
}
