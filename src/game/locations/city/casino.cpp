#include "game.hpp"
#include "utilities/text.hpp"
#include <iostream>
#include <random>
#include <algorithm>

static int drawCard()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 10);
    return dist(rng);
}

static std::string cardName(int value)
{
    switch (value)
    {
    case 1:
        return "Ace";
    case 2:
        return "Two";
    case 3:
        return "Three";
    case 4:
        return "Four";
    case 5:
        return "Five";
    case 6:
        return "Six";
    case 7:
        return "Seven";
    case 8:
        return "Eight";
    case 9:
        return "Nine";
    case 10:
        return "Crown";
    default:
        return "???";
    }
}

static void playCrownsFortune(GameState &gs, int bet)
{
    if (gs.player.gold < bet)
    {
        std::cout << colored("  You pat your purse and realize you don't have enough gold.", ansi::YELLOW) << "\n";
        std::cout << "  (You have " << gs.player.gold << " gold)\n";
        return;
    }

    gs.player.gold -= bet;
    std::cout << "\n"
              << colored("  ========= Crown's Fortune =========", ansi::BRIGHT_YELLOW) << "\n";
    std::cout << "  You slide " << bet << " gold across the table.\n";

    delay_ms(800);
    int playerCard = drawCard();
    std::cout << "  You draw: " << colored(cardName(playerCard), ansi::BRIGHT_CYAN) << " (" << playerCard << ")\n";

    delay_ms(800);
    int dealerCard = drawCard();
    std::cout << "  Madame Fortuna draws: " << colored(cardName(dealerCard), ansi::BRIGHT_MAGENTA) << " (" << dealerCard << ")\n";

    delay_ms(600);

    if (playerCard > dealerCard)
    {
        int winnings = bet * 2;
        gs.player.gold += winnings;
        std::cout << "\n"
                  << colored("  You win! +" + std::to_string(winnings) + " gold!", ansi::BRIGHT_GREEN) << "\n";
        std::cout << "  Madame Fortuna nods approvingly. \"Fortune smiles upon you, my lady.\"\n";
        gs.player.reputation = std::min(100, gs.player.reputation + 1);
    }
    else if (playerCard == dealerCard)
    {
        gs.player.gold += bet;
        std::cout << "\n"
                  << colored("  A draw! Your bet is returned.", ansi::BRIGHT_YELLOW) << "\n";
        std::cout << "  \"The fates are undecided,\" Madame Fortuna murmurs.\n";
    }
    else
    {
        std::cout << "\n"
                  << colored("  You lose! -" + std::to_string(bet) + " gold.", ansi::BRIGHT_RED) << "\n";
        std::cout << "  Madame Fortuna sweeps the coins away with a sympathetic smile.\n";
    }

    std::cout << "  " << dim("(Gold: " + std::to_string(gs.player.gold) + ")") << "\n";
    std::cout << colored("  =================================", ansi::BRIGHT_YELLOW) << "\n\n";
    advanceTime(gs, 5);
}

