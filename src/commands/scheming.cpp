#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include <iostream>
#include <algorithm>

void cmdPlot(GameState &state, const std::string &)
{
    std::cout << "\n--- Plotting ---\n";
    std::cout << "Elena's Popularity: " << state.heroine_popularity << "/100\n";
    std::cout << "Gold: " << state.player.gold << "\n";
    std::cout << "Time: " << timeToString(state.hour, state.minute) << "\n\n";

    if (!state.quest.dead_bodies.empty())
    {
        std::cout << "~ Bodies ~\n";
        bool any_unhidden = false;
        for (const auto &entry : state.quest.dead_bodies)
        {
            std::string name = state.npcs.count(entry.first) ? state.npcs.at(entry.first).name : entry.first;
            if (state.quest.hidden_bodies.count(entry.first))
            {
                std::cout << "  [x] " << name << "'s body has been disposed of.\n";
            }
            else
            {
                std::cout << "  [!] " << name << "'s body is still in the " << state.rooms.at(entry.second).name << "!\n";
                any_unhidden = true;
            }
        }
        if (any_unhidden)
        {
            if (state.quest.secret_passage_known)
            {
                std::cout << "  Hint: USE rope in the cellar to use the secret passage.\n";
            }
            else
            {
                std::cout << "  Hint: Find someone who knows hidden paths out of the estate.\n";
            }
        }
        else
        {
            std::cout << "  All evidence has been hidden. Keep your suspicion low.\n";
        }
        std::cout << "\n";
    }

    if (state.quest.elena_dead)
    {
        std::cout << "Elena is dead.\n";
    }
    else
    {
        std::cout << "~ Poison Tea Plot ~\n";
        if (!state.quest.invited_elena)
        {
            std::cout << "  [ ] Talk to your Father about inviting Elena to dinner.\n";
        }
        else
        {
            std::cout << "  [x] Father has approved the dinner invitation.\n";
        }

        if (!state.quest.wrote_invitation)
        {
            std::cout << "  [ ] Write the invitation letter (WRITE in your bedroom).\n";
        }
        else
        {
            std::cout << "  [x] Invitation letter written.\n";
        }

        if (!state.quest.elena_arrived_dinner)
        {
            std::cout << "  [ ] Give the letter to Elena or have Graves deliver it.\n";
        }
        else
        {
            std::cout << "  [x] Elena has accepted the invitation.\n";
        }

        if (!state.quest.acquired_poison)
        {
            std::cout << "  [ ] Acquire poison (cellar vial or garden nightshade).\n";
        }
        else
        {
            std::cout << "  [x] Poison acquired.\n";
        }

        if (!state.quest.poisoned_tea)
        {
            std::cout << "  [ ] Poison the tea (USE poison with tea_set in kitchen).\n";
        }
        else
        {
            std::cout << "  [x] Tea has been poisoned!\n";
        }

        if (state.quest.poisoned_tea && !state.quest.elena_drank_tea)
        {
            std::cout << "  [ ] Serve the tea to Elena (USE tea_set in dining room).\n";
        }
    }

    std::cout << "\n~ Other Schemes ~\n";
    if (state.player.current_room == "library")
    {
        std::cout << "In the library, you could READ books to gain useful skills.\n";
    }
    else if (state.player.current_room == "balcony")
    {
        std::cout << "From up here, you can observe the courtyard and garden.\n";
        std::cout << "  [i] Strategic observation: insight for your schemes.\n";
    }
    else if (state.player.current_room == "cellar")
    {
        std::cout << "The cellar is dark and private. A good place to hide things...\n";
    }
    else if (state.player.current_room == "bedroom")
    {
        std::cout << "In the privacy of your chambers, review your options.\n";
        std::cout << "  - TALK to NPCs for alliances\n";
        std::cout << "  - HIRE servants for dirty work\n";
        std::cout << "  - WRITE to compose letters\n";
    }
    else
    {
        std::cout << "The heroine's popularity grows by the day. Act wisely.\n";
    }
    std::cout << "\n";
}

void cmdHire(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Hire whom? Specify an NPC name.\n";
        return;
    }

    std::string npc_id = findNPCInRoom(state, args);
    if (npc_id.empty())
    {
        std::cout << "There's no one called \"" << args << "\" here to hire.\n";
        return;
    }

    NPC &npc = state.npcs.at(npc_id);
    if (!npc.hireable)
    {
        std::cout << npc.name << " is not available for hire.\n";
        return;
    }

    if (state.player.gold < npc.hire_cost)
    {
        std::cout << npc.name << " wants " << npc.hire_cost << " gold, but you only have " << state.player.gold << ".\n";
        return;
    }

    std::cout << "You approach " << npc.name << " about a discreet arrangement.\n";
    std::cout << "(Use TALK " << args << " and look for their hire options.)\n";
}

