#include "test_framework.hpp"
#include "game.hpp"
#include "commands/handlers.hpp"
#include "commands/helpers.hpp"

static GameState makeTestState()
{
    GameState state;
    state.player.name = "Test Lady";
    state.player.current_room = "bedroom";
    state.player.hunger = 100;
    state.player.energy = 100;
    state.player.gold = 50;
    state.player.room_state = "standing";

    Room bedroom;
    bedroom.id = "bedroom";
    bedroom.name = "Bedroom";
    bedroom.description = "A cozy bedroom.";
    bedroom.area_id = "estate";
    bedroom.allows_sleep = true;
    bedroom.exits[Direction::South] = "hallway";
    state.rooms["bedroom"] = bedroom;

    Room hallway;
    hallway.id = "hallway";
    hallway.name = "Hallway";
    hallway.description = "A long hallway.";
    hallway.area_id = "estate";
    hallway.exits[Direction::North] = "bedroom";
    hallway.exits[Direction::South] = "grand_hall";
    state.rooms["hallway"] = hallway;

    Room grand_hall;
    grand_hall.id = "grand_hall";
    grand_hall.name = "Grand Hall";
    grand_hall.description = "A grand hall with a chandelier.";
    grand_hall.area_id = "estate";
    grand_hall.exits[Direction::North] = "hallway";
    state.rooms["grand_hall"] = grand_hall;

    Item apple;
    apple.id = "apple";
    apple.name = "Apple";
    apple.description = "A shiny red apple.";
    apple.edible = true;
    apple.hunger_restore = 20;
    state.items["apple"] = apple;
    state.rooms["bedroom"].item_ids.push_back("apple");

    Item dagger;
    dagger.id = "dagger";
    dagger.name = "Dagger";
    dagger.description = "A sharp dagger.";
    dagger.is_weapon = true;
    dagger.is_suspicious = true;
    state.items["dagger"] = dagger;
    state.rooms["hallway"].item_ids.push_back("dagger");

    Item book;
    book.id = "book";
    book.name = "Book of Alchemy";
    book.description = "A dusty book.";
    book.readable = true;
    book.skill_grant = "alchemy";
    book.xp_grant = 10;
    state.items["book"] = book;

    NPC butler;
    butler.id = "butler";
    butler.name = "Butler Graves";
    butler.title = "Head Butler";
    butler.description = "The loyal family butler.";
    butler.current_room = "hallway";
    butler.disposition = Disposition::Loyal;
    butler.affection = 50;
    butler.suspicion = 0;
    butler.alive = true;
    butler.hireable = true;
    butler.hire_cost = 10;
    state.npcs["butler"] = butler;
    state.rooms["hallway"].npc_ids.push_back("butler");

    NPC elena;
    elena.id = "elena";
    elena.name = "Elena";
    elena.title = "The Heroine";
    elena.description = "A charming commoner.";
    elena.current_room = "grand_hall";
    elena.disposition = Disposition::Neutral;
    elena.affection = 0;
    elena.suspicion = 0;
    elena.alive = true;
    elena.is_heroine = true;
    state.npcs["elena"] = elena;
    state.rooms["grand_hall"].npc_ids.push_back("elena");

    return state;
}

bool test_player_default_state()
{
    GameState state = makeTestState();
    TEST_ASSERT_EQ(state.player.current_room, "bedroom", "starts in bedroom");
    TEST_ASSERT_EQ(state.player.hunger, 100, "hunger starts at 100");
    TEST_ASSERT_EQ(state.player.energy, 100, "energy starts at 100");
    TEST_ASSERT_EQ(state.player.gold, 50, "gold starts at 50");
    TEST_ASSERT(state.player.inventory.empty(), "inventory starts empty");
    return true;
}

bool test_movement_basic()
{
    GameState state = makeTestState();
    moveToRoom(state, "hallway", Direction::South);
    TEST_ASSERT_EQ(state.player.current_room, "hallway", "moved to hallway");
    return true;
}

bool test_movement_chain()
{
    GameState state = makeTestState();
    moveToRoom(state, "hallway", Direction::South);
    TEST_ASSERT_EQ(state.player.current_room, "hallway", "in hallway");
    moveToRoom(state, "grand_hall", Direction::South);
    TEST_ASSERT_EQ(state.player.current_room, "grand_hall", "in grand hall");
    moveToRoom(state, "hallway", Direction::North);
    TEST_ASSERT_EQ(state.player.current_room, "hallway", "back in hallway");
    return true;
}