void registerCityCasino(GameState &state)
{
    Room r;
    r.id = "city_casino";
    r.name = "The Golden Chalice Casino";
    r.description = "A dimly lit establishment draped in velvet curtains and gilded mirrors.\n"
                    "Card tables fill the main floor, surrounded by nobles and merchants\n"
                    "risking their fortunes. Crystal chandeliers cast a warm amber glow\n"
                    "over the scene. The air smells of pipe smoke and expensive perfume.\n"
                    "Madame Fortuna presides over the center table, shuffling her cards\n"
                    "with hypnotic grace. The exit leads back to the Central Plaza.";
    r.area_id = "city_market_district";
    r.exits = {
        {Direction::Up, "city_central_plaza"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    registerRoomActions(
        "city_casino",
        {{"Play Crown's Fortune (5 gold)",
          [](const GameState &gs)
          {
              return gs.player.gold >= 5;
          },
          [](GameState &gs)
          {
              playCrownsFortune(gs, 5);
          }},
         {"Play Crown's Fortune (10 gold)",
          [](const GameState &gs)
          {
              return gs.player.gold >= 10;
          },
          [](GameState &gs)
          {
              playCrownsFortune(gs, 10);
          }},
         {"Play Crown's Fortune (25 gold)",
          [](const GameState &gs)
          {
              return gs.player.gold >= 25;
          },
          [](GameState &gs)
          {
              playCrownsFortune(gs, 25);
          }},
         {"Observe the other players",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You lean against a pillar and watch the room.\n\n";
              int roll = drawCard();
              if (roll <= 3)
              {
                  std::cout << "A merchant slams his fist on the table after a bad hand.\n";
                  std::cout << "His companion whispers, \"Perhaps Elena could lend you some\n";
                  std::cout << "luck. The girl seems to charm everyone she meets.\"\n";
                  std::cout << colored("  [i] Elena's influence reaches even here.", ansi::BRIGHT_CYAN) << "\n";
              }
              else if (roll <= 6)
              {
                  std::cout << "Two nobles discuss politics in hushed tones. One mentions\n";
                  std::cout << "the Aldric family with respect. Your reputation precedes you.\n";
                  gs.player.reputation = std::min(100, gs.player.reputation + 1);
                  std::cout << colored("  Reputation +1", ansi::GREEN) << "\n";
              }
              else if (roll <= 8)
              {
                  std::cout << "A cloaked figure catches your eye. They seem to be\n";
                  std::cout << "watching the exits carefully, perhaps a spy or a thief.\n";
                  std::cout << "You file the observation away for later.\n";
              }
              else
              {
                  std::cout << "Madame Fortuna catches you watching and winks knowingly.\n";
                  std::cout << "\"The cards reveal more than fortune, my lady. They reveal\n";
                  std::cout << "character.\" She taps a card with a painted crown.\n";
              }
              advanceTime(gs, 3);
          }},
         {"Ask Madame Fortuna for a reading",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "Madame Fortuna sets aside her deck and produces a smaller,\n";
              std::cout << "more ornate set of cards. She fans them across the velvet.\n\n";
              delay_ms(600);

              int roll = drawCard();
              if (!gs.quest.met_elena)
              {
                  std::cout << "\"I see a meeting ahead of you, my lady. A woman of light\n";
                  std::cout << "and shadow. She will change your fate, or you will change hers.\"\n";
                  std::cout << colored("  [i] Perhaps you should seek out Elena.", ansi::BRIGHT_CYAN) << "\n";
              }
              else if (gs.npcs.count("elena") && gs.npcs.at("elena").suspicion >= 40)
              {
                  std::cout << "\"*She draws the Serpent card.* Beware, my lady. Your rival\n";
                  std::cout << "knows of your schemes. The serpent bites when cornered.\"\n";
                  std::cout << colored("  [i] Elena is growing suspicious of you.", ansi::BRIGHT_YELLOW) << "\n";
              }
              else if (gs.player.suspicion >= 50)
              {
                  std::cout << "\"*She turns the Masked Lady.* Too many eyes watch you, child.\n";
                  std::cout << "Pull back before the mask cracks.\"\n";
                  std::cout << colored("  [i] Your suspicion is dangerously high.", ansi::BRIGHT_RED) << "\n";
              }
              else if (roll <= 5)
              {
                  std::cout << "\"*She reveals the Rising Star.* Your rival climbs, but stars\n";
                  std::cout << "that rise too fast also fall the hardest. Patience, my lady.\"\n";
                  std::cout << colored("  [i] Fortuna speaks of Elena's rising popularity.", ansi::BRIGHT_CYAN) << "\n";
              }
              else
              {
                  std::cout << "\"*She smiles at the card: the Silver Crown.* Nobility is not\n";
                  std::cout << "born, it is earned. You walk the right path, my lady.\"\n";
                  gs.player.reputation = std::min(100, gs.player.reputation + 2);
                  std::cout << colored("  Reputation +2", ansi::GREEN) << "\n";
              }
              advanceTime(gs, 5);
          }}});
}
