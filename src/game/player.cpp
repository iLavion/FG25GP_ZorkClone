#include "game.hpp"
#include "utilities/text.hpp"

std::string playerDisplayName(const GameState &state)
{
    return colored(state.player.name, ansi::BRIGHT_RED);
}
