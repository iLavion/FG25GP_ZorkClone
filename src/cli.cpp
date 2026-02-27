#include "cli.hpp"
#include "game.hpp"
#include "commands/handlers.hpp"
#include "utilities/string.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

void registerCommands(Game &game)
{
    auto &cmds = game.commands;

    cmds.push_back({"look", "Describe the current room, NPCs, and items.", false, [](GameState &s, const std::string &a)
                    { cmdLook(s, a); }});
    cmds.push_back({"go", "Move to an adjacent room (direction).", true, [](GameState &s, const std::string &a)
                    { cmdGo(s, a); }});
    cmds.push_back({"talk", "Initiate dialogue with an NPC.", true, [](GameState &s, const std::string &a)
                    { cmdTalk(s, a); }});
    cmds.push_back({"pickup", "Pick up an item from the room.", true, [](GameState &s, const std::string &a)
                    { cmdPickup(s, a); }});
    cmds.push_back({"drop", "Drop an item from your inventory.", true, [](GameState &s, const std::string &a)
                    { cmdDrop(s, a); }});
    cmds.push_back({"use", "Use an item from your inventory.", true, [](GameState &s, const std::string &a)
                    { cmdUse(s, a); }});
    cmds.push_back({"inventory", "List your inventory.", false, [](GameState &s, const std::string &a)
                    { cmdInventory(s, a); }});
    cmds.push_back({"eat", "Eat a food item to restore hunger.", true, [](GameState &s, const std::string &a)
                    { cmdEat(s, a); }});
    cmds.push_back({"sleep", "Sleep to restore energy (bedroom only).", false, [](GameState &s, const std::string &a)
                    { cmdSleep(s, a); }});
    cmds.push_back({"plot", "Scheme against the heroine (context-sensitive).", false, [](GameState &s, const std::string &a)
                    { cmdPlot(s, a); }});
    cmds.push_back({"hire", "Hire an NPC to do your bidding.", true, [](GameState &s, const std::string &a)
                    { cmdHire(s, a); }});
    cmds.push_back({"read", "Read a book or document (gain skills!).", true, [](GameState &s, const std::string &a)
                    { cmdRead(s, a); }});
    cmds.push_back({"write", "Write a letter at your desk (bedroom only).", false, [](GameState &s, const std::string &a)
                    { cmdWrite(s, a); }});
    cmds.push_back({"search", "Search the room thoroughly for hidden items.", false, [](GameState &s, const std::string &a)
                    { cmdSearch(s, a); }});
    cmds.push_back({"kill", "Attempt to kill an NPC (requires a weapon).", true, [](GameState &s, const std::string &a)
                    { cmdKill(s, a); }});
    cmds.push_back({"inspect", "Inspect an item closely for details.", true, [](GameState &s, const std::string &a)
                    { cmdInspect(s, a); }});
    cmds.push_back({"status", "Show your stats, skills, and Elena's popularity.", false, [](GameState &s, const std::string &a)
                    { cmdStatus(s, a); }});
    cmds.push_back({"log", "Show all commands entered this session.", false, [](GameState &s, const std::string &a)
                    { cmdLog(s, a); }});
    cmds.push_back({"commands", "Show all available commands.", false, [](GameState &s, const std::string &a)
                    { cmdCommands(s, a); }});
    cmds.push_back({"help", "Show gameplay tips and information.", false, [](GameState &s, const std::string &a)
                    { cmdHelp(s, a); }});
    cmds.push_back({"quit", "Quit the game.", false, [](GameState &s, const std::string &a)
                    { (void)s; (void)a; }});
    cmds.push_back({"undo", "Rewind to the previous game state.", false, [](GameState &s, const std::string &a)
                    { (void)s; (void)a; }});
}

