#include "commands/handlers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void cmdStatus(GameState &state, const std::string &)
{
    std::cout << "\n"
              << colored("--- " + state.player.name + "'s Status ---", ansi::BRIGHT_CYAN) << "\n";
    std::cout << "  Day: " << state.day << "  |  Time: " << timeToString(state.hour, state.minute)
              << "  |  Turn: " << state.player.turn_count << "\n";
    std::cout << "  Location: " << colored(state.rooms.at(state.player.current_room).name, ansi::BRIGHT_CYAN) << "\n";
    std::cout << "  Hunger:     " << state.player.hunger << "/100";
    if (state.player.hunger <= 20)
    {
        std::cout << colored("  [LOW!]", ansi::BRIGHT_RED);
    }
    std::cout << "\n";
    std::cout << "  Energy:     " << state.player.energy << "/100";
    if (state.player.energy <= 20)
    {
        std::cout << colored("  [LOW!]", ansi::BRIGHT_RED);
    }
    std::cout << "\n";
    std::cout << "  Suspicion:  " << state.player.suspicion << "/100";
    if (state.player.suspicion >= 50)
    {
        std::cout << colored("  [DANGEROUS]", ansi::BRIGHT_RED);
    }
    std::cout << "\n";
    std::cout << "  Reputation: " << state.player.reputation << "/100\n";
    std::cout << "  Gold:       " << state.player.gold << "\n";

    if (!state.player.skills.empty())
    {
        std::cout << "\n"
                  << colored("  ~ Skills ~", ansi::BRIGHT_YELLOW) << "\n";
        for (const auto &pair : state.player.skills)
        {
            std::cout << "  " << pair.first << ": " << pair.second << "\n";
        }
    }

    std::cout << "\n"
              << colored("  ~ The Heroine ~", ansi::BRIGHT_MAGENTA) << "\n";
    std::cout << "  Elena's Popularity: " << state.heroine_popularity << "/100";
    if (state.heroine_popularity >= 70)
    {
        std::cout << colored("  [CRITICAL!]", ansi::BRIGHT_RED);
    }
    if (state.quest.elena_dead)
    {
        std::cout << colored("  [DECEASED]", ansi::RED);
    }
    std::cout << "\n\n";
}

void cmdLog(GameState &, const std::string &)
{
    auto log = getCommandLog();
    if (log.empty())
    {
        std::cout << "No commands have been logged yet.\n";
        return;
    }

    std::cout << "\n--- Command Log ---\n";
    int num = 1;
    for (const auto &cmd : log)
    {
        std::cout << "  " << num++ << ". " << cmd << "\n";
    }
    std::cout << "\n";
}

void cmdCommands(GameState &, const std::string &)
{
    std::cout << "\n--- Available Commands ---\n";
    std::cout << "  LOOK              - Describe the current room, NPCs, and items.\n";
    std::cout << "  GO <direction>    - Move (north, south, east, west, up, down).\n";
    std::cout << "  TALK <npc>        - Initiate dialogue with an NPC.\n";
    std::cout << "  PICKUP <item>     - Pick up an item from the room.\n";
    std::cout << "  DROP <item>       - Drop an item from your inventory.\n";
    std::cout << "  USE <item>        - Use an item from your inventory.\n";
    std::cout << "  READ <item>       - Read a book or document (gain skills!).\n";
    std::cout << "  WRITE             - Write a letter at your desk (bedroom only).\n";
    std::cout << "  INVENTORY         - List your inventory.\n";
    std::cout << "  EAT <item>        - Eat a food item to restore hunger.\n";
    std::cout << "  SLEEP             - Sleep to restore energy (bedroom only).\n";
    std::cout << "  PLOT              - Scheme against the heroine (context-sensitive).\n";
    std::cout << "  HIRE <npc>        - Hire someone to do your bidding.\n";
    std::cout << "  SEARCH            - Search the room thoroughly for hidden items.\n";
    std::cout << "  KILL <npc>        - Attempt to kill an NPC (requires a weapon).\n";
    std::cout << "  INSPECT <item>    - Inspect an item closely for details.\n";
    std::cout << "  STATUS            - Show your stats, skills, and Elena's popularity.\n";
    std::cout << "  LOG               - Show all commands entered this session.\n";
    std::cout << "  UNDO              - Rewind to the previous game state.\n";
    std::cout << "  COMMANDS          - Show this list.\n";
    std::cout << "  HELP              - Show gameplay tips.\n";
    std::cout << "  QUIT              - Quit the game.\n";
    std::cout << "\n  Navigation: north/n, south/s, east/e, west/w, up/u, down/d\n";
    std::cout << "  You can also type: GO TO <room name>  (e.g. 'go to hallway')\n";
    std::cout << "  Or simply enter a number to choose from the options shown.\n\n";
}

