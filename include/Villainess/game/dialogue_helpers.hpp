#pragma once

#include "game.hpp"
#include <string>
#include <vector>
#include <utility>

inline void addNode(
    GameState &state,
    const std::string &id, const std::string &speaker,
    const std::string &text, std::vector<DialogueChoice> choices,
    bool isEnd = false)
{
    DialogueNode node;
    node.id = id;
    node.speaker = speaker;
    node.text = text;
    node.choices = std::move(choices);
    node.is_end = isEnd;
    state.dialogue_nodes[id] = node;
}
