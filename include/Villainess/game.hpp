#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "core/player.hpp"
#include "core/room.hpp"
#include "core/area.hpp"
#include "core/npc.hpp"
#include "core/item.hpp"
#include "core/dialogue.hpp"

struct QuestFlags
{
    bool invited_elena = false;
    bool wrote_invitation = false;
    bool elena_arrived_dinner = false;
    bool acquired_poison = false;
    bool poisoned_tea = false;
    bool elena_drank_tea = false;
    bool elena_dead = false;
    bool body_hidden = false;
    bool body_discovered = false;
    bool secret_passage_known = false;
    bool elena_diary_read = false;
    bool rumors_spread = false;
    bool chef_bribed = false;
    bool elena_embarrassed = false;
    bool cedric_alliance = false;
    bool rosalind_warned = false;
    bool elena_letters_found = false;
    bool duke_suspicious_elena = false;
    bool servants_loyal = false;
    bool overheard_secret = false;
    bool elena_expelled = false;
    bool murder_witnessed = false;
    bool npc_killed_unseen = false;
    bool met_elena = false;
    bool elena_retaliating = false;
    int elena_retaliation_count = 0;
    bool starvation_warning = false;
    bool duke_dead = false;
    std::unordered_map<std::string, int> action_cooldowns;
    bool player_bloodied = false;
    std::string murder_weapon;
    std::unordered_map<std::string, std::string> dead_bodies;
    std::unordered_set<std::string> hidden_bodies;
    int welfare_check_timer = 0;
    std::unordered_set<std::string> welfare_checked;
};

struct GameState
{
    Player player;
    std::unordered_map<std::string, Room> rooms;
    std::unordered_map<std::string, Area> areas;
    std::unordered_map<std::string, NPC> npcs;
    std::unordered_map<std::string, Item> items;
    std::unordered_map<std::string, DialogueNode> dialogue_nodes;

    int heroine_popularity = 10;
    int day = 1;
    int hour = 8;
    int minute = 0;

    bool in_dialogue = false;
    std::string current_dialogue_node;
    std::string talking_to_npc;

    bool game_over = false;

    QuestFlags quest;

    std::unordered_set<std::string> books_read;
};

struct CommandInfo
{
    std::string verb;
    std::string description;
    bool takes_argument;
    std::function<void(GameState &, const std::string &)> handler;
};

struct Game
{
    bool isRunning = false;
    GameState state;
    std::vector<GameState> undo_stack;
    std::vector<CommandInfo> commands;
};

void setupGame(Game &game);
void startGame(Game &game);
void stopGame(Game &game, const std::string &args);

void logCommand(const std::string &cmd);
std::vector<std::string> getCommandLog();
void clearCommandLog();

void tickStatus(GameState &state);

void advanceTime(GameState &state, int minutes);
std::string timeToString(int hour, int minute);
void updateNPCLocations(GameState &state);

void buildItems(GameState &state);
void buildRooms(GameState &state);
void buildNPCs(GameState &state);

struct RoomAction
{
    std::string text;
    std::function<bool(const GameState &)> condition = nullptr;
    std::function<void(GameState &)> effect;
};

void registerRoomActions(const std::string &room_id, std::vector<RoomAction> actions);
void showRoomChoices(const GameState &state);
void cmdChoose(GameState &state, const std::string &args);

void moveToRoom(GameState &state, const std::string &target_id, Direction dir);
std::string playerDisplayName(const GameState &state);