void cmdHelp(GameState &state, const std::string &)
{
    std::cout << "\n--- Help: Villainess of the Empire ---\n\n";
    std::cout << "You are " << state.player.name << ", the villainess. Your goal is to end the\n";
    std::cout << "heroine Elena's rising popularity before it destroys your family.\n\n";
    std::cout << "KEY MECHANICS:\n";
    std::cout << "  - Numbered choices appear after actions. Type a number to choose.\n";
    std::cout << "  - Move with GO <direction>, GO TO <room name>, or pick a number.\n";
    std::cout << "  - Elena's Popularity rises over time. If it hits 90, you lose.\n";
    std::cout << "  - Your Suspicion rises when you do shady things. At 80, you're caught.\n";
    std::cout << "  - Time passes as you move and act. NPCs follow daily schedules.\n";
    std::cout << "  - NPC schedules are influenced by traits (EarlyBird, NightOwl, etc.)\n";
    std::cout << "  - Check the DUTY ROSTER in the Servants' Quarters to see staff schedules.\n";
    std::cout << "  - READ books in the library to gain skills (alchemy, stealth, etc.).\n";
    std::cout << "  - TALK to NPCs to gather info, form alliances, and hire help.\n";
    std::cout << "  - PICKUP items and USE them strategically.\n";
    std::cout << "  - INSPECT items for detailed lore and properties.\n";
    std::cout << "  - EAT food and SLEEP regularly, or you'll get status effects.\n";
    std::cout << "  - PLOT to see your scheming options and quest progress.\n";
    std::cout << "  - HIRE servants to spread rumors, sabotage, or spy.\n";
    std::cout << "  - Each room has contextual interactions, explore everywhere!\n\n";
    std::cout << "THE POISON TEA PLOT:\n";
    std::cout << "  1. Talk to Duke Aldric about inviting Elena\n";
    std::cout << "  2. WRITE the invitation in your bedroom\n";
    std::cout << "  3. Talk to Elena or have Graves deliver the letter\n";
    std::cout << "  4. Acquire poison (cellar vial or garden nightshade)\n";
    std::cout << "  5. Get the tea set from the kitchen\n";
    std::cout << "  6. USE poison in the kitchen to lace the tea\n";
    std::cout << "  7. USE tea_set in the dining room when Elena is there\n\n";
    std::cout << "TIPS:\n";
    std::cout << "  - Be careful who sees you with suspicious items.\n";
    std::cout << "  - SEARCH rooms to find hidden items (especially in the Kitchen).\n";
    std::cout << "  - You can KILL NPCs if you have a weapon, but beware witnesses!\n";
    std::cout << "  - Killing with no witnesses = low suspicion. With witnesses = game over.\n";
    std::cout << "  - Strong NPCs fight back. Perceptive NPCs notice your approach.\n";
    std::cout << "  - NPCs are unaware at night; use the sleeping draught for stealth.\n";
    std::cout << "  - USE the iron key on the kitchen cabinet to unlock supplies.\n";
    std::cout << "  - Your family members can help or hinder you.\n";
    std::cout << "  - NPCs move on schedules, learn their routines.\n";
    std::cout << "  - Each room has unique interactions. Explore and experiment!\n";
    std::cout << "  - There are multiple endings based on your choices.\n";
    std::cout << "  - Use UNDO if you make a mistake.\n\n";
}

void cmdUndo(GameState &, const std::string &)
{
    std::cout << "Undo not available here.\n";
}
