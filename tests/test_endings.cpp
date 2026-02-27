#include "test_framework.hpp"
#include "game.hpp"
#include "commands/handlers.hpp"
#include "commands/helpers.hpp"

static GameState makeFullTestState()
{
    GameState state;
    buildItems(state);
    buildRooms(state);
    buildNPCs(state);
    state.player.room_state = "standing";
    return state;
}

bool test_ending_villainess_falls()
{
    GameState state = makeFullTestState();
    state.heroine_popularity = 90;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "game over when popularity hits 90");
    return true;
}

bool test_ending_starvation()
{
    GameState state = makeFullTestState();
    state.quest.starvation_warning = true;
    state.player.hunger = 0;
    state.player.energy = 0;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "starvation ending triggered");
    return true;
}

bool test_ending_perfect_villainess()
{
    GameState state = makeFullTestState();
    state.quest.elena_dead = true;
    state.quest.body_hidden = true;
    state.npcs["elena"].alive = false;
    state.heroine_popularity = 0;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "perfect villainess ending triggered");
    return true;
}

bool test_ending_villainess_condemned()
{
    GameState state = makeFullTestState();
    state.quest.elena_dead = true;
    state.quest.body_discovered = true;
    state.npcs["elena"].alive = false;
    state.heroine_popularity = 0;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "condemned ending triggered");
    return true;
}

bool test_ending_bloodstained_villainess()
{
    GameState state = makeFullTestState();
    state.quest.murder_witnessed = true;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "bloodstained ending triggered");
    return true;
}

bool test_ending_true_noblewoman()
{
    GameState state = makeFullTestState();
    state.quest.elena_dead = false;
    state.heroine_popularity = 15;
    int boosted = 0;
    for (auto &pair : state.npcs)
    {
        if (!pair.second.is_heroine && pair.second.alive && boosted < 6)
        {
            pair.second.affection = 80;
            boosted++;
        }
    }
    tickStatus(state);
    TEST_ASSERT(state.game_over, "true noblewoman ending triggered");
    return true;
}

bool test_ending_exposed_and_expelled()
{
    GameState state = makeFullTestState();
    state.quest.elena_expelled = true;
    state.quest.elena_dead = false;
    state.heroine_popularity = 30;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "exposed and expelled ending triggered");
    return true;
}

bool test_no_ending_when_conditions_not_met()
{
    GameState state = makeFullTestState();
    state.heroine_popularity = 50;
    tickStatus(state);
    TEST_ASSERT(!state.game_over, "no ending when conditions not met");
    return true;
}

bool test_elena_tea_death_sequence()
{
    GameState state = makeFullTestState();
    state.quest.elena_drank_tea = true;
    state.npcs["elena"].alive = true;
    state.quest.elena_dead = false;

    tickStatus(state);

    TEST_ASSERT(state.quest.elena_dead, "elena is dead after drinking tea");
    TEST_ASSERT(!state.npcs["elena"].alive, "elena alive flag set to false");
    TEST_ASSERT_EQ(state.heroine_popularity, 0, "heroine popularity reset to 0");
    return true;
}

bool test_elena_retaliation_triggers()
{
    GameState state = makeFullTestState();
    state.quest.met_elena = true;
    state.quest.elena_dead = false;
    state.npcs["elena"].suspicion = 30;
    state.quest.elena_retaliating = false;

    tickStatus(state);

    TEST_ASSERT(state.quest.elena_retaliating, "elena starts retaliating at suspicion >= 25");
    return true;
}

bool test_elena_retaliation_increases_popularity()
{
    GameState state = makeFullTestState();
    state.quest.met_elena = true;
    state.quest.elena_dead = false;
    state.npcs["elena"].suspicion = 30;
    state.quest.elena_retaliating = true;
    state.player.turn_count = 11;
    int pop_before = state.heroine_popularity;

    tickStatus(state);

    TEST_ASSERT(state.heroine_popularity > pop_before,
                "elena retaliation increases popularity on turn_count % 12 == 0");
    return true;
}

bool test_body_discovery_triggers()
{
    GameState state = makeFullTestState();
    state.quest.elena_dead = true;
    state.quest.body_hidden = false;
    state.quest.body_discovered = false;
    state.player.turn_count = 14;
    state.npcs["elena"].alive = false;
    state.heroine_popularity = 0;

    tickStatus(state);

    TEST_ASSERT(state.quest.body_discovered, "body discovered on turn % 15 == 0");
    return true;
}

