#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include <iostream>
#include <algorithm>

void cmdPickup(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Pick up what? Specify an item name.\n";
        return;
    }

    std::string item_id = findItemInRoom(state, args);
    if (item_id.empty())
    {
        std::cout << "There's no \"" << args << "\" here to pick up.\n";
        return;
    }

    Room &room = state.rooms.at(state.player.current_room);
    auto it = std::find(room.item_ids.begin(), room.item_ids.end(), item_id);
    if (it != room.item_ids.end())
    {
        room.item_ids.erase(it);
    }

    state.player.inventory.push_back(item_id);

    const Item &item = state.items.at(item_id);
    if (!item.pickup_text.empty())
    {
        std::cout << item.pickup_text << "\n";
    }
    else
    {
        std::cout << "You pick up the " << item.name << ".\n";
    }

    if (item.is_suspicious)
    {
        std::cout << "  [!] This item could raise suspicion if others see it.\n";
    }
}

void cmdDrop(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Drop what? Specify an item name.\n";
        return;
    }

    std::string item_id = findItemInInventory(state, args);
    if (item_id.empty())
    {
        std::cout << "You don't have \"" << args << "\" in your inventory.\n";
        return;
    }

    auto it = std::find(state.player.inventory.begin(), state.player.inventory.end(), item_id);
    if (it != state.player.inventory.end())
    {
        state.player.inventory.erase(it);
    }

    Room &room = state.rooms.at(state.player.current_room);
    room.item_ids.push_back(item_id);

    std::cout << "You drop the " << state.items.at(item_id).name << " on the ground.\n";
}

void cmdInventory(GameState &state, const std::string &)
{
    if (state.player.inventory.empty())
    {
        std::cout << "Your inventory is empty.\n";
        return;
    }

    std::cout << "\n--- Inventory ---\n";
    for (const auto &item_id : state.player.inventory)
    {
        if (state.items.count(item_id))
        {
            const Item &item = state.items.at(item_id);
            std::cout << "  - " << item.name << ": " << item.description << "\n";
        }
    }
    std::cout << "\nGold: " << state.player.gold << "\n\n";
}
