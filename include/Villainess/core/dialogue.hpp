#pragma once

#include <string>
#include <vector>
#include <functional>

struct GameState;

struct DialogueChoice
{
    std::string text;
    std::string next_node;
    std::function<bool(const GameState &)> condition = nullptr;
    std::function<void(GameState &)> effect = nullptr;
};

struct DialogueNode
{
    std::string id;
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;
    bool is_end = false;
};