bool test_full_world_has_rooms()
{
    GameState state = makeFullTestState();
    TEST_ASSERT(state.rooms.count("bedroom") > 0, "bedroom exists");
    TEST_ASSERT(state.rooms.count("hallway") > 0, "hallway exists");
    TEST_ASSERT(state.rooms.count("grand_hall") > 0, "grand_hall exists");
    TEST_ASSERT(state.rooms.count("kitchen") > 0, "kitchen exists");
    TEST_ASSERT(state.rooms.count("library") > 0, "library exists");
    TEST_ASSERT(state.rooms.count("garden") > 0, "garden exists");
    TEST_ASSERT(state.rooms.count("cellar") > 0, "cellar exists");
    return true;
}

bool test_full_world_has_npcs()
{
    GameState state = makeFullTestState();
    TEST_ASSERT(state.npcs.count("elena") > 0, "elena exists");
    TEST_ASSERT(state.npcs.count("butler_graves") > 0, "butler_graves exists");
    TEST_ASSERT(state.npcs.count("duke_aldric") > 0, "duke_aldric exists");
    TEST_ASSERT(state.npcs.count("cedric") > 0, "cedric exists");
    TEST_ASSERT(state.npcs.count("rosalind") > 0, "rosalind exists");
    TEST_ASSERT(state.npcs.count("maid_clara") > 0, "maid_clara exists");
    TEST_ASSERT(state.npcs.count("chef_marcel") > 0, "chef_marcel exists");
    TEST_ASSERT(state.npcs.count("captain_roderick") > 0, "captain_roderick exists");
    TEST_ASSERT(state.npcs.count("gardener_thorne") > 0, "gardener_thorne exists");
    return true;
}

bool test_full_world_has_items()
{
    GameState state = makeFullTestState();
    TEST_ASSERT(state.items.size() > 5, "at least 5 items in the world");
    return true;
}

bool test_full_world_rooms_connected()
{
    GameState state = makeFullTestState();
    const Room &bedroom = state.rooms.at("bedroom");
    TEST_ASSERT(!bedroom.exits.empty(), "bedroom has exits");

    for (const auto &pair : bedroom.exits)
    {
        TEST_ASSERT(state.rooms.count(pair.second) > 0,
                    "bedroom exit leads to valid room: " + pair.second);
    }
    return true;
}

bool test_integration_pickup_eat_sequence()
{
    GameState state = makeFullTestState();

    bool has_food = false;
    std::string food_id;
    for (const auto &item_id : state.rooms.at("bedroom").item_ids)
    {
        if (state.items.count(item_id) && state.items.at(item_id).edible)
        {
            has_food = true;
            food_id = item_id;
            break;
        }
    }

    if (!has_food)
    {
        for (const auto &item_id : state.rooms.at("kitchen").item_ids)
        {
            if (state.items.count(item_id) && state.items.at(item_id).edible)
            {
                has_food = true;
                food_id = item_id;
                state.player.current_room = "kitchen";
                break;
            }
        }
    }

    if (!has_food)
    {
        return true;
    }

    state.player.hunger = 50;
    cmdPickup(state, food_id);
    TEST_ASSERT_EQ(static_cast<int>(state.player.inventory.size()), 1, "picked up food");

    cmdEat(state, food_id);
    TEST_ASSERT(state.player.hunger > 50, "hunger restored after eating");
    TEST_ASSERT(state.player.inventory.empty(), "food consumed");
    return true;
}

bool test_integration_sleep_cycle()
{
    GameState state = makeFullTestState();
    state.player.energy = 30;
    state.player.room_state = "standing";

    cmdSleep(state, "");
    TEST_ASSERT_EQ(state.player.energy, 70, "energy restored after sleep");
    TEST_ASSERT_EQ(state.player.room_state, "in_bed", "player in bed after sleep");
    return true;
}

