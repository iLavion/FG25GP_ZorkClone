#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include "utilities/string.hpp"
#include "utilities/text.hpp"
#include <iostream>

static void printHUD(const GameState &state)
{
    std::string hunger_color = ansi::GREEN;
    if (state.player.hunger <= 20)
    {
        hunger_color = ansi::BRIGHT_RED;
    }
    else if (state.player.hunger <= 50)
    {
        hunger_color = ansi::YELLOW;
    }

    std::string energy_color = ansi::GREEN;
    if (state.player.energy <= 20)
    {
        energy_color = ansi::BRIGHT_RED;
    }
    else if (state.player.energy <= 50)
    {
        energy_color = ansi::YELLOW;
    }

    std::cout << dim("[ ")
              << colored("Hunger " + std::to_string(state.player.hunger), hunger_color.c_str())
              << dim(" | ")
              << colored("Energy " + std::to_string(state.player.energy), energy_color.c_str())
              << dim(" | ")
              << colored("Gold " + std::to_string(state.player.gold), ansi::YELLOW)
              << dim(" ]") << "\n";
}

static void printRoomDescription(const GameState &state, const Room &room)
{
    std::cout << colored("[ " + room.name + " ]", ansi::BRIGHT_CYAN)
              << "  " << dim(timeToString(state.hour, state.minute)) << "\n";
    printHUD(state);

    if (room.state_descriptions.count(state.player.room_state))
    {
        std::cout << room.state_descriptions.at(state.player.room_state) << "\n";
    }
    else
    {
        std::cout << room.description << "\n";
    }

    if (!room.npc_ids.empty())
    {
        std::cout << "\n"
                  << colored("People here:", ansi::YELLOW);
        for (const auto &npc_id : room.npc_ids)
        {
            if (state.npcs.count(npc_id))
            {
                const NPC &npc = state.npcs.at(npc_id);
                std::cout << "\n  - " << colored(npc.name, ansi::YELLOW)
                          << dim(" (" + npc.title + ")");
            }
        }
        std::cout << "\n";
    }

    if (!room.item_ids.empty())
    {
        std::cout << "\n"
                  << colored("Items here:", ansi::GREEN);
        for (const auto &item_id : room.item_ids)
        {
            if (state.items.count(item_id))
            {
                std::cout << "\n  - " << colored(state.items.at(item_id).name, ansi::GREEN);
            }
        }
        std::cout << "\n";
    }
}

void moveToRoom(GameState &state, const std::string &target_id, Direction dir)
{
    if (!state.rooms.count(target_id))
    {
        std::cout << "That path leads somewhere... that doesn't exist. Strange.\n";
        return;
    }

    advanceTime(state, state.rooms.at(target_id).travel_time);
    state.player.current_room = target_id;
    state.player.room_state = "standing";

    const Room &room = state.rooms.at(target_id);

    std::cout << "\nYou head " << direction_to_string(dir) << " to the " << colored(room.name, ansi::BRIGHT_CYAN) << ".";
    if (room.travel_time > 1)
    {
        std::cout << dim(" (" + std::to_string(room.travel_time) + " min)");
    }
    std::cout << "\n\n";

    printRoomDescription(state, room);
    std::cout << "\n";

    bool has_suspicious = false;
    for (const auto &inv_id : state.player.inventory)
    {
        if (state.items.count(inv_id) && state.items.at(inv_id).is_suspicious && !state.items.at(inv_id).is_concealable)
        {
            has_suspicious = true;
            break;
        }
    }
    if (has_suspicious && !room.npc_ids.empty())
    {
        std::cout << "  [!] You feel watched. Carrying suspicious items around people is risky.\n";
    }
}

void cmdLook(GameState &state, const std::string &)
{
    const Room &room = state.rooms.at(state.player.current_room);
    std::cout << "\n";
    printRoomDescription(state, room);
    std::cout << "\n";
    state.rooms.at(state.player.current_room).visited = true;
}

void cmdGo(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Go where? Specify a direction or room name.\n";
        return;
    }

    if (state.player.room_state == "in_bed")
    {
        std::cout << "You need to get out of bed first.\n";
        return;
    }

    try
    {
        Direction dir = direction_from_string(args);
        const Room &current = state.rooms.at(state.player.current_room);
        auto it = current.exits.find(dir);
        if (it == current.exits.end())
        {
            std::cout << "You can't go " << direction_to_string(dir) << " from here.\n";
            return;
        }
        moveToRoom(state, it->second, dir);
        return;
    }
    catch (const std::invalid_argument &)
    {
    }

    std::string room_name = args;
    if (room_name.size() > 3 && room_name.substr(0, 3) == "to ")
    {
        room_name = room_name.substr(3);
    }
    if (room_name.size() > 4 && room_name.substr(0, 4) == "the ")
    {
        room_name = room_name.substr(4);
    }

    const Room &current = state.rooms.at(state.player.current_room);
    for (const auto &exit : current.exits)
    {
        if (!state.rooms.count(exit.second))
        {
            continue;
        }
        std::string target_name = to_lower(state.rooms.at(exit.second).name);
        if (target_name.find(to_lower(room_name)) != std::string::npos)
        {
            moveToRoom(state, exit.second, exit.first);
            return;
        }
    }

    std::cout << "\"" << args << "\" is not a valid direction or connected room.\n";
    std::cout << "Try a direction (north, south, ...) or a room name (e.g., \"go to hallway\").\n";
}