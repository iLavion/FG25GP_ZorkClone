#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerMadameFortuna(GameState &state)
{
        NPC n;
        n.id = "madame_fortuna";
        n.name = "Madame Fortuna";
        n.title = "Casino Proprietress";
        n.description = "An enigmatic woman draped in silks of deep purple and gold. Her\n"
                        "dark eyes seem to read your very soul. She shuffles her cards with\n"
                        "impossible elegance, each movement precise and mesmerizing.";
        n.current_room = "city_casino";
        n.affection = 20;
        n.suspicion = 0;
        n.disposition = Disposition::Neutral;
        n.dialogue_root = "fortuna_root";
        n.traits = {Trait::Perceptive};
        n.schedule = {
            {10, "city_casino"},
            {22, "city_alleyways"},
            {23, "city_casino"},
        };
        n.associates = {"merchant_vera", "baroness_vivienne"};
        state.npcs[n.id] = n;
        if (state.rooms.count(n.current_room))
        {
                state.rooms[n.current_room].npc_ids.push_back(n.id);
        }

        addNode(state, "fortuna_root", "Madame Fortuna",
                "\"*She fans her cards across the table and looks up at you with knowing eyes.*\n"
                "Welcome, Lady Seraphina. The cards told me you would come today.\n"
                "What brings a noblewoman to my humble establishment?\"",
                {{"\"I'm here to test my luck.\"", "fortuna_luck", nullptr, nullptr},
                 {"\"I've heard you know things. Tell me about Elena.\"", "fortuna_elena",
                  [](const GameState &gs)
                  { return gs.quest.met_elena; },
                  nullptr},
                 {"\"Who are you, really?\"", "fortuna_identity", nullptr, nullptr},
                 {"\"I need information about the nobles who frequent this place.\"",
                  "fortuna_nobles", nullptr, nullptr},
                 {"\"Tell me my fortune.\"", "fortuna_reading", nullptr, nullptr}});

        addNode(state, "fortuna_luck", "Madame Fortuna",
                "\"*She chuckles, a rich warm sound.*\n"
                "Luck? There is no such thing, my lady. There is only fate, and how\n"
                "cleverly we dance with it. But if you wish to dance, my tables are\n"
                "open. Crown's Fortune is the game of choice among the discerning.\"",
                {{"\"How does Crown's Fortune work?\"", "fortuna_rules", nullptr, nullptr},
                 {"\"What are the stakes?\"", "fortuna_stakes", nullptr, nullptr}});

        addNode(state, "fortuna_rules", "Madame Fortuna",
                "\"*She holds up two cards.*\n"
                "Simple, my lady. We each draw a card, numbered one through ten.\n"
                "The Crown is the highest, the Ace the lowest. Higher card wins.\n"
                "A tie returns your wager. It is a game of pure fate, nothing more,\n"
                "nothing less. *She winks.* Unless you believe in destiny.\"",
                {{"\"I see. Thank you.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_stakes", "Madame Fortuna",
                "\"*She taps the table with a painted nail.*\n"
                "Five, ten, or twenty-five gold per hand. Some nobles have lost\n"
                "fortunes here. Others have built them. The cards do not discriminate\n"
                "between duke and beggar, my lady. That is their beauty.\"",
                {{"\"Interesting. I'll keep that in mind.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_elena", "Madame Fortuna",
                "\"*Her expression shifts, something guarded entering her eyes.*\n"
                "Ah, the young heroine. She has been here, once or twice. Charming girl.\n"
                "The nobles adore her, the merchants give her credit, and the servants\n"
                "whisper her name like a prayer.\"",
                {{"\"You sound almost impressed.\"", "fortuna_elena_impressed", nullptr, nullptr},
                 {"\"Does she have any weaknesses?\"", "fortuna_elena_weakness", nullptr,
                  [](GameState &gs)
                  { gs.npcs["madame_fortuna"].suspicion += 5; }},
                 {"\"Has she been gambling here?\"", "fortuna_elena_gambling", nullptr, nullptr}});

        addNode(state, "fortuna_elena_impressed", "Madame Fortuna",
                "\"Impressed? *She laughs.* I am a reader of people, my lady. That girl\n"
                "has something burning inside her, an ambition wrapped in sweetness.\n"
                "She reminds me of someone I knew long ago. *She pauses, lost in\n"
                "thought.* Be careful with her. Flowers with the deepest roots are\n"
                "hardest to pull.\"",
                {{"\"An interesting metaphor.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_elena_weakness", "Madame Fortuna",
                "\"*She leans in close, lowering her voice.*\n"
                "Weaknesses? Everyone has them, my lady. Elena's is her pride disguised\n"
                "as humility. She cannot bear to be seen as anything less than virtuous.\n"
                "If her image cracks, even slightly, she will scramble to repair it.\n"
                "That scramble, that is when she makes mistakes.\"",
                {{"\"That's very useful. Thank you, Fortuna.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["madame_fortuna"].affection += 5;
                          std::cout << colored("  [i] You've learned about Elena's weakness: her public image.", ansi::BRIGHT_CYAN) << "\n";
                  }},
                 {"\"You seem to know a great deal about people's weaknesses.\"",
                  "fortuna_elena_weakness_follow", nullptr, nullptr}});

        addNode(state, "fortuna_elena_weakness_follow", "Madame Fortuna",
                "\"*She smiles enigmatically.*\n"
                "It is my trade, my lady. Cards tell truth, people tell stories.\n"
                "I simply learn to read both. *She shuffles her deck.* Now, was\n"
                "there anything else, or shall we let the cards decide the rest?\"",
                {{"\"That will be all for now.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_elena_gambling", "Madame Fortuna",
                "\"*She smirks.*\n"
                "Once. She played cautiously, small bets. Won a little, lost a little.\n"
                "But what was interesting is who she came with, a young baron's son.\n"
                "He was quite smitten. She barely noticed him. Her eyes were on a\n"
                "merchant counting his coins. Always watching the money, that one.\"",
                {{"\"A baron's son? Which one?\"", "fortuna_elena_baron", nullptr, nullptr},
                 {"\"Watching the money... interesting.\"", "", nullptr, nullptr}});

        addNode(state, "fortuna_elena_baron", "Madame Fortuna",
                "\"Young Lord Fairfax. Pleasant enough boy, no spine to speak of.\n"
                "He would do anything Elena asked, which is precisely why she keeps\n"
                "him close. A useful admirer is worth more than gold in the right\n"
                "circles, wouldn't you agree, my lady? *She winks.*\"",
                {{"\"I know the type. Thank you, Fortuna.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] Elena has admirers she uses for influence.", ansi::BRIGHT_CYAN) << "\n";
                  }}},
                true);

        addNode(state, "fortuna_identity", "Madame Fortuna",
                "\"*She sets down her cards and meets your eyes directly.*\n"
                "Who am I? I am Fortuna. That is all anyone needs to know.\n"
                "*A pause.* But since you ask with such earnestness... I was once\n"
                "a lady of a lesser house. Politics took my title, the cards gave\n"
                "me a new one. We are not so different, you and I.\"",
                {{"\"A fallen noblewoman? I'm sorry.\"", "fortuna_past_sympathy", nullptr,
                  [](GameState &gs)
                  { gs.npcs["madame_fortuna"].affection += 10; }},
                 {"\"Is that why you understand the nobility so well?\"",
                  "fortuna_past_insight", nullptr, nullptr}});

        addNode(state, "fortuna_past_sympathy", "Madame Fortuna",
                "\"*For the first time, genuine emotion flickers across her face.*\n"
                "Don't be sorry. I am freer now than I ever was wearing silk in\n"
                "gilded halls. *She touches her deck.* These cards saved me. Perhaps\n"
                "someday, if you need saving, they'll save you too.\"",
                {{"\"I hope it never comes to that.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_past_insight", "Madame Fortuna",
                "\"*She nods slowly.*\n"
                "Precisely. I have been both the player and the card. I know how\n"
                "the game is played from every angle. That is why the nobles come\n"
                "to me, not just for gold, but for truth they cannot find elsewhere.\"",
                {{"\"A valuable perspective.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "fortuna_nobles", "Madame Fortuna",
                "\"*She glances around the room, then back at you.*\n"
                "The nobles? They come here to be someone other than who they are.\n"
                "Baron Whitmore gambles away his wife's inheritance. Countess Ashford\n"
                "comes to meet a certain guardsman. And Lord Pemberton... well, he\n"
                "simply likes to lose. What specifically interests you?\"",
                {{"\"Who has been talking about Elena?\"", "fortuna_nobles_elena", nullptr, nullptr},
                 {"\"Who might be useful to my cause?\"", "fortuna_nobles_useful", nullptr,
                  [](GameState &gs)
                  { gs.npcs["madame_fortuna"].suspicion += 5; }},
                 {"\"I was just curious. Thank you.\"", "", nullptr, nullptr}});

        addNode(state, "fortuna_nobles_elena", "Madame Fortuna",
                "\"Everyone, my lady. That is precisely the problem, isn't it?\n"
                "She is the talk of every table. The young admire her beauty, the\n"
                "old admire her manners, and the envious admire her rise. You would\n"
                "need to give them something else to talk about.\"",
                {{"\"Like a scandal?\"", "fortuna_nobles_scandal", nullptr, nullptr},
                 {"\"Or perhaps my own accomplishments.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] Fortuna nods approvingly.", ansi::GREEN) << "\n";
                  }}});

        addNode(state, "fortuna_nobles_scandal", "Madame Fortuna",
                "\"*Her eyes gleam.*\n"
                "A scandal is a powerful thing, my lady. But it cuts both ways.\n"
                "If it can be traced to you, you become the villain of the story\n"
                "rather than the heroine. *She taps the table.* If you want a\n"
                "scandal, make sure it looks like it found itself.\"",
                {{"\"Sound advice. Thank you, Fortuna.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["madame_fortuna"].affection += 5;
                          std::cout << colored("  [i] Fortuna's advice: scandals must appear natural.", ansi::BRIGHT_CYAN) << "\n";
                  }}},
                true);

        addNode(state, "fortuna_nobles_useful", "Madame Fortuna",
                "\"*She considers for a moment.*\n"
                "Useful is a dangerous word. But if you seek allies... Baroness\n"
                "Vivienne in the Noble Quarter shares your, shall we say, concern\n"
                "about rising commoners. And the Scholar at the Academy knows things\n"
                "about bloodlines that could prove embarrassing for certain people.\"",
                {{"\"Baroness Vivienne and a scholar. I'll remember that.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] Fortuna suggests seeking Baroness Vivienne and the Academy Scholar.", ansi::BRIGHT_CYAN) << "\n";
                  }}},
                true);

        addNode(state, "fortuna_reading", "Madame Fortuna",
                "\"*She produces an ornate set of cards, smaller than her gaming deck.*\n"
                "Very well, my lady. Let us see what fate has written for you.\n"
                "*She draws three cards and lays them face down.*\"",
                {{"\"Turn the first card.\"", "fortuna_reading_first", nullptr, nullptr}});

        addNode(state, "fortuna_reading_first", "Madame Fortuna",
                "\"*She flips the first card: a woman in a crown of thorns.*\n"
                "The Burdened Queen. You carry a weight that is not yours alone.\n"
                "Family, duty, legacy. These chains are also your strength, my lady.\n"
                "Do not mistake the weight for weakness.\"",
                {{"\"Turn the second card.\"", "fortuna_reading_second", nullptr, nullptr}});

        addNode(state, "fortuna_reading_second", "Madame Fortuna",
                "\"*The second card reveals a mirror reflecting two faces.*\n"
                "The Double Mirror. You and your rival are more alike than either\n"
                "would admit. The same fire burns in both of you. The question is\n"
                "not who is stronger, but who is wiser.\"",
                {{"\"And the final card?\"", "fortuna_reading_third", nullptr, nullptr}});

        addNode(state, "fortuna_reading_third", "Madame Fortuna",
                "\"*She hesitates, then turns the last card. It shows a crossroads\n"
                "under a full moon.*\n"
                "The Moonlit Path. A choice approaches, my lady. One road leads to\n"
                "power, the other to peace. Neither is wrong, but both demand\n"
                "sacrifice. *She meets your eyes.* Choose wisely when the time comes.\"",
                {{"\"Thank you, Fortuna. That was... enlightening.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["madame_fortuna"].affection += 5;
                  }},
                 {"\"Pretty words. Do you actually believe in these cards?\"", "fortuna_reading_belief",
                  nullptr, nullptr}});

        addNode(state, "fortuna_reading_belief", "Madame Fortuna",
                "\"*She gathers her cards with a sad smile.*\n"
                "Belief is irrelevant, my lady. The cards are a mirror. People see\n"
                "in them what they already know but fear to admit. Whether the\n"
                "magic is in the cards or in the truth they reveal, the result\n"
                "is the same. *She tucks the deck away.* Good luck, Lady Seraphina.\"",
                {{"\"Good luck to you too, Fortuna.\"", "", nullptr, nullptr}},
                true);
}