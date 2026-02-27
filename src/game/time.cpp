#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <string>

std::string timeToString(int hour, int minute)
{
    std::string h = (hour < 10 ? "0" : "") + std::to_string(hour);
    std::string m = (minute < 10 ? "0" : "") + std::to_string(minute);
    std::string period = (hour < 12) ? "morning" : (hour < 17) ? "afternoon"
                                               : (hour < 21)   ? "evening"
                                                               : "night";
    return h + ":" + m + " (" + period + ")";
}

void advanceTime(GameState &state, int minutes)
{
    state.minute += minutes;
    while (state.minute >= 60)
    {
        state.minute -= 60;
        state.hour++;
    }
    bool new_day = false;
    while (state.hour >= 24)
    {
        state.hour -= 24;
        state.day++;
        new_day = true;
    }
    if (new_day)
    {
        std::cout << "\n*** A new day dawns. It is now Day " << state.day << ". ***\n";
    }
    updateNPCLocations(state);
}

static int applyTraitOffset(int sched_hour, const std::vector<Trait> &traits)
{
    int h = sched_hour;
    for (auto t : traits)
    {
        switch (t)
        {
        case Trait::EarlyBird:
            h -= 1;
            break;
        case Trait::NightOwl:
            h += 1;
            break;
        case Trait::DeepSleeper:
            if (sched_hour < 12)
            {
                h += 2;
            }
            break;
        default:
            break;
        }
    }
    while (h < 0)
        h += 24;
    while (h >= 24)
        h -= 24;
    return h;
}

void updateNPCLocations(GameState &state)
{
    int now = state.hour * 60 + state.minute;
    for (auto &pair : state.npcs)
    {
        NPC &npc = pair.second;
        const std::string &npc_id = pair.first;
        if (!npc.alive || npc.schedule.empty())
        {
            continue;
        }
        if (npc.pinned_until >= 0 && now < npc.pinned_until)
        {
            continue;
        }
        npc.pinned_until = -1;

        int best_effective = -1;
        std::string best_room;
        for (const auto &entry : npc.schedule)
        {
            int eff = applyTraitOffset(entry.first, npc.traits);
            if (eff <= state.hour && eff > best_effective)
            {
                best_effective = eff;
                best_room = entry.second;
            }
        }
        if (best_effective < 0)
        {
            for (const auto &entry : npc.schedule)
            {
                int eff = applyTraitOffset(entry.first, npc.traits);
                if (eff > best_effective)
                {
                    best_effective = eff;
                    best_room = entry.second;
                }
            }
        }

        if (!best_room.empty() && best_room != npc.current_room && state.rooms.count(best_room))
        {
            if (state.rooms.count(npc.current_room))
            {
                auto &old_ids = state.rooms[npc.current_room].npc_ids;
                old_ids.erase(std::remove(old_ids.begin(), old_ids.end(), npc_id), old_ids.end());
            }
            npc.current_room = best_room;
            auto &new_ids = state.rooms[best_room].npc_ids;
            if (std::find(new_ids.begin(), new_ids.end(), npc_id) == new_ids.end())
            {
                new_ids.push_back(npc_id);
            }
        }
    }
}