bool test_movement_resets_room_state()
{
    GameState state = makeTestState();
    state.player.room_state = "in_bed";
    moveToRoom(state, "hallway", Direction::South);
    TEST_ASSERT_EQ(state.player.room_state, "standing", "room state reset to standing");
    return true;
}

bool test_pickup_item()
{
    GameState state = makeTestState();
    cmdPickup(state, "apple");
    TEST_ASSERT_EQ(static_cast<int>(state.player.inventory.size()), 1, "inventory has 1 item");
    TEST_ASSERT_EQ(state.player.inventory[0], "apple", "inventory has apple");

    bool apple_in_room = false;
    for (const auto &id : state.rooms["bedroom"].item_ids)
    {
        if (id == "apple")
        {
            apple_in_room = true;
        }
    }
    TEST_ASSERT(!apple_in_room, "apple removed from room");
    return true;
}

bool test_pickup_nonexistent_item()
{
    GameState state = makeTestState();
    cmdPickup(state, "diamond");
    TEST_ASSERT(state.player.inventory.empty(), "inventory still empty after picking up nonexistent item");
    return true;
}

bool test_drop_item()
{
    GameState state = makeTestState();
    cmdPickup(state, "apple");
    TEST_ASSERT_EQ(static_cast<int>(state.player.inventory.size()), 1, "picked up apple");

    cmdDrop(state, "apple");
    TEST_ASSERT(state.player.inventory.empty(), "inventory empty after drop");

    bool apple_in_room = false;
    for (const auto &id : state.rooms["bedroom"].item_ids)
    {
        if (id == "apple")
        {
            apple_in_room = true;
        }
    }
    TEST_ASSERT(apple_in_room, "apple back in room after drop");
    return true;
}

bool test_drop_item_persists_in_different_room()
{
    GameState state = makeTestState();
    cmdPickup(state, "apple");
    moveToRoom(state, "hallway", Direction::South);
    cmdDrop(state, "apple");

    bool apple_in_hallway = false;
    for (const auto &id : state.rooms["hallway"].item_ids)
    {
        if (id == "apple")
        {
            apple_in_hallway = true;
        }
    }
    TEST_ASSERT(apple_in_hallway, "apple persists in hallway after drop");

    bool apple_in_bedroom = false;
    for (const auto &id : state.rooms["bedroom"].item_ids)
    {
        if (id == "apple")
        {
            apple_in_bedroom = true;
        }
    }
    TEST_ASSERT(!apple_in_bedroom, "apple not in bedroom anymore");
    return true;
}

bool test_eat_item()
{
    GameState state = makeTestState();
    state.player.hunger = 50;
    cmdPickup(state, "apple");
    cmdEat(state, "apple");
    TEST_ASSERT_EQ(state.player.hunger, 70, "hunger restored by 20");
    TEST_ASSERT(state.player.inventory.empty(), "apple consumed from inventory");
    return true;
}

bool test_eat_non_food()
{
    GameState state = makeTestState();
    moveToRoom(state, "hallway", Direction::South);
    cmdPickup(state, "dagger");
    int inv_size_before = static_cast<int>(state.player.inventory.size());
    cmdEat(state, "dagger");
    TEST_ASSERT_EQ(static_cast<int>(state.player.inventory.size()), inv_size_before,
                   "non-food item not consumed");
    return true;
}

bool test_hunger_does_not_exceed_100()
{
    GameState state = makeTestState();
    state.player.hunger = 95;
    cmdPickup(state, "apple");
    cmdEat(state, "apple");
    TEST_ASSERT_EQ(state.player.hunger, 100, "hunger capped at 100");
    return true;
}

bool test_sleep_restores_energy()
{
    GameState state = makeTestState();
    state.player.energy = 40;
    cmdSleep(state, "");
    TEST_ASSERT_EQ(state.player.energy, 80, "energy restored by 40");
    TEST_ASSERT_EQ(state.player.room_state, "in_bed", "room state set to in_bed");
    return true;
}

bool test_sleep_wrong_room()
{
    GameState state = makeTestState();
    state.player.energy = 40;
    moveToRoom(state, "hallway", Direction::South);
    cmdSleep(state, "");
    TEST_ASSERT_EQ(state.player.energy, 40, "energy unchanged, can't sleep in hallway");
    return true;
}

