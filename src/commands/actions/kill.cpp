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
        if (hasTrait(npc, Trait::LightSleeper))
        {
            return true;
        }
        return false;
    }
    return true;
}

void cmdKill(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Kill whom? Specify an NPC name.\n";
        return;
    }

    bool has_weapon = false;
    std::string weapon_id;
    std::string weapon_name;
    for (const auto &inv_id : state.player.inventory)
    {
        if (state.items.count(inv_id) && state.items.at(inv_id).is_weapon)
        {
            has_weapon = true;
            weapon_id = inv_id;
            weapon_name = state.items.at(inv_id).name;
            break;
        }
    }

    if (!has_weapon)
    {
        std::cout << "You have no weapon. You'd need something sharp, a knife, perhaps.\n";
        std::cout << "  [i] Try SEARCH in the Kitchen to find weapons.\n";
        return;
    }

    std::string npc_id = findNPCInRoom(state, args);
    if (npc_id.empty())
    {
        std::cout << "There's no one called \"" << args << "\" here.\n";
        return;
    }

    NPC &target = state.npcs.at(npc_id);

    if (!target.alive)
    {
        std::cout << target.name << " is already dead.\n";
        return;
    }

    bool is_family = (npc_id == "duke_aldric" || npc_id == "cedric" || npc_id == "rosalind");
    if (is_family)
    {
        std::cout << "You raise the " << weapon_name << " toward " << target.name << "...\n";
        std::cout << "This is your own FAMILY. Are you truly this far gone?\n";
        std::cout << "(The deed is done regardless, you've crossed a line.)\n\n";
    }

    const Room &room = state.rooms.at(state.player.current_room);

    std::vector<std::string> witnesses;
    for (const auto &other_id : room.npc_ids)
    {
        if (other_id != npc_id && state.npcs.count(other_id) && state.npcs.at(other_id).alive)
        {
            witnesses.push_back(other_id);
        }
    }

    bool target_alert = isNPCAlert(target, state.hour);
    bool target_strong = hasTrait(target, Trait::Strong);
    bool target_perceptive = hasTrait(target, Trait::Perceptive);

    if (!target_alert && witnesses.empty())
    {
        std::cout << target.name << " doesn't notice your approach.\n";
        if (hasTrait(target, Trait::LightSleeper))
        {
            std::cout << "At the last moment, " << target.name << "'s eyes flutter open, but it's too late.\n";
        }
        std::cout << "You drive the " << weapon_name << " forward. It's over in an instant.\n";
        std::cout << target.name << " slumps to the ground. Silent. Still.\n\n";
        std::cout << "  ** " << target.name << " is dead. **\n";
        target.alive = false;
        state.player.suspicion += 5;
        state.quest.npc_killed_unseen = true;
        std::cout << "  Suspicion +5 (clean kill, but the body remains)\n";
    }
    else if (target_alert && witnesses.empty())
    {
        std::cout << target.name << " sees you reach for the " << weapon_name << ".\n";
        if (target_perceptive)
        {
            std::cout << "\"I KNEW something was wrong with you!\" " << target.name << " shouts.\n";
            state.player.suspicion += 8;
        }
        if (target_strong)
        {
            std::cout << target.name << " lunges at you! A struggle ensues!\n";
            std::cout << "Furniture crashes. You're thrown against the wall.\n";
            std::cout << "But desperation gives you strength. The " << weapon_name << " finds its mark.\n";
            std::cout << target.name << " staggers... and falls.\n\n";
            std::cout << "  ** " << target.name << " is dead. **\n";
            std::cout << "  The struggle was loud. Someone may have heard.\n";

            target.alive = false;
            state.player.suspicion += 18;
            state.player.energy = std::max(0, state.player.energy - 20);
            std::cout << "  Suspicion +18, Energy -20 (brutal struggle)\n";
        }
        else
        {
            std::cout << "\"W-what are you--\" " << target.name << " backs away.\n";
            std::cout << "They try to run, but you're quicker.\n";
            std::cout << "The " << weapon_name << " strikes true. " << target.name << " collapses.\n\n";
            std::cout << "  ** " << target.name << " is dead. **\n";
            target.alive = false;
            state.player.suspicion += 12;
            std::cout << "  Suspicion +12 (they saw it coming, may have cried out)\n";
        }
    }
    else
    {
        std::cout << "You raise the " << weapon_name << " toward " << target.name << "...\n\n";
        for (const auto &w_id : witnesses)
        {
            const NPC &witness = state.npcs.at(w_id);
            if (hasTrait(witness, Trait::Strong))
            {
                std::cout << witness.name << " shouts \"STOP!\" and moves to intervene!\n";
            }
            else if (hasTrait(witness, Trait::Perceptive))
            {
                std::cout << witness.name << " screams in horror, eyes wide with recognition!\n";
            }
            else
            {
                std::cout << witness.name << " gasps and staggers backward!\n";
            }
        }

        bool blocked = false;
        for (const auto &w_id : witnesses)
        {
            if (hasTrait(state.npcs.at(w_id), Trait::Strong))
            {
                blocked = true;
                break;
            }
        }

        if (blocked)
        {
            std::cout << "\nA strong hand grabs your arm and wrenches the " << weapon_name << " away!\n";
            std::cout << "\"Have you lost your MIND?!\" \n";
            std::cout << "The attempt fails, but everyone saw what you tried to do.\n\n";
            std::cout << "  [!!] MURDER ATTEMPT WITNESSED, your reputation is destroyed.\n";
            state.player.suspicion += 35;
            state.player.reputation = std::max(0, state.player.reputation - 30);
            state.quest.murder_witnessed = true;
            std::cout << "  Suspicion +35, Reputation -30\n";
            auto wit = std::find(state.player.inventory.begin(), state.player.inventory.end(), weapon_id);
            if (wit != state.player.inventory.end())
            {
                state.player.inventory.erase(wit);
            }
            state.rooms[state.player.current_room].item_ids.push_back(weapon_id);
            std::cout << "  The " << weapon_name << " is knocked from your hands.\n";
        }
        else
        {
            if (target_strong)
            {
                std::cout << "\n"
                          << target.name << " fights back viciously!\n";
                std::cout << "The room erupts in chaos. Screaming. Crashing. Blood.\n";
                std::cout << "But in the end, you prevail. " << target.name << " falls.\n\n";
                state.player.energy = std::max(0, state.player.energy - 20);
            }
            else
            {
                std::cout << "\nBefore anyone can react, the " << weapon_name << " strikes. " << target.name << " crumples.\n\n";
            }
            std::cout << "  ** " << target.name << " is dead. **\n";
            std::cout << "  [!!] MURDER WITNESSED by " << witnesses.size() << " person(s)!\n";
            target.alive = false;
            state.player.suspicion += 40;
            state.player.reputation = std::max(0, state.player.reputation - 25);
            state.quest.murder_witnessed = true;
            std::cout << "  Suspicion +40, Reputation -25\n";
            for (const auto &w_id : witnesses)
            {
                state.npcs[w_id].disposition = Disposition::Hostile;
                state.npcs[w_id].suspicion = 100;
            }
        }
    }

    if (!target.alive)
    {
        auto &npc_ids = state.rooms[state.player.current_room].npc_ids;
        npc_ids.erase(std::remove(npc_ids.begin(), npc_ids.end(), npc_id), npc_ids.end());
        if (npc_id == "elena")
        {
            state.quest.elena_dead = true;
            state.heroine_popularity = 0;
            std::cout << "\n  Elena, the heroine, is dead by your hand.\n";
            std::cout << "  The heroine's popularity is now 0.\n";
            std::cout << "  But the consequences may be dire...\n";
        }
        if (npc_id == "duke_aldric")
        {
            std::cout << "\n  You have killed your own FATHER.\n";
            std::cout << "  The estate will fall into chaos. The nobles will demand justice.\n";
            state.player.suspicion += 20;
            state.player.reputation = 0;
        }
        if (npc_id == "captain_roderick")
        {
            std::cout << "\n  With the guard captain dead, the estate's security crumbles.\n";
            std::cout << "  No one will investigate... for now.\n";
            state.player.suspicion = std::max(0, state.player.suspicion - 10);
        }
        advanceTime(state, 10);
        std::cout << "\n  You stand over the body, breathing heavily.\n";
        std::cout << "  You should leave this room. The body may be found.\n";
        std::cout << "  [!] The " << weapon_name << " is stained with blood.\n";
    }
}
