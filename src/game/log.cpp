#include "game.hpp"
#include <vector>
#include <string>

namespace
{
    std::vector<std::string> s_commandLog;
}

void logCommand(const std::string &cmd)
{
    s_commandLog.push_back(cmd);
}

std::vector<std::string> getCommandLog()
{
    return s_commandLog;
}

void clearCommandLog()
{
    s_commandLog.clear();
}
