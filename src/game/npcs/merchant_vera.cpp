#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerMerchantVera(GameState &state)
{
    NPC n;
    n.id = "merchant_vera";
    n.name = "Merchant Vera";
    n.title = "Traveling Merchant";
    n.description = "A sharp-eyed woman with sun-weathered skin and a colorful headscarf.\n"
                    "Her market stall is overflowing with trinkets, fabrics, and curiosities\n"
                    "from distant lands. She sizes up every customer with a practiced eye.";
    n.current_room = "city_central_plaza";
    n.affection = 10;
    n.suspicion = 0;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "vera_root";
    n.traits = {Trait::Perceptive};
    n.schedule = {
        {6, "city_bakery"},
        {7, "city_central_plaza"},
        {12, "city_bakery"},
        {13, "city_central_plaza"},
        {18, "city_general_store"},
        {20, "city_alleyways"},
        {22, "city_central_plaza"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
    {
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    }

    addNode(state, "vera_root", "Merchant Vera",
            "\"*She looks up from arranging her wares and grins.*\n"
            "Well, well! A lady of quality, gracing my humble stall. What can\n"
            "Vera do for you today, my lady? I have goods from every corner\n"
            "of the Empire.\"",
            {{"\"What do you have for sale?\"", "vera_goods", nullptr, nullptr},
             {"\"I'm looking for information, not goods.\"", "vera_info", nullptr,
              [](GameState &gs)
              { gs.npcs["merchant_vera"].suspicion += 3; }},
             {"\"Tell me what's happening in the city.\"", "vera_gossip", nullptr, nullptr},
             {"\"Do you know anything about Elena?\"", "vera_elena",
              [](const GameState &gs)
              { return gs.quest.met_elena; }, nullptr},
             {"\"You seem to know everyone. How?\"", "vera_connections", nullptr, nullptr}});

    addNode(state, "vera_goods", "Merchant Vera",
            "\"*She sweeps her hand across the stall proudly.*\n"
            "Silk scarves from the eastern provinces! Perfumes from the coast!\n"
            "Silver hair pins that would look divine on you, my lady. And for\n"
            "the discerning buyer, *she lowers her voice,* I have certain\n"
            "items that are harder to find through official channels.\"",
            {{"\"What kind of 'harder to find' items?\"", "vera_special", nullptr,
              [](GameState &gs)
              { gs.npcs["merchant_vera"].suspicion += 5; }},
             {"\"I'll take a silk scarf. (10 gold)\"", "vera_buy_scarf",
              [](const GameState &gs)
              { return gs.player.gold >= 10; }, nullptr},
             {"\"Just browsing, thank you.\"", "", nullptr, nullptr}});

    addNode(state, "vera_special", "Merchant Vera",
            "\"*She glances around, then leans closer.*\n"
            "Well, I occasionally come across... documents. Letters that went\n"
            "astray. Seals that can be replicated. And certain herbs that are\n"
            "not sold in the apothecary. *She winks.* All perfectly legal,\n"
            "naturally. Just rare.\"",
            {{"\"Interesting. I may need such things someday.\"", "vera_special_maybe",
              nullptr, nullptr},
             {"\"That sounds dangerous. I'll pass.\"", "", nullptr, nullptr}});

    addNode(state, "vera_special_maybe", "Merchant Vera",
            "\"*She nods knowingly.*\n"
            "When that day comes, my lady, you know where to find me. Vera\n"
            "never forgets a customer, especially one of your refinement.\n"
            "Just say the word, and I'll have what you need.\"",
            {{"\"I'll remember. Thank you, Vera.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 5;
                  std::cout << colored("  [i] Vera can procure 'special' items if needed.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "vera_buy_scarf", "Merchant Vera",
            "\"*She wraps a shimmering blue scarf in tissue paper.*\n"
            "An excellent choice, my lady! This silk was woven in the eastern\n"
            "provinces, where they say the silkworms feed on moonlit mulberry\n"
            "leaves. *She hands it to you with a flourish.* Wear it well.\"",
            {{"\"Thank you, Vera. It's lovely.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.player.gold -= 10;
                  gs.player.inventory.push_back("silk_scarf");
                  gs.player.reputation = std::min(100, gs.player.reputation + 2);
                  std::cout << colored("  Acquired: Silk Scarf (-10 gold)", ansi::BRIGHT_GREEN) << "\n";
                  std::cout << colored("  Reputation +2 (wearing fine accessories)", ansi::GREEN) << "\n";
              }}},
            true);

    addNode(state, "vera_info", "Merchant Vera",
            "\"*She arches an eyebrow.*\n"
            "Information? Now that, my lady, is my most valuable commodity.\n"
            "A merchant hears everything, customers talk while they shop,\n"
            "servants gossip while they haggle. I know who owes money to whom,\n"
            "who is sleeping with whose spouse, and who has been buying arsenic\n"
            "from the apothecary. *She grins.* What would you like to know?\"",
            {{"\"Who's been buying arsenic?\"", "vera_arsenic", nullptr,
              [](GameState &gs)
              { gs.npcs["merchant_vera"].suspicion += 5; }},
             {"\"What are the servants saying about the Aldric family?\"",
              "vera_aldric_servants", nullptr, nullptr},
             {"\"Who controls the black market around here?\"", "vera_black_market",
              nullptr, nullptr}});

    addNode(state, "vera_arsenic", "Merchant Vera",
            "\"*She chuckles.*\n"
            "Oh, that got your attention? Don't worry, it's mostly old women\n"
            "buying rat poison. Mostly. *She pauses meaningfully.* But there\n"
            "was one curious purchase last month. A well-dressed servant, could\n"
            "not place the house, bought a quantity better suited for something\n"
            "larger than rats. Make of that what you will, my lady.\"",
            {{"\"Can you describe this servant?\"", "vera_servant_desc", nullptr, nullptr},
             {"\"That's troubling. Thank you for the warning.\"", "", nullptr, nullptr}});

    addNode(state, "vera_servant_desc", "Merchant Vera",
            "\"Tall, dark hair, well-groomed, spoke with a slight northern accent.\n"
            "Paid in silver, which is unusual for servants. Whoever they work\n"
            "for has deep pockets. *She shrugs.* Beyond that, I can't say.\n"
            "But if I see them again, I'll make note of it, for a friend's\n"
            "sake.\"",
            {{"\"Please do. I appreciate it, Vera.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 5;
                  std::cout << colored("  [i] Someone's servant bought a suspicious amount of arsenic.", ansi::BRIGHT_YELLOW) << "\n";
              }}},
            true);

    addNode(state, "vera_aldric_servants", "Merchant Vera",
            "\"*She leans in conspiratorially.*\n"
            "Your household servants are mostly loyal, though your father's new\n"
            "guest has caused quite a stir. The older servants resent having to\n"
            "serve a commoner. The younger ones think Elena is charming. It's\n"
            "a split right down the middle, my lady. You might want to shore\n"
            "up the loyalists before the other side grows.\"",
            {{"\"Which servants are loyal to me?\"", "vera_loyal_servants", nullptr, nullptr},
             {"\"And the ones who favor Elena?\"", "vera_elena_servants", nullptr, nullptr}});

    addNode(state, "vera_loyal_servants", "Merchant Vera",
            "\"Your butler, Graves, is solid as stone. The cook, Marcel,\n"
            "complains about the extra work but respects the family. Old\n"
            "Hannah the seamstress has served three generations of Aldrics\n"
            "and won't hear a word against you. Keep them close, my lady.\n"
            "Loyalty is worth more than gold.\"",
            {{"\"Thank you, Vera. That's good to know.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 5;
                  std::cout << colored("  [i] Graves, Marcel, and Hannah are loyal to the Aldric family.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "vera_elena_servants", "Merchant Vera",
            "\"The young footman, Peter, practically trips over himself when\n"
            "Elena walks by. A kitchen maid named Lily has been seen running\n"
            "errands for her. And Clara the maid, well, Clara gossips about\n"
            "everything, but she's been more favorable toward Elena lately.\n"
            "People are charmed by novelty, my lady. Give them something\n"
            "better to be charmed by: you.\"",
            {{"\"I intend to. Thank you, Vera.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Some servants are being swayed by Elena's charm.", ansi::BRIGHT_YELLOW) << "\n";
              }}},
            true);

    addNode(state, "vera_black_market", "Merchant Vera",
            "\"*She crosses her arms.*\n"
            "Control is a strong word. The alleyways behind the plaza have a\n"
            "certain economy of their own. No one 'controls' it, but a man\n"
            "called Crooked Tam acts as a middleman for most transactions.\n"
            "Dangerous fellow, but reliable in his way. *She looks at you\n"
            "seriously.* I wouldn't recommend a lady of your standing visiting\n"
            "that world, but I can act as a go-between, for a small fee.\"",
            {{"\"I may take you up on that offer.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 5;
                  std::cout << colored("  [i] Vera can connect you to the black market.", ansi::BRIGHT_CYAN) << "\n";
              }},
             {"\"I'll stay in the light, thank you.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "vera_gossip", "Merchant Vera",
            "\"*She grins broadly.*\n"
            "Oh, where to begin? The Harvest Festival is next month and everyone\n"
            "is jockeying for the best positions. Baron Whitmore lost a fortune\n"
            "at the Golden Chalice last week, his wife is furious. And there's\n"
            "talk of a new tax on imported silks, which would ruin me.\"",
            {{"\"What about the nobles? Any interesting politics?\"",
              "vera_gossip_nobles", nullptr, nullptr},
             {"\"Has Elena been seen in the city?\"", "vera_gossip_elena",
              [](const GameState &gs)
              { return gs.quest.met_elena; }, nullptr},
             {"\"That's quite enough gossip. Thank you.\"", "", nullptr, nullptr}});

    addNode(state, "vera_gossip_nobles", "Merchant Vera",
            "\"The big talk is about the upcoming Royal Ball. Every noble family\n"
            "will be vying for the Prince's attention. Rumor has it that Elena\n"
            "has been invited as a special guest, which has ruffled more than\n"
            "a few feathers. Baroness Vivienne in the Noble Quarter is\n"
            "particularly vocal about it.\"",
            {{"\"Elena at the Royal Ball? That's outrageous.\"", "vera_ball_outrage",
              nullptr, nullptr},
             {"\"The Baroness sounds like someone I should meet.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Baroness Vivienne in the Noble Quarter may share your concerns.", ansi::BRIGHT_CYAN) << "\n";
              }}});

    addNode(state, "vera_ball_outrage", "Merchant Vera",
            "\"Many agree with you, my lady. A commoner at the Royal Ball?\n"
            "It threatens the very order of things. But Elena has powerful\n"
            "friends. If you want to stop her invitation, you'd need to move\n"
            "quickly and carefully. *She leans closer.* Or make sure her\n"
            "appearance there works against her rather than for her.\"",
            {{"\"That's an interesting thought. Thank you, Vera.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] The Royal Ball could be an opportunity to undermine Elena.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "vera_gossip_elena", "Merchant Vera",
            "\"Oh yes, quite frequently now. She shops here, visits the bookshop,\n"
            "even stopped by the bakery to buy sweets for the orphanage. *She\n"
            "rolls her eyes.* Always performing, that one. But I'll say this,\n"
            "the common folk love her. She remembers names, asks about children,\n"
            "compliments the merchandise. She's good, my lady. Very good.\"",
            {{"\"Better than me?\"", "vera_compare", nullptr, nullptr},
             {"\"Everyone has a weakness.\"", "", nullptr, nullptr}});

    addNode(state, "vera_compare", "Merchant Vera",
            "\"*She considers carefully.*\n"
            "Different. Elena charms downward, making commoners feel seen. You\n"
            "have the natural authority that comes from breeding. Your strength\n"
            "is command, hers is seduction. The question is which the people\n"
            "value more when the music stops.\"",
            {{"\"I'll make sure they value the right thing.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["merchant_vera"].affection += 5; }}},
            true);

    addNode(state, "vera_elena", "Merchant Vera",
            "\"*She lowers her voice.*\n"
            "Elena? That girl is a force of nature, I'll give her that. She\n"
            "came through my stall last week, charmed me into giving her a\n"
            "discount I've never given anyone. I was halfway through wrapping\n"
            "the package before I realized what happened. *She shakes her\n"
            "head.* Careful with that one, my lady.\"",
            {{"\"She charmed you? Vera, I'm disappointed.\"", "vera_elena_charmed",
              nullptr, nullptr},
             {"\"What did she buy?\"", "vera_elena_purchase", nullptr, nullptr},
             {"\"I need to know everything you've heard about her.\"",
              "vera_elena_everything", nullptr,
              [](GameState &gs)
              { gs.npcs["merchant_vera"].suspicion += 5; }}});

    addNode(state, "vera_elena_charmed", "Merchant Vera",
            "\"*She laughs.*\n"
            "Don't be! It won't happen again. But that's my point, she has a\n"
            "gift for making you feel like the most important person in the\n"
            "world, even when she's taking your money. Imagine what she does\n"
            "to nobles with actual power to give.\"",
            {{"\"A dangerous gift indeed.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "vera_elena_purchase", "Merchant Vera",
            "\"Writing paper, fine quality. A small bottle of violet ink. And\n"
            "a set of wax sealing tools. *She raises an eyebrow.* That girl\n"
            "is writing letters, my lady. Lots of them. To whom, I wonder?\"",
            {{"\"That IS interesting. Letters to whom, indeed.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena has been buying letter-writing supplies.", ansi::BRIGHT_CYAN) << "\n";
                  std::cout << colored("      She may be building a correspondence network.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "vera_elena_everything", "Merchant Vera",
            "\"*She sighs.*\n"
            "Everything? She's been visiting the Academy, the Cathedral, and\n"
            "the Noble Quarter. She donates to charity, studies diligently,\n"
            "and prays devoutly. On the surface, she's a saint. But, and this\n"
            "is just Vera's intuition, no one is that perfect without trying\n"
            "very hard to appear so. The question is what she's hiding beneath\n"
            "all that polish.\"",
            {{"\"Exactly what I intend to find out.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 5;
              }}},
            true);

    addNode(state, "vera_connections", "Merchant Vera",
            "\"*She grins proudly.*\n"
            "I've been trading in this plaza for fifteen years, my lady. You\n"
            "learn everyone's name, their habits, their secrets. A merchant who\n"
            "only sells goods is a poor merchant indeed. I sell trust, and that\n"
            "is far more valuable. *She winks.* If you need eyes and ears in\n"
            "the city, Vera is your woman.\"",
            {{"\"I could use a friend in the city.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["merchant_vera"].affection += 10;
                  std::cout << colored("  [i] Merchant Vera is now a contact in the city.", ansi::BRIGHT_GREEN) << "\n";
              }},
             {"\"I'll keep that in mind.\"", "", nullptr, nullptr}},
            true);
}
