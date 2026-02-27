#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>

void buildItems(GameState &state);
void buildRooms(GameState &state);
void buildNPCs(GameState &state);

static void buildWorld(GameState &state)
{
    buildItems(state);
    buildRooms(state);
    buildNPCs(state);
}

void setupGame(Game &game)
{
    game.isRunning = false;
    buildWorld(game.state);
    game.state.player.room_state = "in_bed";
    clearCommandLog();
}

void startGame(Game &game)
{
    game.isRunning = true;
    std::cout << "\n"
              << colored("============================================================", ansi::YELLOW) << "\n";
    std::cout << colored("                  VILLAINESS OF THE EMPIRE", ansi::BOLD) << "\n";
    std::cout << dim("        Copyright (c) 2026 Lavion  |  Version " + std::string(VILLAINESS_VERSION)) << "\n";
    std::cout << colored("============================================================", ansi::YELLOW) << "\n\n";

    print_narrative("You are " + playerDisplayName(game.state) + ", daughter of Duke Aldric.");
    print_narrative("A commoner named " + colored("Elena", ansi::BRIGHT_MAGENTA) + " has been gaining frightening popularity");
    print_narrative("among the nobles. If left unchecked, she will steal your");
    print_narrative("family's influence, and your very life may be at stake.");
    print_pause(colored("End her spotlight... by any means necessary.\n\n", ansi::BRIGHT_RED), 600);

    std::cout << dim("Type HELP or COMMANDS to get started.") << "\n\n";

    const Room &room = game.state.rooms.at(game.state.player.current_room);
    std::cout << colored("[ " + room.name + " ]", ansi::BRIGHT_CYAN) << "  " << dim(timeToString(game.state.hour, game.state.minute)) << "\n";
    if (room.state_descriptions.count(game.state.player.room_state))
    {
        std::cout << room.state_descriptions.at(game.state.player.room_state) << "\n\n";
    }
    else
    {
        std::cout << room.description << "\n\n";
    }
    showRoomChoices(game.state);
}

void stopGame(Game &game, const std::string &)
{
    std::cout << "\nThe curtain falls on " << game.state.player.name << "'s story... for now.\n";
    std::cout << "Goodbye.\n";
    game.isRunning = false;
}
