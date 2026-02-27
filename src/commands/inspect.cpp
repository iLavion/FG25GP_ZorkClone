#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include <iostream>

void cmdInspect(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Inspect what? Specify an item name.\n";
        return;
    }

    std::string item_id = findItemInInventory(state, args);
    if (item_id.empty())
    {
        item_id = findItemInRoom(state, args);
    }
    if (item_id.empty())
    {
        std::cout << "There's no \"" << args << "\" here or in your inventory to inspect.\n";
        return;
    }

    const Item &item = state.items.at(item_id);

    std::cout << "\n--- " << item.name << " ---\n";

    if (!item.inspect_text.empty())
    {
        std::cout << item.inspect_text << "\n";
    }
    else
    {
        std::cout << item.description << "\n";
    }

    std::cout << "\n";

    if (item.edible)
    {
        std::cout << "  [Food] Restores " << item.hunger_restore << " hunger when eaten.\n";
    }
    else if (item.is_weapon)
    {
        std::cout << "  [Weapon] Can be used as a weapon.\n";
    }
    else if (item.readable)
    {
        std::cout << "  [Readable] Use the READ command to study this.\n";
    }
    else if (item.is_poison)
    {
        std::cout << "  [Poison] A deadly substance.\n";
    }
    else if (item.is_suspicious)
    {
        std::cout << "  [Suspicious] Carrying this raises suspicion.\n";
    }
    else if (item.is_consumable)
    {
        std::cout << "  [Consumable] Used up when consumed.\n";
    }

    std::cout << "\n";
}
