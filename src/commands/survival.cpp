#include "commands/handlers.hpp"
#include "commands/helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <algorithm>

void cmdEat(GameState &state, const std::string &args)
{
    if (args.empty())
    {
        std::cout << "Eat what? Specify a food item.\n";
        return;
    }

    std::string item_id = findItemInInventory(state, args);
    if (item_id.empty())
    {
        std::cout << "You don't have \"" << args << "\" to eat.\n";
        return;
    }

    const Item &item = state.items.at(item_id);
    if (!item.edible)
    {
        std::cout << "You can't eat the " << item.name << ". That's not food.\n";
        return;
    }

    auto it = std::find(state.player.inventory.begin(), state.player.inventory.end(), item_id);
    if (it != state.player.inventory.end())
    {
        state.player.inventory.erase(it);
    }

    if (item.is_poison)
    {
        std::cout << "\n";
        print_narrative("You pop the berries into your mouth. They taste sweet at first...");
        print_narrative("Then a burning sensation spreads across your tongue.");
        print_narrative("Your vision blurs. Your legs give way beneath you.");
        print_narrative("The world tilts sideways as you crumple to the floor.");
        std::cout << "\n";
        std::cout << colored("  *** The deadly nightshade does its work swiftly. ***", ansi::BRIGHT_RED) << "\n";
        print_narrative("Lady Seraphina, daughter of Duke Aldric, is found cold and still,");
        print_narrative("a stain of dark berries on her lips. No foul play is suspected.");
        print_narrative("After all, who would poison themselves?");
        std::cout << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        std::cout << colored("  ** ENDING: A Bitter Taste **", ansi::BRIGHT_WHITE) << "\n";
        std::cout << colored("============================================================", ansi::RED) << "\n";
        state.game_over = true;
        return;
    }

    state.player.hunger = std::min(100, state.player.hunger + item.hunger_restore);
    state.player.turns_without_eating = 0;

    std::cout << "You eat the " << item.name << ". ";
    if (item.hunger_restore >= 20)
    {
        std::cout << "Delicious! You feel much better.\n";
    }
    else
    {
        std::cout << "It takes the edge off your hunger.\n";
    }
    std::cout << "  Hunger: " << state.player.hunger << "/100\n";

    advanceTime(state, 10);
}

void cmdSleep(GameState &state, const std::string &)
{
    const Room &room = state.rooms.at(state.player.current_room);
    if (!room.allows_sleep)
    {
        std::cout << "You can't sleep here. Find a proper bed (try your Bedroom).\n";
        return;
    }

    state.player.energy = std::min(100, state.player.energy + 40);
    state.player.turns_without_sleeping = 0;
    std::cout << "You lie down and rest...\n";
    std::cout << "...\n";

    int sleep_hours = 8;
    advanceTime(state, sleep_hours * 60);

    std::cout << "You wake feeling refreshed. It is now " << timeToString(state.hour, state.minute) << ".\n";
    std::cout << "  Energy: " << state.player.energy << "/100\n";

    state.player.room_state = "in_bed";
    state.heroine_popularity = std::min(100, state.heroine_popularity + 1);
    std::cout << "  [i] Time has passed. Elena's influence may have grown.\n";
}
