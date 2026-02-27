#pragma once

#include <string>
#include <unordered_map>
#include <vector>

enum class Disposition
{
    Loyal,
    Neutral,
    Suspicious,
    Hostile
};

enum class Trait
{
    EarlyBird,
    NightOwl,
    DeepSleeper,
    LightSleeper,
    Weak,
    Strong,
    Perceptive,
    Gullible,
    Greedy,
    Loyal_Trait,
    Gossip,
    Secretive,
};

struct NPC
{
    std::string id;
    std::string name;
    std::string title;
    std::string description;
    std::string current_room;
    std::string dialogue_root;
    int affection = 50;
    int suspicion = 0;
    Disposition disposition = Disposition::Neutral;
    bool alive = true;
    bool hireable = false;
    int hire_cost = 0;
    bool is_heroine = false;
    std::vector<Trait> traits;
    std::vector<std::string> associates;
    std::unordered_map<int, std::string> schedule;
    int pinned_until = -1;
};