bool test_integration_navigate_estate()
{
    GameState state = makeFullTestState();
    state.player.current_room = "bedroom";
    state.player.room_state = "standing";

    const Room &bedroom = state.rooms.at("bedroom");
    TEST_ASSERT(!bedroom.exits.empty(), "bedroom has at least one exit");

    auto first_exit = bedroom.exits.begin();
    std::string next_room = first_exit->second;
    Direction dir = first_exit->first;

    moveToRoom(state, next_room, dir);
    TEST_ASSERT_EQ(state.player.current_room, next_room, "moved to next room");

    bool can_go_back = false;
    const Room &new_room = state.rooms.at(next_room);
    for (const auto &pair : new_room.exits)
    {
        if (pair.second == "bedroom")
        {
            can_go_back = true;
            moveToRoom(state, "bedroom", pair.first);
            break;
        }
    }

    if (can_go_back)
    {
        TEST_ASSERT_EQ(state.player.current_room, "bedroom", "navigated back to bedroom");
    }
    return true;
}

bool test_poison_tea_quest_flags()
{
    GameState state = makeFullTestState();

    state.quest.invited_elena = true;
    TEST_ASSERT(state.quest.invited_elena, "invited elena flag set");

    state.quest.wrote_invitation = true;
    TEST_ASSERT(state.quest.wrote_invitation, "wrote invitation flag set");

    state.quest.elena_arrived_dinner = true;
    state.quest.acquired_poison = true;
    state.quest.poisoned_tea = true;
    TEST_ASSERT(state.quest.poisoned_tea, "poisoned tea flag set");

    state.quest.elena_drank_tea = true;
    tickStatus(state);
    TEST_ASSERT(state.quest.elena_dead, "elena dead after full quest sequence");
    TEST_ASSERT_EQ(state.heroine_popularity, 0, "popularity zeroed");
    return true;
}

bool test_ending_priority_popularity_over_expelled()
{
    GameState state = makeFullTestState();
    state.heroine_popularity = 90;
    state.quest.elena_expelled = true;
    state.quest.elena_dead = false;
    tickStatus(state);
    TEST_ASSERT(state.game_over, "game over triggered");
    return true;
}

bool test_ending_starvation_npc_rescue()
{
    GameState state = makeFullTestState();
    state.player.hunger = 0;
    state.player.energy = 0;
    state.quest.starvation_warning = false;

    const Room &room = state.rooms.at(state.player.current_room);
    if (!room.npc_ids.empty())
    {
        std::string npc_id = room.npc_ids[0];
        state.npcs[npc_id].affection = 80;
    }

    tickStatus(state);

    TEST_ASSERT(state.quest.starvation_warning, "starvation warning triggered");
    TEST_ASSERT(state.player.energy > 0 || state.player.hunger > 0,
                "player rescued or given survival energy");
    return true;
}

TestSuite createEndingTests()
{
    TestSuite suite;
    suite.name = "Endings & Integration";
    suite.tests = {
        {"ENDING: The Villainess Falls (popularity >= 90)", test_ending_villainess_falls},
        {"ENDING: Starved to Death (hunger + energy = 0)", test_ending_starvation},
        {"ENDING: The Perfect Villainess (dead + hidden)", test_ending_perfect_villainess},
        {"ENDING: The Villainess Condemned (dead + discovered)", test_ending_villainess_condemned},
        {"ENDING: The Bloodstained Villainess (murder witnessed)", test_ending_bloodstained_villainess},
        {"ENDING: The True Noblewoman (5+ high affection + low pop)", test_ending_true_noblewoman},
        {"ENDING: Exposed and Expelled (elena_expelled)", test_ending_exposed_and_expelled},
        {"no ending when conditions not met", test_no_ending_when_conditions_not_met},
        {"elena tea death sequence", test_elena_tea_death_sequence},
        {"elena retaliation triggers", test_elena_retaliation_triggers},
        {"elena retaliation increases popularity", test_elena_retaliation_increases_popularity},
        {"body discovery triggers", test_body_discovery_triggers},
        {"full world has rooms", test_full_world_has_rooms},
        {"full world has NPCs", test_full_world_has_npcs},
        {"full world has items", test_full_world_has_items},
        {"full world rooms connected", test_full_world_rooms_connected},
        {"integration: pickup and eat", test_integration_pickup_eat_sequence},
        {"integration: sleep cycle", test_integration_sleep_cycle},
        {"integration: navigate estate", test_integration_navigate_estate},
        {"poison tea quest flags", test_poison_tea_quest_flags},
        {"ending priority: popularity over expelled", test_ending_priority_popularity_over_expelled},
        {"starvation NPC rescue mechanic", test_ending_starvation_npc_rescue},
    };
    return suite;
}