bool test_find_npc_in_room()
{
    GameState state = makeTestState();
    moveToRoom(state, "hallway", Direction::South);
    std::string result = findNPCInRoom(state, "butler");
    TEST_ASSERT_EQ(result, "butler", "found butler by id");

    std::string result2 = findNPCInRoom(state, "Graves");
    TEST_ASSERT_EQ(result2, "butler", "found butler by partial name");

    std::string result3 = findNPCInRoom(state, "nobody");
    TEST_ASSERT_EQ(result3, "", "nobody found returns empty");
    return true;
}

bool test_find_item_in_room()
{
    GameState state = makeTestState();
    std::string result = findItemInRoom(state, "apple");
    TEST_ASSERT_EQ(result, "apple", "found apple in room");

    std::string result2 = findItemInRoom(state, "App");
    TEST_ASSERT_EQ(result2, "apple", "found apple by partial name");

    std::string result3 = findItemInRoom(state, "diamond");
    TEST_ASSERT_EQ(result3, "", "diamond not found");
    return true;
}

bool test_find_item_in_inventory()
{
    GameState state = makeTestState();
    state.player.inventory.push_back("apple");
    std::string result = findItemInInventory(state, "apple");
    TEST_ASSERT_EQ(result, "apple", "found apple in inventory");

    std::string result2 = findItemInInventory(state, "diamond");
    TEST_ASSERT_EQ(result2, "", "diamond not in inventory");
    return true;
}

bool test_npc_suspicion_tracking()
{
    GameState state = makeTestState();
    TEST_ASSERT_EQ(state.npcs["butler"].suspicion, 0, "butler suspicion starts at 0");
    state.npcs["butler"].suspicion += 10;
    TEST_ASSERT_EQ(state.npcs["butler"].suspicion, 10, "butler suspicion increased to 10");
    TEST_ASSERT_EQ(state.npcs["elena"].suspicion, 0, "elena suspicion unaffected");
    return true;
}

bool test_time_advances()
{
    GameState state = makeTestState();
    int before_min = state.minute;
    int before_hour = state.hour;
    advanceTime(state, 30);
    int total_before = before_hour * 60 + before_min;
    int total_after = state.hour * 60 + state.minute;
    TEST_ASSERT_EQ(total_after - total_before, 30, "time advanced by 30 minutes");
    return true;
}

bool test_time_hour_rollover()
{
    GameState state = makeTestState();
    state.hour = 8;
    state.minute = 45;
    advanceTime(state, 30);
    TEST_ASSERT_EQ(state.hour, 9, "hour rolled over from 8:45 + 30min");
    TEST_ASSERT_EQ(state.minute, 15, "minute is 15 after rollover");
    return true;
}

bool test_time_day_rollover()
{
    GameState state = makeTestState();
    state.hour = 23;
    state.minute = 30;
    int old_day = state.day;
    advanceTime(state, 60);
    TEST_ASSERT_EQ(state.day, old_day + 1, "day incremented on midnight rollover");
    TEST_ASSERT_EQ(state.hour, 0, "hour reset to 0");
    TEST_ASSERT_EQ(state.minute, 30, "minute is 30 after rollover");
    return true;
}

bool test_time_to_string()
{
    TEST_ASSERT_EQ(timeToString(8, 0), "08:00 (morning)", "8:00 morning");
    TEST_ASSERT_EQ(timeToString(14, 30), "14:30 (afternoon)", "14:30 afternoon");
    TEST_ASSERT_EQ(timeToString(19, 0), "19:00 (evening)", "19:00 evening");
    TEST_ASSERT_EQ(timeToString(22, 0), "22:00 (night)", "22:00 night");
    return true;
}

bool test_tick_hunger_decay()
{
    GameState state = makeTestState();
    state.player.turns_without_eating = 16;
    state.player.hunger = 80;
    tickStatus(state);
    TEST_ASSERT(state.player.hunger < 80, "hunger decreased after not eating");
    return true;
}

bool test_tick_energy_decay()
{
    GameState state = makeTestState();
    state.player.turns_without_sleeping = 21;
    state.player.energy = 80;
    tickStatus(state);
    TEST_ASSERT(state.player.energy < 80, "energy decreased after not sleeping");
    return true;
}

bool test_tick_starvation_drains_energy()
{
    GameState state = makeTestState();
    state.player.hunger = 0;
    state.player.energy = 50;
    tickStatus(state);
    TEST_ASSERT(state.player.energy < 50, "energy drained while starving");
    return true;
}

