#include "commands/helpers.hpp"
#include "utilities/string.hpp"

std::string findNPCInRoom(const GameState &state, const std::string &name)
{
    std::string lower_name = to_lower(name);
    const Room &room = state.rooms.at(state.player.current_room);
    for (const auto &npc_id : room.npc_ids)
    {
        if (state.npcs.count(npc_id))
        {
            const NPC &npc = state.npcs.at(npc_id);
            std::string lower_npc = to_lower(npc.name);
            if (to_lower(npc_id) == lower_name ||
                lower_npc == lower_name ||
                lower_npc.find(lower_name) != std::string::npos)
            {
                return npc_id;
            }
        }
    }
    return "";
}

std::string findItemInRoom(const GameState &state, const std::string &name)
{
    std::string lower_name = to_lower(name);
    const Room &room = state.rooms.at(state.player.current_room);
    for (const auto &item_id : room.item_ids)
    {
        if (state.items.count(item_id))
        {
            const Item &item = state.items.at(item_id);
            std::string lower_item = to_lower(item.name);
            if (to_lower(item_id) == lower_name ||
                lower_item == lower_name ||
                lower_item.find(lower_name) != std::string::npos)
            {
                return item_id;
            }
        }
    }
    return "";
}

std::string findItemInInventory(const GameState &state, const std::string &name)
{
    std::string lower_name = to_lower(name);
    for (const auto &item_id : state.player.inventory)
    {
        if (state.items.count(item_id))
        {
            const Item &item = state.items.at(item_id);
            std::string lower_item = to_lower(item.name);
            if (to_lower(item_id) == lower_name ||
                lower_item == lower_name ||
                lower_item.find(lower_name) != std::string::npos)
            {
                return item_id;
            }
        }
    }
    return "";
}
