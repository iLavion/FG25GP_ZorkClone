#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace
{
    std::unordered_map<std::string, std::vector<RoomAction>> s_roomActions;
}

void registerRoomActions(const std::string &room_id, std::vector<RoomAction> actions)
{
    auto &existing = s_roomActions[room_id];
    for (auto &action : actions)
    {
        existing.push_back(action);
    }
}

static std::vector<const RoomAction *> getVisibleActions(const GameState &state)
{
    std::vector<const RoomAction *> visible;
    const std::string &room_id = state.player.current_room;

    if (s_roomActions.count(room_id))
    {
        for (const auto &action : s_roomActions.at(room_id))
        {
            if (!action.condition || action.condition(state))
            {
                visible.push_back(&action);
            }
        }
    }
    return visible;
}

static std::vector<std::pair<Direction, std::string>> getNavExits(const GameState &state)
{
    std::vector<std::pair<Direction, std::string>> exits;
    if (state.player.room_state != "standing")
    {
        return exits;
    }
    const Room &room = state.rooms.at(state.player.current_room);
    for (const auto &exit : room.exits)
    {
        if (state.rooms.count(exit.second))
        {
            exits.push_back({exit.first, exit.second});
        }
    }
    return exits;
}

void showRoomChoices(const GameState &state)
{
    auto actions = getVisibleActions(state);
    auto exits = getNavExits(state);
    if (actions.empty() && exits.empty())
    {
        return;
    }
    int idx = 1;
    for (const auto *action : actions)
    {
        std::cout << "  " << colored(std::to_string(idx++) + ") " + action->text, ansi::BRIGHT_CYAN) << "\n";
    }
    for (const auto &exit : exits)
    {
        std::string label = std::to_string(idx++) + ") Go to the " +
                            state.rooms.at(exit.second).name +
                            " (" + direction_to_string(exit.first) + ")";
        std::cout << "  " << colored(label, ansi::BRIGHT_CYAN) << "\n";
    }
    std::cout << "\n";
}

void cmdChoose(GameState &state, const std::string &args)
{
    int choice_num = 0;
    try
    {
        choice_num = std::stoi(args);
    }
    catch (...)
    {
        std::cout << "Enter a number to make a choice.\n";
        return;
    }
    auto actions = getVisibleActions(state);
    auto exits = getNavExits(state);
    int total = static_cast<int>(actions.size() + exits.size());
    if (choice_num < 1 || choice_num > total)
    {
        if (total == 0)
        {
            std::cout << "There are no choices available right now.\n";
        }
        else
        {
            std::cout << "Invalid choice. Enter 1-" << total << ".\n";
        }
        return;
    }
    int action_count = static_cast<int>(actions.size());
    if (choice_num <= action_count)
    {
        actions[choice_num - 1]->effect(state);
    }
    else
    {
        int nav_idx = choice_num - action_count - 1;
        Direction dir = exits[nav_idx].first;
        std::string target_id = exits[nav_idx].second;
        moveToRoom(state, target_id, dir);
    }
}
