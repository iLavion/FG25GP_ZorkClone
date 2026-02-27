#include "game.hpp"

void registerKnife(GameState &state)
{
    Item item;
    item.id = "knife";
    item.name = "Kitchen Knife";
    item.description = "A sharp blade from the kitchen.";
    item.inspect_text =
        "A well-honed kitchen knife with a wooden handle darkened by years of use.\n"
        "The blade gleams under any light, Chef Marcel keeps his tools immaculate.\n"
        "It was made for cutting meat, but in desperate hands, it could serve\n"
        "a far darker purpose. The weight feels natural. Almost too natural.";
    item.pickup_text =
        "You slide the knife off the cutting board and conceal it in your sleeve.\n"
        "Your heart pounds. This is not something a lady should carry.";
    item.is_weapon = true;
    item.is_suspicious = true;
    state.items[item.id] = item;
}