void cmdRead(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Read what? Specify an item name.\n";
        return;
    }

    std::string item_id = findItemInInventory(state, args);
    if (item_id.empty())
    {
        item_id = findItemInRoom(state, args);
        std::cout << "There's no \"" << args << "\" here to read.\n";
        return;
    }

    const Item &item = state.items.at(item_id);

    if (!item.readable && item_id != "letter" && item_id != "diary")
    {
        std::cout << "You can't read the " << item.name << ".\n";
        return;
    }

    if (item_id == "diary")
    {
        std::cout << "You flip through Elena's diary...\n";
        std::cout << "\"Day 14: The Duke's son is kinder than I expected.\n";
        std::cout << " The Prince's letters grow more frequent. I must be careful\n";
        std::cout << " not to draw too much attention. 'She' is watching me.\"\n\n";
        std::cout << "So she KNOWS you're watching.\n";
        state.quest.elena_diary_read = true;
        state.heroine_popularity += 2;
        return;
    }

    if (item_id == "letter")
    {
        std::cout << "You read the sealed letter. It's from an anonymous benefactor,\n";
        std::cout << "promising Elena support for her \"ascension.\" Someone powerful backs her.\n";
        return;
    }

    if (item.readable && !item.skill_grant.empty())
    {
        if (state.books_read.count(item_id))
        {
            std::cout << "You've already studied \"" << item.name << "\". You recall the key points.\n";
            return;
        }

        std::cout << "You settle into a reading nook and open \"" << item.name << "\"...\n";
        std::cout << "...\n";

        state.player.skills[item.skill_grant] += item.xp_grant;
        state.books_read.insert(item_id);

        std::cout << "After careful study, you've gained insight!\n";
        std::cout << "  " << item.skill_grant << " +" << item.xp_grant
                  << " (now: " << state.player.skills[item.skill_grant] << ")\n\n";

        if (item.skill_grant == "alchemy")
        {
            std::cout << "You now understand the basics of herbal preparations.\n";
            std::cout << "Poisons, antidotes, sleeping draughts, the possibilities...\n";
            state.quest.acquired_poison = true;
        }
        else if (item.skill_grant == "persuasion")
        {
            std::cout << "The art of words. You feel more confident in conversations.\n";
        }
        else if (item.skill_grant == "stealth")
        {
            std::cout << "How to move unseen. How to leave no trace. Useful knowledge.\n";
        }
        else if (item.skill_grant == "knowledge")
        {
            std::cout << "Noble lineages, inheritance laws, political maneuvers.\n";
            std::cout << "You understand the game of nobles better now.\n";
        }

        advanceTime(state, 30);
        std::cout << "\n  Time passed: 30 minutes. It is now " << timeToString(state.hour, state.minute) << ".\n";
    }
    else if (item.readable)
    {
        std::cout << "You read \"" << item.name << "\". " << item.description << "\n";
    }
}

void cmdWrite(GameState &state, const std::string &)
{
    if (state.player.current_room != "bedroom")
    {
        std::cout << "You need your writing desk. Go to your bedroom.\n";
        return;
    }

    if (!state.quest.invited_elena)
    {
        std::cout << "You sit at the desk but have nothing to write. Perhaps you should\n";
        std::cout << "talk to your Father about inviting Elena first?\n";
        return;
    }

    if (state.quest.wrote_invitation)
    {
        std::cout << "You've already written the invitation. Have it delivered.\n";
        return;
    }

    std::cout << "You sit at your writing desk and carefully pen a formal invitation:\n\n";
    std::cout << "  \"Dear Elena,\n";
    std::cout << "   I would be honored if you would join me for afternoon tea.\n";
    std::cout << "   It would give us a chance to know each other better.\n";
    std::cout << "   With warm regards,\n";
    std::cout << "   Lady Seraphina\"\n\n";
    std::cout << "The letter is ready. You can deliver it to Elena yourself,\n";
    std::cout << "or ask Butler Graves to deliver it for you.\n";

    state.quest.wrote_invitation = true;

    state.player.inventory.push_back("invitation_letter");

    advanceTime(state, 15);
}