bool test_log_command()
{
    clearCommandLog();
    logCommand("look");
    logCommand("go north");
    logCommand("inventory");
    std::vector<std::string> log = getCommandLog();
    TEST_ASSERT_EQ(static_cast<int>(log.size()), 3, "3 commands logged");
    TEST_ASSERT_EQ(log[0], "look", "first command is look");
    TEST_ASSERT_EQ(log[1], "go north", "second command is go north");
    TEST_ASSERT_EQ(log[2], "inventory", "third command is inventory");
    clearCommandLog();
    return true;
}

bool test_log_clear()
{
    clearCommandLog();
    logCommand("test");
    clearCommandLog();
    std::vector<std::string> log = getCommandLog();
    TEST_ASSERT(log.empty(), "log cleared");
    return true;
}

bool test_undo_restores_state()
{
    Game game;
    game.state = makeTestState();
    game.isRunning = true;

    game.undo_stack.push_back(game.state);
    moveToRoom(game.state, "hallway", Direction::South);
    TEST_ASSERT_EQ(game.state.player.current_room, "hallway", "moved to hallway");

    game.state = game.undo_stack.back();
    game.undo_stack.pop_back();
    TEST_ASSERT_EQ(game.state.player.current_room, "bedroom", "undo restored bedroom");
    return true;
}

bool test_undo_stack_limit()
{
    Game game;
    game.state = makeTestState();

    for (int i = 0; i < 60; i++)
    {
        game.undo_stack.push_back(game.state);
        if (game.undo_stack.size() > 50)
        {
            game.undo_stack.erase(game.undo_stack.begin());
        }
    }
    TEST_ASSERT(static_cast<int>(game.undo_stack.size()) <= 50, "undo stack capped at 50");
    return true;
}

bool test_quest_flags_default()
{
    QuestFlags q;
    TEST_ASSERT(!q.invited_elena, "invited_elena defaults false");
    TEST_ASSERT(!q.elena_dead, "elena_dead defaults false");
    TEST_ASSERT(!q.body_hidden, "body_hidden defaults false");
    TEST_ASSERT(!q.murder_witnessed, "murder_witnessed defaults false");
    TEST_ASSERT(!q.elena_expelled, "elena_expelled defaults false");
    TEST_ASSERT_EQ(q.elena_retaliation_count, 0, "retaliation count defaults 0");
    TEST_ASSERT(!q.starvation_warning, "starvation_warning defaults false");
    TEST_ASSERT(!q.duke_dead, "duke_dead defaults false");
    TEST_ASSERT(!q.player_bloodied, "player_bloodied defaults false");
    TEST_ASSERT(q.murder_weapon.empty(), "murder_weapon defaults empty");
    TEST_ASSERT(q.dead_bodies.empty(), "dead_bodies defaults empty");
    TEST_ASSERT(q.action_cooldowns.empty(), "action_cooldowns defaults empty");
    return true;
}

TestSuite createGameStateTests()
{
    TestSuite suite;
    suite.name = "Game State & Commands";
    suite.tests = {
        {"player default state", test_player_default_state},
        {"movement - basic", test_movement_basic},
        {"movement - chain", test_movement_chain},
        {"movement - resets room state", test_movement_resets_room_state},
        {"pickup item", test_pickup_item},
        {"pickup nonexistent item", test_pickup_nonexistent_item},
        {"drop item", test_drop_item},
        {"drop item persists in different room", test_drop_item_persists_in_different_room},
        {"eat item", test_eat_item},
        {"eat non-food", test_eat_non_food},
        {"hunger does not exceed 100", test_hunger_does_not_exceed_100},
        {"sleep restores energy", test_sleep_restores_energy},
        {"sleep wrong room", test_sleep_wrong_room},
        {"find NPC in room", test_find_npc_in_room},
        {"find item in room", test_find_item_in_room},
        {"find item in inventory", test_find_item_in_inventory},
        {"NPC suspicion tracking", test_npc_suspicion_tracking},
        {"time advances", test_time_advances},
        {"time hour rollover", test_time_hour_rollover},
        {"time day rollover", test_time_day_rollover},
        {"timeToString", test_time_to_string},
        {"tick - hunger decay", test_tick_hunger_decay},
        {"tick - energy decay", test_tick_energy_decay},
        {"tick - starvation drains energy", test_tick_starvation_drains_energy},
        {"log command", test_log_command},
        {"log clear", test_log_clear},
        {"undo restores state", test_undo_restores_state},
        {"undo stack limit", test_undo_stack_limit},
        {"quest flags default", test_quest_flags_default},
    };
    return suite;
}