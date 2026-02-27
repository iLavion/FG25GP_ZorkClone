#pragma once

#include <string>
#include <vector>

struct Item
{
    std::string id;
    std::string name;
    std::string description;
    std::string inspect_text;
    std::string pickup_text;
    bool edible = false;
    int hunger_restore = 0;
    bool is_weapon = false;
    bool is_suspicious = false;
    bool readable = false;
    std::string skill_grant;
    int xp_grant = 0;
    bool is_poison = false;
    bool is_consumable = false;
};
