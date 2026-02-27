#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void tickStatus(GameState &state)
{
    state.player.turn_count++;
    state.player.turns_without_eating++;
    state.player.turns_without_sleeping++;

    if (state.player.turns_without_eating > 15)
    {
        state.player.hunger = std::max(0, state.player.hunger - 2);
    }

    if (state.player.turns_without_sleeping > 20)
    {
        state.player.energy = std::max(0, state.player.energy - 2);
    }

    if (state.quest.met_elena && !state.quest.elena_dead &&
        state.npcs.count("elena") && state.npcs.at("elena").suspicion >= 25)
    {

        if (!state.quest.elena_retaliating)
        {
            state.quest.elena_retaliating = true;
            std::cout << "\n"
                      << colored("  [!] Elena has noticed your hostility. She is now actively working", ansi::BRIGHT_YELLOW) << "\n";
            std::cout << colored("      to strengthen her position among the nobles.", ansi::BRIGHT_YELLOW) << "\n\n";
        }

        if (state.player.turn_count % 12 == 0)
        {
            state.quest.elena_retaliation_count++;
            int gain = 3;
            if (state.npcs.at("elena").suspicion >= 50)
            {
                gain = 5;
            }
            state.heroine_popularity = std::min(100, state.heroine_popularity + gain);

            if (state.quest.elena_retaliation_count % 3 == 0)
            {
                std::cout << colored("  [!] Word reaches you that Elena has been charming more nobles.", ansi::BRIGHT_YELLOW) << "\n";
                std::cout << colored("      Her popularity grows. (" + std::to_string(state.heroine_popularity) + "/100)", ansi::BRIGHT_YELLOW) << "\n\n";
            }
        }
    }

    if (state.player.hunger <= 20 && state.player.hunger > 0)
    {
        std::cout << colored("  [!] You feel faint from hunger. You should EAT something.", ansi::YELLOW) << "\n";
    }
    else if (state.player.hunger == 0)
    {
        std::cout << colored("  [!!] You are starving! Your energy drains faster.", ansi::BRIGHT_RED) << "\n";
        state.player.energy = std::max(0, state.player.energy - 2);
    }

    if (state.player.energy <= 20 && state.player.energy > 0)
    {
        std::cout << colored("  [!] You are exhausted. Find a bed and SLEEP.", ansi::YELLOW) << "\n";
    }
    else if (state.player.energy == 0 && state.player.hunger > 0)
    {
        std::cout << colored("  [!!] You collapse from exhaustion!", ansi::BRIGHT_RED) << "\n";

        bool npc_found = false;
        const Room &collapse_room = state.rooms.at(state.player.current_room);
        for (const auto &npc_id : collapse_room.npc_ids)
        {
            if (state.npcs.count(npc_id) && state.npcs.at(npc_id).alive)
            {
                const NPC &helper = state.npcs.at(npc_id);
                std::cout << colored("  " + helper.name + " shakes you awake.", ansi::YELLOW) << "\n";
                std::cout << colored("  \"My lady! You must take better care of yourself!\"", ansi::YELLOW) << "\n";
                advanceTime(state, 60);
                state.player.energy = 15;
                state.player.turns_without_sleeping = 0;
                npc_found = true;
                break;
            }
        }

        if (!npc_found)
        {
            std::cout << colored("  You crumple to the ground, alone. Hours pass...", ansi::RED) << "\n";
            int sleep_minutes = 120 + (state.player.turn_count % 3) * 60;
            advanceTime(state, sleep_minutes);
            state.player.energy = 10;
            state.player.turns_without_sleeping = 0;
            std::cout << colored("  You stir awake, cold and aching on the floor.", ansi::YELLOW) << "\n";
            std::cout << "  It is now " << timeToString(state.hour, state.minute) << ".\n";
            state.heroine_popularity = std::min(100, state.heroine_popularity + 2);
            std::cout << colored("  [i] Time has passed. Elena's influence may have grown.", ansi::CYAN) << "\n";
        }
    }

    if (state.quest.elena_drank_tea && !state.quest.elena_dead)
    {
        state.quest.elena_dead = true;
        state.npcs["elena"].alive = false;
        state.heroine_popularity = 0;
        delay_ms(500);
        std::cout << "\n"
                  << colored("  *** A terrible scream echoes through the estate! ***", ansi::BRIGHT_RED) << "\n";
        print_narrative("  News spreads quickly: Elena has collapsed.", 400);
        print_narrative("  You feel a chill run down your spine.", 300);
        std::cout << "\n";
    }

    if (state.quest.elena_dead && !state.quest.body_hidden && !state.quest.hidden_bodies.count("elena") && state.player.turn_count % 15 == 0)
    {
        if (!state.quest.body_discovered)
        {
            state.quest.body_discovered = true;
            delay_ms(500);
            std::cout << "\n"
                      << colored("  *** The body has been discovered! ***", ansi::BRIGHT_RED) << "\n";
            print_narrative("  Captain Roderick is launching an investigation.", 400);
        }
    }

    if (!state.quest.dead_bodies.empty() && state.player.turn_count % 20 == 0)
    {
        for (const auto &body : state.quest.dead_bodies)
        {
            const std::string &dead_id = body.first;
            const std::string &body_room = body.second;

            if (state.quest.welfare_checked.count(dead_id))
            {
                continue;
            }

            if (state.quest.hidden_bodies.count(dead_id))
            {
                continue;
            }

            if (!state.npcs.count(dead_id))
            {
                continue;
            }

            const NPC &dead_npc = state.npcs.at(dead_id);
            for (const auto &associate_id : dead_npc.associates)
            {
                if (!state.npcs.count(associate_id) || !state.npcs.at(associate_id).alive)
                {
                    continue;
                }

                const NPC &checker = state.npcs.at(associate_id);
                state.quest.welfare_checked.insert(dead_id);

                delay_ms(400);
                std::cout << "\n"
                          << colored("  *** " + checker.name + " went looking for " + dead_npc.name + "... ***", ansi::BRIGHT_RED) << "\n";

                if (body_room == state.player.current_room)
                {
                    print_narrative("  They arrive at the " + state.rooms.at(body_room).name + " and find you standing over the body!", 400);
                    state.quest.murder_witnessed = true;
                    state.npcs[associate_id].disposition = Disposition::Hostile;
                    state.npcs[associate_id].suspicion = 100;
                }
                else
                {
                    print_narrative("  They found the body in the " + state.rooms.at(body_room).name + ".", 400);
                    print_narrative("  Word will spread quickly. An investigation begins.", 300);

                    if (dead_id == "elena" && !state.quest.body_discovered)
                    {
                        state.quest.body_discovered = true;
                    }

                    for (const auto &assoc_of_checker : checker.associates)
                    {
                        if (state.npcs.count(assoc_of_checker) && state.npcs.at(assoc_of_checker).alive)
                        {
                            state.npcs[assoc_of_checker].suspicion = std::min(100, state.npcs[assoc_of_checker].suspicion + 15);
                        }
                    }
                }
                break;
            }
        }
    }

    if (state.player.hunger <= 0 && state.player.energy <= 0 && !state.quest.starvation_warning)
    {
        state.quest.starvation_warning = true;
        std::cout << "\n"
                  << colored("  [!!] You collapse to the ground from starvation!", ansi::BRIGHT_RED) << "\n";
        std::cout << colored("  Your vision darkens...", ansi::RED) << "\n\n";

        bool rescued = false;
        const Room &room = state.rooms.at(state.player.current_room);
        for (const auto &npc_id : room.npc_ids)
        {
            if (state.npcs.count(npc_id) && state.npcs.at(npc_id).alive &&
                state.npcs.at(npc_id).affection >= 40)
            {
                const NPC &helper = state.npcs.at(npc_id);
                std::cout << colored("  " + helper.name + " rushes to your side!", ansi::BRIGHT_YELLOW) << "\n";
                std::cout << colored("  \"My lady! Stay with me!\"", ansi::YELLOW) << "\n";
                std::cout << colored("  They help you sit up and bring you a bit of water.", ansi::YELLOW) << "\n\n";
                state.player.energy = 10;
                state.player.hunger = 10;
                rescued = true;
                break;
            }
        }

        if (!rescued)
        {
            std::cout << colored("  No one is here to help you...", ansi::RED) << "\n";
            state.player.energy = 5;
            state.player.hunger = 5;
            std::cout << colored("  You muster the last of your strength to stay conscious.", ansi::YELLOW) << "\n";
            std::cout << colored("  Find food immediately, or this will be your end.", ansi::BRIGHT_RED) << "\n\n";
        }
    }

    if (state.quest.starvation_warning && state.player.hunger <= 0 && state.player.energy <= 0)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::RED) << "\n";
        print_narrative("Your body can take no more. The great Lady Seraphina,");
        print_narrative("daughter of Duke Aldric, collapses in the " +
                        state.rooms.at(state.player.current_room).name + ".");
        print_narrative("No schemes, no plots, no villainy. Just hunger and neglect.");
        print_narrative("They find you cold and still the next morning.");
        std::cout << colored("  ** ENDING: Starved to Death **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    if (state.game_over)
    {
        return;
    }

    if (state.heroine_popularity >= 90)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::RED) << "\n";
        print_narrative("Elena's popularity has reached a tipping point! The nobility");
        print_narrative("turns against your family. A conspiracy unfolds...");
        std::cout << colored("  ** ENDING: The Villainess Falls **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    if (state.quest.elena_dead && (state.quest.body_hidden || state.quest.hidden_bodies.count("elena")))
    {
        bool all_hidden = true;
        for (const auto &entry : state.quest.dead_bodies)
        {
            if (!state.quest.hidden_bodies.count(entry.first))
            {
                all_hidden = false;
                break;
            }
        }
        if (all_hidden)
        {
            std::cout << "\n"
                      << colored("============================================================", ansi::GREEN) << "\n";
            print_narrative("Elena has vanished without a trace. The Prince mourns, the");
            print_narrative("nobles gossip, but no one suspects you. Your family's position");
            print_narrative("is secure. You sip your tea calmly.");
            std::cout << colored("  ** ENDING: The Perfect Villainess **", ansi::BRIGHT_WHITE) << "\n";
            std::cout << colored("============================================================", ansi::GREEN) << "\n";
            state.game_over = true;
            return;
        }
    }

    if (state.quest.elena_dead && state.quest.body_discovered)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::RED) << "\n";
        print_narrative("The evidence points to you. Captain Roderick arrives at your");
        print_narrative("door with guards. \"" + playerDisplayName(state) + ", you are under arrest for");
        print_narrative("the murder of Elena.\" Your father cannot protect you now.");
        std::cout << colored("  ** ENDING: The Villainess Condemned **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    if (state.quest.murder_witnessed)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::BRIGHT_RED) << "\n";
        print_narrative("Screams echo through the estate! Guards swarm the corridors.");
        print_narrative("Captain Roderick corners you, blade drawn. \"You MONSTER.");
        print_narrative(playerDisplayName(state) + ", you are a murderer, and there are witnesses.\"");
        print_narrative("Your father disowns you. The executioner awaits.");
        std::cout << colored("  ** ENDING: The Bloodstained Villainess **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::BRIGHT_RED) << "\n";
        state.game_over = true;
        return;
    }

    if (!state.quest.elena_dead && state.heroine_popularity <= 20)
    {
        int high_affection_count = 0;
        for (const auto &pair : state.npcs)
        {
            if (pair.second.alive && !pair.second.is_heroine && pair.second.affection >= 70)
            {
                high_affection_count++;
            }
        }
        if (high_affection_count >= 5)
        {
            std::cout << "\n"
                      << colored("============================================================", ansi::BRIGHT_GREEN) << "\n";
            print_narrative("Your grace, poise, and cunning have won the day. The nobles");
            print_narrative("fawn over " + playerDisplayName(state) + " while Elena fades into obscurity.");
            print_narrative("The Prince himself sends flowers, to YOU.");
            std::cout << colored("  ** ENDING: The True Noblewoman **", ansi::BRIGHT_WHITE) << "\n";
            std::cout << colored("============================================================", ansi::BRIGHT_GREEN) << "\n";
            state.game_over = true;
            return;
        }
    }

    if (state.quest.elena_expelled && !state.quest.elena_dead)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::BRIGHT_YELLOW) << "\n";
        print_narrative("Armed with evidence of Elena's true motives, Duke Aldric");
        print_narrative("banishes her from the estate. She leaves with nothing but");
        print_narrative("the clothes on her back. The threat is over, for now.");
        std::cout << colored("  ** ENDING: Exposed and Expelled **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::BRIGHT_YELLOW) << "\n";
        state.game_over = true;
        return;
    }
}