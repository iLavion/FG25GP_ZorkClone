#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include <iostream>
#include <algorithm>

void cmdUse(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Use what? Specify an item name.\n";
        return;
    }

    std::string item_id = findItemInInventory(state, args);
    if (item_id.empty())
    {
        std::cout << "You don't have \"" << args << "\" to use.\n";
        return;
    }

    const Item &item = state.items.at(item_id);

    if (item_id == "perfume")
    {
        std::cout << "You dab on some Lavender Perfume. You smell delightful.\n";
        std::cout << "NPCs will be slightly more receptive to you.\n";
        state.player.reputation = std::min(100, state.player.reputation + 3);
    }
    else if (item_id == "diary")
    {
        std::cout << "You read Elena's diary carefully...\n";
        std::cout << "\"Day 14: The Duke's son is kinder than I expected.\n";
        std::cout << " The Prince's letters grow more frequent. I must be careful\n";
        std::cout << " not to draw too much attention. 'She' is watching me.\"\n\n";
        std::cout << "So she KNOWS you're watching. Interesting.\n";
        state.heroine_popularity += 2;
        state.quest.elena_diary_read = true;
    }
    else if (item_id == "letter")
    {
        std::cout << "You read the sealed letter. It's addressed to Elena from an\n";
        std::cout << "anonymous benefactor, promising support for her \"ascension.\"\n";
        std::cout << "Someone powerful is backing her.\n";
    }
    else if (item_id == "poison_vial" || item_id == "nightshade")
    {
        bool has_tea = findItemInInventory(state, "tea_set") != "";
        if (has_tea && state.player.current_room == "kitchen" && state.quest.elena_arrived_dinner)
        {
            std::cout << "With trembling hands, you uncork the vial and pour its contents\n";
            std::cout << "into the tea. The dark liquid dissolves without a trace.\n";
            std::cout << "The tea looks, and smells, perfectly normal.\n\n";
            std::cout << "  [!] The tea is now poisoned. Bring it to Elena in the dining room.\n";
            state.quest.poisoned_tea = true;
            state.player.suspicion += 5;
            auto pit = std::find(state.player.inventory.begin(), state.player.inventory.end(), item_id);
            if (pit != state.player.inventory.end())
            {
                state.player.inventory.erase(pit);
            }
        }
        else if (item.is_poison)
        {
            std::cout << "You examine the " << item.name << " carefully. Deadly stuff.\n";
            if (!state.quest.elena_arrived_dinner)
            {
                std::cout << "You need a reason to serve something to Elena first.\n";
                std::cout << "Perhaps invite her to tea?\n";
            }
            else if (!has_tea)
            {
                std::cout << "You need something to put it in. A tea set, perhaps?\n";
            }
            else
            {
                std::cout << "The kitchen would be the best place to prepare this.\n";
            }
            state.player.suspicion += 3;
        }
    }
    else if (item_id == "tea_set")
    {
        if (state.quest.poisoned_tea && state.player.current_room == "dining_room")
        {
            bool elena_here = false;
            for (const auto &npc_id : state.rooms.at("dining_room").npc_ids)
            {
                if (npc_id == "elena")
                {
                    elena_here = true;
                }
            }
            if (elena_here && state.npcs.count("elena") && state.npcs.at("elena").alive)
            {
                std::cout << "\"Oh, how thoughtful!\" Elena smiles and takes the cup.\n";
                std::cout << "She raises it to her lips and drinks deeply.\n";
                std::cout << "\"Mmm, this is exquisite. Thank you, Lady Seraphina.\"\n\n";
                std::cout << "You watch her sip the poisoned tea. Minutes pass...\n";
                std::cout << "Elena's smile fades. Her cup falls from trembling hands.\n";
                std::cout << "\"I... I don't feel well...\" She collapses.\n\n";
                state.quest.elena_drank_tea = true;
                auto tit = std::find(state.player.inventory.begin(), state.player.inventory.end(), "tea_set");
                if (tit != state.player.inventory.end())
                {
                    state.player.inventory.erase(tit);
                }
            }
            else
            {
                std::cout << "You set up the tea service. You need Elena here to serve it.\n";
            }
        }
        else if (state.quest.poisoned_tea)
        {
            std::cout << "The poisoned tea is ready. Bring it to the dining room when Elena is there.\n";
        }
        else
        {
            std::cout << "A beautiful tea set. You could use it to serve tea to a guest.\n";
        }
    }
    else if (item_id == "rope" && state.quest.elena_dead && !state.quest.body_hidden)
    {
        if (state.player.current_room == "cellar" && state.quest.secret_passage_known)
        {
            std::cout << "Using the rope, you carefully move the evidence through Thorne's\n";
            std::cout << "secret passage. No one will find it beyond the estate walls.\n";
            state.quest.body_hidden = true;
            state.player.suspicion = std::max(0, state.player.suspicion - 10);
            auto rit = std::find(state.player.inventory.begin(), state.player.inventory.end(), "rope");
            if (rit != state.player.inventory.end())
            {
                state.player.inventory.erase(rit);
            }
        }
        else if (state.quest.elena_dead)
        {
            std::cout << "You could use this to move the body... but where? And how?\n";
            if (!state.quest.secret_passage_known)
            {
                std::cout << "You need to find a hidden way out of the estate.\n";
            }
            else
            {
                std::cout << "The cellar passage might be your best bet.\n";
            }
        }
        else
        {
            std::cout << "Sturdy rope. You're not sure what to do with it right now.\n";
        }
    }
    else if (item_id == "key")
    {
        if (state.player.current_room == "kitchen")
        {
            std::cout << "You try the iron key on the locked cabinet... it clicks open!\n";
            std::cout << "Inside you find medicinal supplies and herbs.\n";
            if (!state.items.count("sleeping_draught"))
            {
                std::cout << "You discover a Sleeping Draught among the supplies!\n";
                state.rooms["kitchen"].item_ids.push_back("sleeping_draught");
                std::cout << "  A Sleeping Draught has appeared! PICKUP sleeping_draught to take it.\n";
            }
            else
            {
                bool draught_placed = false;
                for (const auto &rid_item : state.rooms["kitchen"].item_ids)
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
                if (!draught_placed && !draught_in_inv)
                {
                    std::cout << "You discover a Sleeping Draught among the supplies!\n";
                    state.rooms["kitchen"].item_ids.push_back("sleeping_draught");
                    std::cout << "  A Sleeping Draught has appeared! PICKUP sleeping_draught to take it.\n";
                }
                else
                {
                    std::cout << "The cabinet is already empty.\n";
                }
            }
            auto kit = std::find(state.player.inventory.begin(),
                                 state.player.inventory.end(), "key");
            if (kit != state.player.inventory.end())
            {
                state.player.inventory.erase(kit);
            }
        }
        else
        {
            std::cout << "You try the iron key... but there's nothing to unlock here.\n";
            std::cout << "  [i] Perhaps there's a locked cabinet somewhere in the estate.\n";
        }
    }
    else if (item_id == "sleeping_draught")
    {
        const Room &room = state.rooms.at(state.player.current_room);
        if (!room.npc_ids.empty())
        {
            std::string target_id;
            for (const auto &nid : room.npc_ids)
            {
                if (state.npcs.count(nid) && state.npcs.at(nid).alive)
                {
                    target_id = nid;
                    break;
                }
            }
            if (!target_id.empty())
            {
                NPC &target = state.npcs.at(target_id);
                std::cout << "You discreetly slip the sleeping draught into " << target.name
                          << "'s drink.\n";
                std::cout << "Minutes later, their eyes grow heavy... they slump into a chair.\n";
                std::cout << target.name << " is fast asleep! They won't notice anything for hours.\n\n";
                auto &npc_ids = state.rooms[state.player.current_room].npc_ids;
                npc_ids.erase(std::remove(npc_ids.begin(), npc_ids.end(), target_id), npc_ids.end());
                target.current_room = "servants_quarters";
                state.rooms["servants_quarters"].npc_ids.push_back(target_id);
                state.player.suspicion += 5;
                std::cout << "  " << target.name << " has been moved. Suspicion +5.\n";
                auto dit = std::find(state.player.inventory.begin(),
                                     state.player.inventory.end(), "sleeping_draught");
                if (dit != state.player.inventory.end())
                {
                    state.player.inventory.erase(dit);
                }
            }
        }
        else
        {
            std::cout << "There's no one here to use this on.\n";
        }
    }
    else if (item.is_weapon)
    {
        std::cout << "You brandish the " << item.name << ". Careful, if someone sees you...\n";
        state.player.suspicion += 3;
    }
    else if (item_id == "gold_ring" || item_id == "silver_brooch")
    {
        std::cout << "You could offer this as a bribe or gift. TALK to an NPC to negotiate.\n";
    }
    else
    {
        std::cout << "You examine the " << item.name << ". " << item.description << "\n";
    }
}
