#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void cmdTalk(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Talk to whom? Specify an NPC name.\n";
        return;
    }
    std::string npc_id = findNPCInRoom(state, args);
    if (npc_id.empty())
    {
        std::cout << "There's no one called \"" << args << "\" here.\n";
        return;
    }
    const NPC &npc = state.npcs.at(npc_id);
    if (!npc.alive)
    {
        std::cout << npc.name << " is... no longer able to converse.\n";
        return;
    }
    std::string root = npc.dialogue_root;
    if (!state.dialogue_nodes.count(root))
    {
        std::cout << npc.name << " has nothing to say right now.\n";
        return;
    }
    state.in_dialogue = true;
    state.current_dialogue_node = root;
    state.talking_to_npc = npc_id;
    advanceTime(state, 3);
    std::cout << "\n"
              << colored("--- Conversation with " + npc.name + " ---", ansi::YELLOW) << "\n\n";
    const DialogueNode &node = state.dialogue_nodes.at(root);
    std::cout << colored(node.speaker + ": ", ansi::YELLOW) << node.text << "\n";

    delay_ms(1250);
    std::cout << "\n";
    int idx = 1;
    for (const auto &choice : node.choices)
    {
        if (!choice.condition || choice.condition(state))
        {
            std::cout << "  " << colored(std::to_string(idx++) + ") " + choice.text, ansi::BRIGHT_CYAN) << "\n";
        }
    }
    std::cout << dim("\nEnter a number to choose (or 0 to leave):") << "\n";
}