void procDialogueInput(Game &game, const std::string &input)
{
    GameState &state = game.state;

    int choice_num = 0;
    try
    {
        choice_num = std::stoi(input);
    }
    catch (...)
    {
        std::cout << "Enter a number to choose (or 0 to leave the conversation).\n";
        return;
    }

    if (choice_num == 0)
    {
        std::cout << "\nYou end the conversation.\n\n";
        state.in_dialogue = false;
        state.current_dialogue_node = "";
        state.talking_to_npc = "";
        return;
    }

    if (!state.dialogue_nodes.count(state.current_dialogue_node))
    {
        state.in_dialogue = false;
        return;
    }

    const DialogueNode &node = state.dialogue_nodes.at(state.current_dialogue_node);

    std::vector<int> visible_indices;
    for (int i = 0; i < static_cast<int>(node.choices.size()); i++)
    {
        if (!node.choices[i].condition || node.choices[i].condition(state))
        {
            visible_indices.push_back(i);
        }
    }

    if (choice_num < 1 || choice_num > static_cast<int>(visible_indices.size()))
    {
        std::cout << "Invalid choice. Enter 1-" << visible_indices.size() << " or 0 to leave.\n";
        return;
    }

    int actual_idx = visible_indices[choice_num - 1];
    const DialogueChoice &chosen = node.choices[actual_idx];

    delay_ms(500);
    std::cout << "\n"
              << playerDisplayName(state) << ": " << chosen.text << "\n";

    advanceTime(state, 2);

    if (chosen.effect)
    {
        chosen.effect(state);
    }

    if (chosen.next_node.empty() || !state.dialogue_nodes.count(chosen.next_node))
    {
        delay_ms(1250);
        print_narrative(dim("The conversation ends."), 400);
        std::cout << "\n";
        state.in_dialogue = false;
        state.current_dialogue_node = "";
        state.talking_to_npc = "";
        return;
    }

    const DialogueNode &next = state.dialogue_nodes.at(chosen.next_node);
    state.current_dialogue_node = chosen.next_node;

    delay_ms(1250);
    std::cout << "\n"
              << colored(next.speaker + ": ", ansi::YELLOW) << next.text << "\n";

    if (next.is_end)
    {
        if (!next.choices.empty())
        {
            const auto &final_choice = next.choices[0];
            if (final_choice.effect)
            {
                final_choice.effect(state);
            }
        }
        delay_ms(1250);
        print_narrative(dim("The conversation ends."), 400);
        std::cout << "\n";
        state.in_dialogue = false;
        state.current_dialogue_node = "";
        state.talking_to_npc = "";
        return;
    }

    delay_ms(1250);
    std::cout << "\n";
    int idx = 1;
    for (const auto &c : next.choices)
    {
        if (!c.condition || c.condition(state))
        {
            std::cout << "  " << colored(std::to_string(idx++) + ") " + c.text, ansi::BRIGHT_CYAN) << "\n";
        }
    }
    std::cout << dim("\nEnter a number to choose (or 0 to leave):") << "\n";
}

void procInput(Game &game, const std::string &input)
{
    std::string cleaned = to_lower(to_trim(input));
    if (cleaned.empty())
    {
        return;
    }

    logCommand(input);

    if (game.state.in_dialogue)
    {
        procDialogueInput(game, cleaned);
        if (!game.state.in_dialogue)
        {
            showRoomChoices(game.state);
        }
        return;
    }

    if (!cleaned.empty() &&
        std::all_of(cleaned.begin(), cleaned.end(), ::isdigit))
    {
        game.undo_stack.push_back(game.state);
        if (game.undo_stack.size() > 50)
        {
            game.undo_stack.erase(game.undo_stack.begin());
        }

        cmdChoose(game.state, cleaned);
        tickStatus(game.state);
        showRoomChoices(game.state);
        return;
    }

    std::string verb;
    std::string args;
    auto space_pos = cleaned.find(' ');
    if (space_pos != std::string::npos)
    {
        verb = cleaned.substr(0, space_pos);
        args = to_trim(cleaned.substr(space_pos + 1));
    }
    else
    {
        verb = cleaned;
    }

    if (verb == "quit" || verb == "exit")
    {
        stopGame(game, args);
        return;
    }

    if (verb == "undo")
    {
        if (game.undo_stack.empty())
        {
            std::cout << "Nothing to undo.\n";
        }
        else
        {
            game.state = game.undo_stack.back();
            game.undo_stack.pop_back();
            std::cout << "Undone! You are back in: " << game.state.rooms.at(game.state.player.current_room).name << "\n";
        }
        return;
    }

    game.undo_stack.push_back(game.state);
    if (game.undo_stack.size() > 50)
    {
        game.undo_stack.erase(game.undo_stack.begin());
    }

    for (const auto &cmd : game.commands)
    {
        if (cmd.verb == verb)
        {
            cmd.handler(game.state, args);
            if (!game.state.in_dialogue)
            {
                tickStatus(game.state);
                showRoomChoices(game.state);
            }
            return;
        }
    }

    if (verb == "n" || verb == "s" || verb == "e" || verb == "w" || verb == "u" || verb == "d" ||
        verb == "north" || verb == "south" || verb == "east" || verb == "west" ||
        verb == "up" || verb == "down")
    {
        cmdGo(game.state, verb);
        tickStatus(game.state);
        showRoomChoices(game.state);
        return;
    }

    std::cout << "I don't understand \"" << input << "\". Type COMMANDS for a list of actions.\n";
}