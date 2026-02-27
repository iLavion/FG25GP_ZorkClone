#include "game.hpp"

void registerForestWoodlandPath(GameState &state);
void registerForestHuntingClearing(GameState &state);
void registerForestAbandonedShack(GameState &state);
void registerForestHiddenCave(GameState &state);
void registerForestOldRuins(GameState &state);

void buildForest(GameState &state)
{
    Area area;
    area.id = "forest_edge";
    area.name = "The Forest Edge";
    area.rooms = {
        "forest_woodland_path", "forest_hunting_clearing",
        "forest_abandoned_shack", "forest_hidden_cave", "forest_old_ruins"};
    state.areas[area.id] = area;

    registerForestWoodlandPath(state);
    registerForestHuntingClearing(state);
    registerForestAbandonedShack(state);
    registerForestHiddenCave(state);
    registerForestOldRuins(state);
}
