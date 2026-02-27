#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Player
{
    std::string name = "Lady Seraphina";
    std::string current_room = "bedroom";
    std::vector<std::string> inventory;
    int hunger = 100;
    int energy = 100;
    int suspicion = 0;
    int reputation = 80;
    int gold = 50;
    int turns_without_eating = 0;
    int turns_without_sleeping = 0;
    int turn_count = 0;
    std::unordered_map<std::string, int> skills;
    std::string room_state = "standing";
};
