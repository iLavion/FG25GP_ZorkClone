#include "game.hpp"

void registerTeaSet(GameState &state)
{
    Item item;
    item.id = "tea_set";
    item.name = "Fine Tea Set";
    item.description = "An elegant porcelain tea set. Perfect for serving guests.";
    item.inspect_text =
        "An exquisite porcelain tea set painted with delicate blue flowers.\n"
        "Two cups, a teapot, a sugar bowl, and a small cream pitcher, all\n"
        "nestled on a silver tray. The kind of set your mother used to host\n"
        "visiting nobility. The cups are thin enough to see light through.\n"
        "A perfect vessel for hospitality... or treachery.";
    item.pickup_text = "You carefully lift the tea set. The porcelain clinks softly.";
    state.items[item.id] = item;
}
