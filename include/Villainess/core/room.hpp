#pragma once

#include <string>
#include <unordered_map>
#include <vector>

enum class Direction
{
    North,
    South,
    East,
    West,
    Up,
    Down
};

struct Room
{
    std::string id;
    std::string name;
    std::string description;
    std::string area_id;
    std::unordered_map<Direction, std::string> exits;
    std::vector<std::string> npc_ids;
    std::vector<std::string> item_ids;
    bool visited = false;
    bool allows_sleep = false;
    int travel_time = 1;
    std::unordered_map<std::string, std::string> state_descriptions;
};

Direction direction_from_string(const std::string &str);
std::string direction_to_string(Direction dir);