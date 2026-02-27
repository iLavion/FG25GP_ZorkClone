#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void tickStatus(GameState &state)
{
    state.player.turn_count++;
    state.player.turns_without_eating++;
    state.player.turns_without_sleeping++;

    if (state.player.turns_without_eating > 5)
    {
        state.player.hunger = std::max(0, state.player.hunger - 5);
    }

    if (state.player.turns_without_sleeping > 10)
    {
        state.player.energy = std::max(0, state.player.energy - 3);
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
        state.player.energy = std::max(0, state.player.energy - 5);
    }

    if (state.player.energy <= 20 && state.player.energy > 0)
    {
        std::cout << colored("  [!] You are exhausted. Find a bed and SLEEP.", ansi::YELLOW) << "\n";
    }
    else if (state.player.energy == 0)
    {
        std::cout << colored("  [!!] You collapse from exhaustion!", ansi::BRIGHT_RED) << "\n";
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

    if (state.quest.elena_dead && !state.quest.body_hidden && state.player.turn_count % 15 == 0)
    {
        if (!state.quest.body_discovered)
        {
            state.quest.body_discovered = true;
            delay_ms(500);
            std::cout << "\n"
                      << colored("  *** The body has been discovered! ***", ansi::BRIGHT_RED) << "\n";
            print_narrative("  Captain Roderick is launching an investigation.", 400);
            state.player.suspicion += 15;
        }
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
        std::cout << colored("  ** ENDING: The Villainess Falls **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    if (state.player.suspicion >= 80)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::RED) << "\n";
        print_narrative("Your schemes have been discovered! Duke Aldric has no choice");
        print_narrative("but to punish you to save the family's honor.");
        std::cout << colored("  ** ENDING: Exiled in Disgrace **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    if (state.quest.elena_dead && state.quest.body_hidden && state.player.suspicion < 30)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::GREEN) << "\n";
        print_narrative("Elena has vanished without a trace. The Prince mourns, the");
        print_narrative("nobles gossip, but no one suspects you. Your family's position");
        print_narrative("is secure. You sip your tea calmly.");
        std::cout << colored("  ** ENDING: The Perfect Villainess **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::GREEN) << "\n";
        state.game_over = true;
        return;
    }

    if (state.quest.elena_dead && state.quest.body_discovered && state.player.suspicion >= 60)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::RED) << "\n";
        print_narrative("The evidence points to you. Captain Roderick arrives at your");
        print_narrative("door with guards. \"" + playerDisplayName(state) + ", you are under arrest for");
        print_narrative("the murder of Elena.\" Your father cannot protect you now.");
        std::cout << colored("  ** ENDING: The Villainess Condemned **", ansi::BOLD) << "\n";
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
        std::cout << colored("  ** ENDING: The Bloodstained Villainess **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::BRIGHT_RED) << "\n";
        state.game_over = true;
        return;
    }

    if (!state.quest.elena_dead && state.player.reputation >= 95 &&
        state.heroine_popularity <= 20 && state.player.suspicion < 30)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::BRIGHT_GREEN) << "\n";
        print_narrative("Your grace, poise, and cunning have won the day. The nobles");
        print_narrative("fawn over " + playerDisplayName(state) + " while Elena fades into obscurity.");
        print_narrative("The Prince himself sends flowers, to YOU.");
        std::cout << colored("  ** ENDING: The True Noblewoman **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::BRIGHT_GREEN) << "\n";
        state.game_over = true;
        return;
    }

    if (state.quest.elena_expelled && !state.quest.elena_dead)
    {
        std::cout << "\n"
                  << colored("============================================================", ansi::BRIGHT_YELLOW) << "\n";
        print_narrative("Armed with evidence of Elena's true motives, Duke Aldric");
        print_narrative("banishes her from the estate. She leaves with nothing but");
        print_narrative("the clothes on her back. The threat is over, for now.");
        std::cout << colored("  ** ENDING: Exposed and Expelled **", ansi::BOLD) << "\n";
        std::cout << colored("============================================================", ansi::BRIGHT_YELLOW) << "\n";
        state.game_over = true;
        return;
    }
}
