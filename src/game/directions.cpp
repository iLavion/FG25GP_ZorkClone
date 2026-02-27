#include "core/room.hpp"
#include "utilities/string.hpp"
#include <stdexcept>

Direction direction_from_string(const std::string &str)
{
    std::string lower = to_lower(str);
    if (lower == "north" || lower == "n")
    {
        return Direction::North;
    }
    else if (lower == "south" || lower == "s")
    {
        return Direction::South;
    }
    else if (lower == "east" || lower == "e")
    {
        return Direction::East;
    }
    else if (lower == "west" || lower == "w")
    {
        return Direction::West;
    }
    else if (lower == "up" || lower == "u")
    {
        return Direction::Up;
    }
    else if (lower == "down" || lower == "d")
    {
        return Direction::Down;
    }
    else
    {
        throw std::invalid_argument("Unknown direction: " + str);
    }
}

std::string direction_to_string(Direction dir)
{
    switch (dir)
    {
    case Direction::North:
        return "north";
    case Direction::South:
        return "south";
    case Direction::East:
        return "east";
    case Direction::West:
        return "west";
    case Direction::Up:
        return "up";
    case Direction::Down:
        return "down";
    }
    return "unknown";
}
