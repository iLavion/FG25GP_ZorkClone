#include "game.hpp"
#include "cli.hpp"
#include "utilities/text.hpp"
#include <iostream>

int main()
{
    enableAnsi();
    Game game;
    setupGame(game);
    registerCommands(game);
    startGame(game);

    std::string input;
    while (game.isRunning)
    {
        if (game.state.game_over)
        {
            std::cout << "\nThe story of " << game.state.player.name << " has reached its conclusion.\n";
            std::cout << "Thank you for playing Villainess of the Empire.\n";
            break;
        }
        std::cout << colored("> ", ansi::BRIGHT_CYAN);
        if (!std::getline(std::cin, input))
        {
            break;
        }
        if (input.empty())
        {
            continue;
        }
        procInput(game, input);
    }

    return 0;
}
