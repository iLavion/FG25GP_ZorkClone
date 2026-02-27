#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include "utilities/string.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

static bool hasTrait(const NPC &npc, Trait t)
{
    return std::find(npc.traits.begin(), npc.traits.end(), t) != npc.traits.end();
}

static bool isNPCAlert(const NPC &npc, int hour)
{
    bool nighttime = (hour >= 22 || hour < 5);
    if (nighttime)
    {
        if (hasTrait(npc, Trait::DeepSleeper))
        {
            return false;
        }
        else if (hasTrait(npc, Trait::LightSleeper))
        {
            return true;
        }
        return false;
    }
    return true;
}

void cmdSearch(GameState &state, const std::string &)
{
    const Room &room = state.rooms.at(state.player.current_room);
    std::cout << "\nYou carefully search the " << room.name << "...\n\n";
    bool noticed = false;
    for (const auto &npc_id : room.npc_ids)
    {
        if (!state.npcs.count(npc_id) || !state.npcs.at(npc_id).alive)
        {
            continue;
        }
        const NPC &npc = state.npcs.at(npc_id);
        if (isNPCAlert(npc, state.hour))
        {
            std::cout << "  " << npc.name << " watches you rummage around with " << (hasTrait(npc, Trait::Perceptive) ? "sharp, suspicious" : "curious") << " eyes.\n";
            noticed = true;
        }
    }

    if (room.item_ids.empty())
    {
        std::cout << "You find nothing of interest.\n";
    }
    else
    {
        std::cout << "You find the following:\n";
        for (const auto &item_id : room.item_ids)
        {
            if (!state.items.count(item_id))
            {
                continue;
            }
            const Item &item = state.items.at(item_id);
            std::cout << "  * " << item.name << ": " << item.description << "\n";
            if (item.is_weapon)
            {
                std::cout << "    [Weapon] Could be used as a weapon.\n";
            }
            else if (item.edible)
            {
                std::cout << "    [Food] Can be eaten. (+" << item.hunger_restore << " hunger)\n";
            }
            else if (item.readable)
            {
                std::cout << "    [Readable] Can be read with the READ command.\n";
            }
            else if (item.is_suspicious)
            {
                std::cout << "    [!] Carrying this would raise suspicion.\n";
            }
            else if (item.is_poison)
            {
                std::cout << "    [Poison] Deadly substance.\n";
            }
        }
    }

    const std::string &rid = state.player.current_room;

    if (rid == "kitchen")
    {
        std::cout << "\nYou check behind the pots, under the counter, inside drawers...\n";
        std::cout << "The kitchen is full of sharp implements and cooking supplies.\n";
        if (std::find(room.item_ids.begin(), room.item_ids.end(), "knife") != room.item_ids.end())
        {
            std::cout << "  [i] The Kitchen Knife sits on the cutting board. PICKUP knife to take it.\n";
        }
        bool draught_placed = false;
        for (const auto &rid_item : state.rooms[state.player.current_room].item_ids)
        {
            if (rid_item == "sleeping_draught")
            {
                draught_placed = true;
                break;
            }
        }
        bool draught_in_inv = false;
        for (const auto &inv_item : state.player.inventory)
        {
            if (inv_item == "sleeping_draught")
            {
                draught_in_inv = true;
                break;
            }
        }
        if (state.player.skills["alchemy"] >= 15 && !draught_placed && !draught_in_inv)
        {
            std::cout << "\nYour alchemy knowledge lets you identify the locked cabinet's contents.\n";
            std::cout << "You pick the simple latch and find a vial labeled \"Sleeping Draught.\"\n";
            state.rooms[state.player.current_room].item_ids.push_back("sleeping_draught");
            std::cout << "  A Sleeping Draught has appeared! PICKUP sleeping_draught to take it.\n";
        }
    }
    else if (rid == "cellar")
    {
        std::cout << "\nThe cellar is dark and damp. You check behind barrels and crates.\n";
        if (state.quest.secret_passage_known)
        {
            std::cout << "You notice the hidden passage Thorne showed you, still open.\n";
        }
        else
        {
            std::cout << "One section of the wall looks slightly different... but you can't figure it out.\n";
        }
    }
    else if (rid == "bedroom")
    {
        std::cout << "\nYou search through your own chambers, dresser, wardrobe, under the bed.\n";
        std::cout << "Everything is where you left it. This is YOUR domain, after all.\n";
    }
    else if (rid == "fathers_study")
    {
        std::cout << "\nYou carefully rifle through papers and books on the shelves.\n";
        std::cout << "Most are estate ledgers, but some correspondence catches your eye.\n";
    }
    else if (rid == "guest_room")
    {
        std::cout << "\nYou go through Elena's belongings with trembling hands.\n";
        std::cout << "Every second you spend here risks discovery.\n";
    }
    else if (rid == "garden")
    {
        std::cout << "\nYou search through the flower beds, hedgerows, and garden paths.\n";
        std::cout << "Nature hides many secrets.\n";
    }
    else if (rid == "servants_quarters")
    {
        std::cout << "\nYou look through the sparse furnishings of the servants' quarters.\n";
        std::cout << "The staff keeps things tidy but some personal effects are visible.\n";
    }
    else if (rid == "library")
    {
        std::cout << "\nShelves upon shelves of books. You can READ specific volumes for knowledge.\n";
    }
    else
    {
        std::cout << "\nYou've searched everywhere you can think of.\n";
    }

    std::cout << "\nUse PICKUP <item> to take anything you find.\n\n";
    advanceTime(state, 8);
}