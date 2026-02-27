#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerScholarElias(GameState &state)
{
    NPC n;
    n.id = "scholar_elias";
    n.name = "Scholar Elias";
    n.title = "Academy Historian";
    n.description = "A lean man with spectacles perched on his nose and ink stains on his\n"
                    "fingers. His robes are slightly rumpled, and books spill from every\n"
                    "pocket. Despite his disheveled appearance, his eyes are sharp and miss\n"
                    "nothing.";
    n.current_room = "academy_archive";
    n.affection = 15;
    n.suspicion = 0;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "elias_root";
    n.traits = {Trait::Perceptive};
    n.schedule = {
        {7, "academy_courtyard"},
        {8, "academy_lecture_hall"},
        {10, "academy_archive"},
        {12, "academy_courtyard"},
        {13, "academy_archive"},
        {17, "academy_rooftop_garden"},
        {19, "academy_lecture_hall"},
        {21, "academy_dormitory"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
    {
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    }

    addNode(state, "elias_root", "Scholar Elias",
            "\"*He looks up from an enormous tome, adjusting his spectacles.*\n"
            "Ah, Lady Seraphina! I was just reading about your family's lineage.\n"
            "The Aldric line stretches back fourteen generations, did you know?\n"
            "Quite fascinating. What brings you to the archive?\"",
            {{"\"I'm interested in my family's history.\"", "elias_aldric_history",
              nullptr, nullptr},
             {"\"I'd like to know more about Elena's background.\"", "elias_elena",
              [](const GameState &gs)
              { return gs.quest.met_elena; },
              [](GameState &gs)
              { gs.npcs["scholar_elias"].suspicion += 5; }},
             {"\"What do you know about noble politics?\"", "elias_politics",
              nullptr, nullptr},
             {"\"I need help with some research.\"", "elias_research",
              nullptr, nullptr},
             {"\"Tell me about the Academy.\"", "elias_academy", nullptr, nullptr}});

    addNode(state, "elias_aldric_history", "Scholar Elias",
            "\"*His eyes light up with academic passion.*\n"
            "Oh, splendid! The Aldric family has served the Crown since the founding\n"
            "wars. Your ancestor, Lord Aldric the First, held the eastern border\n"
            "against three separate invasions. Your family's motto, 'Unwavering\n"
            "in Purpose,' was earned in blood, my lady.\"",
            {{"\"And what of the family's political influence?\"", "elias_aldric_politics",
              nullptr, nullptr},
             {"\"Are there any... controversial chapters?\"", "elias_aldric_secrets",
              nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].suspicion += 5; }},
             {"\"Thank you, that's inspiring.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.player.reputation = std::min(100, gs.player.reputation + 2);
                  std::cout << colored("  [i] Knowing your family's proud history strengthens your resolve. Reputation +2", ansi::GREEN) << "\n";
              }}});

    addNode(state, "elias_aldric_politics", "Scholar Elias",
            "\"The Aldric family has traditionally held the Duke's Council seat with\n"
            "honor. Your father is well-respected, though some newer noble houses\n"
            "have been agitating for reform. *He lowers his voice.* The rise of\n"
            "commoners to prominence has made certain old families... nervous.\"",
            {{"\"Nervous how?\"", "elias_aldric_nervous", nullptr, nullptr},
             {"\"My father can handle politics.\"", "", nullptr, nullptr}});

    addNode(state, "elias_aldric_nervous", "Scholar Elias",
            "\"*He glances around before continuing.*\n"
            "When a commoner like Elena gains the favor of powerful nobles, it\n"
            "disrupts the order of things. Old families see their influence\n"
            "diluted. Some react with grace, others with... less admirable means.\n"
            "History shows us that these tensions usually resolve in one of two\n"
            "ways: integration or elimination. Neither is painless.\"",
            {{"\"A sobering lesson. Thank you, Elias.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "elias_aldric_secrets", "Scholar Elias",
            "\"*He shifts uncomfortably.*\n"
            "Controversial? Well, every great house has its shadows. Your\n"
            "great-grandmother, Lady Isolde, was rumored to have... removed\n"
            "a rival suitor from the picture. The records are vague, perhaps\n"
            "intentionally so. *He coughs.* But that was generations ago.\"",
            {{"\"Removed? You mean she had someone killed?\"", "elias_isolde", nullptr, nullptr},
             {"\"The past is the past. Thank you.\"", "", nullptr, nullptr}});

    addNode(state, "elias_isolde", "Scholar Elias",
            "\"*He pulls out a worn journal.*\n"
            "The official record says Lady Isolde's rival 'departed the realm.'\n"
            "But a personal diary, which I found in these very archives, suggests\n"
            "she orchestrated a scandal that forced the woman's family into exile.\n"
            "Brilliant, ruthless, and entirely deniable. *He looks at you\n"
            "meaningfully.* It seems the Aldric women have always known how\n"
            "to protect what is theirs.\"",
            {{"\"*A slight smile crosses your face.* How very interesting.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Your ancestor Lady Isolde defeated a rival through scandal.", ansi::BRIGHT_CYAN) << "\n";
                  std::cout << colored("      Perhaps history offers lessons for the present.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "elias_elena", "Scholar Elias",
            "\"*He pauses, setting down his quill.*\n"
            "Elena? The heroine everyone is talking about? I have done some\n"
            "research, actually. Academic curiosity, you understand. Her rise\n"
            "from common birth to noble favor is, shall we say, statistically\n"
            "unusual.\"",
            {{"\"What do you mean, 'statistically unusual'?\"", "elias_elena_unusual",
              nullptr, nullptr},
             {"\"Do you know anything about her family?\"", "elias_elena_family",
              nullptr, nullptr},
             {"\"Has she been attending classes here?\"", "elias_elena_classes",
              nullptr, nullptr}});

    addNode(state, "elias_elena_unusual", "Scholar Elias",
            "\"*He adjusts his spectacles.*\n"
            "In the last two hundred years of records, only three commoners have\n"
            "risen to noble prominence without marriage or military service.\n"
            "Elena would be the fourth. Each of the previous three had a patron,\n"
            "someone of considerable power who orchestrated their rise. The\n"
            "question is: who is Elena's patron? Your father, or someone else?\"",
            {{"\"You think someone is behind her rise?\"", "elias_elena_patron", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].suspicion += 5; }},
             {"\"Perhaps she's simply exceptional.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].affection += 5; }}});

    addNode(state, "elias_elena_patron", "Scholar Elias",
            "\"*He speaks carefully.*\n"
            "I am a historian, not a spy. I observe patterns. And the pattern\n"
            "here suggests that Elena's rise is too smooth, too perfectly timed.\n"
            "She arrives just as the social season begins, charms exactly the\n"
            "right people in exactly the right order. Either she is a genius\n"
            "of social manipulation, or she has a very good teacher.\"",
            {{"\"I need to find out who. Thank you, Elias.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elias suspects someone is orchestrating Elena's rise.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "elias_elena_family", "Scholar Elias",
            "\"*He pulls out a folder of notes.*\n"
            "Her mother, a seamstress named Margot, is still alive in a southern\n"
            "village. Her father, a merchant named Thomas, died three years ago.\n"
            "But here is the curious part: Thomas's trading routes included some\n"
            "very high-profile noble estates. He was not just any merchant. He\n"
            "supplied luxury goods to the aristocracy.\"",
            {{"\"So Elena grew up around nobles, even as a commoner?\"", "elias_elena_exposed",
              nullptr, nullptr},
             {"\"That's useful background. Thank you.\"", "", nullptr, nullptr}});

    addNode(state, "elias_elena_exposed", "Scholar Elias",
            "\"Precisely. She would have observed noble manners, speech patterns,\n"
            "social customs, all from a young age. The 'natural grace' everyone\n"
            "admires? It was learned, carefully and deliberately. I do not say\n"
            "this to diminish her, mind you. It is impressive. But it is not\n"
            "the innocent fairy tale she presents to the world.\"",
            {{"\"The mask slips, if you know where to look.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena's 'natural' graces were learned from observing nobles.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "elias_elena_classes", "Scholar Elias",
            "\"Yes, she enrolled two weeks ago. Literature, etiquette, and,\n"
            "interestingly, political history. She is a quick study, I'll grant\n"
            "her that. The professors adore her. She asks all the right\n"
            "questions. *He pauses.* Perhaps too perfectly right.\"",
            {{"\"Has she made friends among the students?\"", "elias_elena_students",
              nullptr, nullptr},
             {"\"Political history? What is she studying?\"", "elias_elena_polhist",
              nullptr, nullptr}});

    addNode(state, "elias_elena_students", "Scholar Elias",
            "\"Several, actually. Mostly children of lesser nobles who see her\n"
            "as exotic and exciting. She has a talent for making people feel\n"
            "special. *He smiles wryly.* Rather like a mirror that shows\n"
            "everyone their best reflection.\"",
            {{"\"A mirror. Yes, that's exactly what she is.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "elias_elena_polhist", "Scholar Elias",
            "\"She's been reading about succession disputes, noble house mergers,\n"
            "and the legal rights of adopted commoners. *He raises an eyebrow.*\n"
            "Curious choices for someone who claims to be content as a guest.\"",
            {{"\"Very curious indeed. Thank you, Elias.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena is studying adoption law and noble succession.", ansi::BRIGHT_CYAN) << "\n";
                  std::cout << colored("      She may be planning a permanent place in the nobility.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "elias_politics", "Scholar Elias",
            "\"*He brightens considerably.*\n"
            "Noble politics! My favorite subject. What aspect interests you?\n"
            "Court intrigue, the balance of houses, or perhaps the art of\n"
            "reputation management?\"",
            {{"\"Reputation management. How does one build a flawless image?\"",
              "elias_reputation", nullptr, nullptr},
             {"\"The art of undermining a rival without getting caught.\"",
              "elias_undermining", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].suspicion += 10; }},
             {"\"The balance of noble houses and how it shifts.\"",
              "elias_balance", nullptr, nullptr}});

    addNode(state, "elias_reputation", "Scholar Elias",
            "\"*He counts on his fingers.*\n"
            "Three pillars of noble reputation: visibility, consistency, and\n"
            "association. Be seen doing good works. Never contradict your public\n"
            "persona. And surround yourself with people of impeccable character.\n"
            "The nobility is a performance, my lady. The audience must never\n"
            "see the stage crew.\"",
            {{"\"Sound advice. I'll remember it.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.player.reputation = std::min(100, gs.player.reputation + 3);
                  std::cout << colored("  [i] Elias's lessons on reputation give you new confidence. Reputation +3", ansi::GREEN) << "\n";
              }}},
            true);

    addNode(state, "elias_undermining", "Scholar Elias",
            "\"*He glances around nervously.*\n"
            "My lady, I am a historian, not a schemer. But, historically speaking,\n"
            "the most effective methods involve information. A well-timed revelation,\n"
            "a letter that falls into the wrong hands, a witness who remembers\n"
            "something inconvenient. *He coughs.* Hypothetically, of course.\"",
            {{"\"Of course. Purely academic.\"", "elias_undermining_academic", nullptr, nullptr},
             {"\"Would you be willing to help me research someone?\"",
              "elias_help_research", nullptr, nullptr}});

    addNode(state, "elias_undermining_academic", "Scholar Elias",
            "\"*He nods, relieved.*\n"
            "Yes, purely academic. The archive here contains records on most\n"
            "noble families and their... entanglements. If there is something\n"
            "to find about anyone, it would be here. *He gestures at the\n"
            "towering shelves.* The past never truly stays buried, my lady.\"",
            {{"\"Good to know. Thank you, Elias.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "elias_help_research", "Scholar Elias",
            "\"*He hesitates, then nods slowly.*\n"
            "I, I suppose I could look into certain matters. Strictly as\n"
            "academic research, you understand. What would you like me to\n"
            "investigate?\"",
            {{"\"Elena's family connections, anything unusual in her past.\"",
              "elias_research_elena", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].affection += 5; }},
             {"\"Never mind. I shouldn't involve you.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].affection += 3; }}});

    addNode(state, "elias_research_elena", "Scholar Elias",
            "\"*He pulls out a fresh notebook.*\n"
            "Very well. I will see what the records reveal about Elena's merchant\n"
            "father and his connections. It may take some time, but if there's\n"
            "anything there, I will find it. *He pauses.* Be careful, my lady.\n"
            "Knowledge is power, but it is also a burden.\"",
            {{"\"I can bear it. Thank you, Elias.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["scholar_elias"].affection += 10;
                  std::cout << colored("  [i] Scholar Elias will investigate Elena's background.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "elias_balance", "Scholar Elias",
            "\"The balance of houses is a delicate thing. Currently, four major\n"
            "families hold sway: Aldric, Ashworth, Beaumont, and Pemberton.\n"
            "Your family is strongest, but the Ashworths have been making moves.\n"
            "If Elena were to be adopted or married into a rival house, it\n"
            "could shift the balance dramatically.\"",
            {{"\"Could someone adopt Elena?\"", "elias_adoption", nullptr, nullptr},
             {"\"The Ashworths are making moves?\"", "elias_ashworths", nullptr, nullptr}});

    addNode(state, "elias_adoption", "Scholar Elias",
            "\"Legally, yes. Any noble of sufficient rank could petition for\n"
            "adoption. It would give Elena full noble status and, potentially,\n"
            "inheritance rights. *He looks at you carefully.* If someone were\n"
            "to adopt her before your father acts, it could create a very\n"
            "uncomfortable situation for the Aldric family.\"",
            {{"\"That must not happen.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena could gain full noble status through adoption.", ansi::BRIGHT_YELLOW) << "\n";
              }}},
            true);

    addNode(state, "elias_ashworths", "Scholar Elias",
            "\"Lord Ashworth has been courting favor with the newer noble\n"
            "families, building alliances. Interestingly, he has also been\n"
            "seen speaking with Elena at social events. Whether this is\n"
            "coincidence or strategy, I cannot say. But in politics, my lady,\n"
            "there are no coincidences.\"",
            {{"\"I'll keep an eye on the Ashworths. Thank you.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "elias_research", "Scholar Elias",
            "\"*He gestures at the archive proudly.*\n"
            "The Academy archive contains records dating back three centuries.\n"
            "Noble lineages, trade records, court proceedings, personal letters.\n"
            "If you need to know something about anyone of importance, the\n"
            "answer is likely somewhere in these shelves.\"",
            {{"\"Could I access the restricted section?\"", "elias_restricted",
              nullptr, nullptr},
             {"\"What's the most interesting thing you've found recently?\"",
              "elias_interesting", nullptr, nullptr}});

    addNode(state, "elias_restricted", "Scholar Elias",
            "\"*He winces.*\n"
            "The restricted section requires special authorization. However,\n"
            "*he glances around,* I have been known to, on occasion, assist\n"
            "scholars of noble birth with their research. Purely in the\n"
            "interest of academic freedom, of course.\"",
            {{"\"I would be grateful for your assistance, Elias.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["scholar_elias"].affection += 10;
                  std::cout << colored("  [i] Elias may grant you access to restricted records.", ansi::BRIGHT_CYAN) << "\n";
              }},
             {"\"I wouldn't want to get you in trouble.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "elias_interesting", "Scholar Elias",
            "\"*His eyes sparkle.*\n"
            "Just last week I found a collection of love letters between a\n"
            "duke and a foreign ambassador from eighty years ago! It completely\n"
            "recontextualizes the Treaty of Meridian. *He catches himself.*\n"
            "But I suppose that's not the sort of thing you're looking for.\n"
            "The archive also has records on recent arrivals to the capital,\n"
            "if that interests you more.\"",
            {{"\"Recent arrivals, like Elena?\"", "elias_elena",
              [](const GameState &gs)
              { return gs.quest.met_elena; },
              nullptr},
             {"\"The love letters sound fascinating, actually.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["scholar_elias"].affection += 10; }}});

    addNode(state, "elias_academy", "Scholar Elias",
            "\"The Royal Academy has educated the Empire's finest minds for\n"
            "over two centuries. We teach everything from swordsmanship to\n"
            "philosophy. The archive, where I spend most of my time, holds\n"
            "records that could reshape our understanding of history.\n"
            "*He pauses.* We also have an excellent rooftop garden, if\n"
            "you enjoy fresh air between studies.\"",
            {{"\"It sounds like a remarkable institution.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["scholar_elias"].affection += 3;
              }}},
            true);
}
