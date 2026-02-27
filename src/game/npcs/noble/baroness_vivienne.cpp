#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerBaronessVivienne(GameState &state)
{
        NPC n;
        n.id = "baroness_vivienne";
        n.name = "Baroness Vivienne";
        n.title = "Baroness of House Ashworth";
        n.description = "An elegant woman in her thirties with sharp cheekbones and piercing\n"
                        "blue eyes. She wears her auburn hair in an elaborate updo adorned\n"
                        "with sapphires. Her smile is warm but calculated, the expression of\n"
                        "someone who weighs every word before speaking it.";
        n.current_room = "noble_salon";
        n.affection = 15;
        n.suspicion = 0;
        n.disposition = Disposition::Neutral;
        n.dialogue_root = "vivienne_root";
        n.traits = {Trait::Perceptive};
        n.schedule = {
            {8, "noble_carriage_lane"},
            {9, "noble_salon"},
            {11, "noble_masquerade_hall"},
            {13, "noble_salon"},
            {15, "noble_diplomat"},
            {17, "noble_salon"},
            {19, "noble_masquerade_hall"},
            {21, "noble_rival_garden"},
            {23, "noble_salon"},
        };
        n.associates = {"merchant_vera", "madame_fortuna", "scholar_elias", "father_matthias"};
        state.npcs[n.id] = n;
        if (state.rooms.count(n.current_room))
        {
                state.rooms[n.current_room].npc_ids.push_back(n.id);
        }

        addNode(state, "vivienne_root", "Baroness Vivienne",
                "\"*She sets down her teacup with practiced grace and studies you.*\n"
                "Lady Seraphina. I've been hoping you would visit. Please, sit.\n"
                "We have much to discuss, I think. *She gestures to the seat beside\n"
                "her with a silk-gloved hand.*\"",
                {{"\"You've been expecting me?\"", "vivienne_expecting", nullptr, nullptr},
                 {"\"What did you want to discuss?\"", "vivienne_discuss", nullptr, nullptr},
                 {"\"I've heard you have concerns about Elena.\"", "vivienne_elena",
                  [](const GameState &gs)
                  { return gs.quest.met_elena; }, nullptr},
                 {"\"Tell me about yourself, Baroness.\"", "vivienne_herself", nullptr, nullptr},
                 {"\"I understand you have influence in the Noble Quarter.\"",
                  "vivienne_influence", nullptr, nullptr}});

        addNode(state, "vivienne_expecting", "Baroness Vivienne",
                "\"*She smiles, a cat-like expression.*\n"
                "Of course. When a commoner begins scaling the walls of our world,\n"
                "it is only natural that those at the top would seek out kindred\n"
                "spirits. You and I, Lady Seraphina, we understand what is at\n"
                "stake. The old families must stand together, or fall separately.\"",
                {{"\"You see Elena as a threat to the nobility?\"",
                  "vivienne_elena_threat", nullptr, nullptr},
                 {"\"I'm not sure I'd call us 'kindred spirits.'\"",
                  "vivienne_not_kindred", nullptr, nullptr}});

        addNode(state, "vivienne_elena_threat", "Baroness Vivienne",
                "\"A threat? *She laughs, but there's no humor in it.* She is a\n"
                "symptom, my dear. The disease is the idea that breeding and\n"
                "lineage no longer matter. That anyone with a pretty face and\n"
                "charming manner can claim a seat at our table. *Her eyes harden.*\n"
                "If Elena succeeds, a hundred more will follow. We must stop the\n"
                "flood before it begins.\"",
                {{"\"I agree. What do you propose?\"", "vivienne_propose", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 10; }},
                 {"\"That seems extreme. She's just one girl.\"", "vivienne_just_one",
                  nullptr, nullptr}});

        addNode(state, "vivienne_not_kindred", "Baroness Vivienne",
                "\"*She arches a perfect eyebrow.*\n"
                "No? Then tell me, Lady Seraphina, why did you come? Curiosity?\n"
                "Boredom? Or perhaps the same sinking feeling I had when I saw a\n"
                "commoner girl charming the prince at the last soiree? *She sips\n"
                "her tea.* We may not be kindred spirits yet, but circumstances\n"
                "have a way of creating alliances.\"",
                {{"\"Fair point. Perhaps we do share common ground.\"", "vivienne_common_ground",
                  nullptr, [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 5; }},
                 {"\"I came to understand the situation, nothing more.\"", "", nullptr, nullptr}});

        addNode(state, "vivienne_common_ground", "Baroness Vivienne",
                "\"*She smiles approvingly.*\n"
                "Now we are getting somewhere. Common ground is the foundation\n"
                "of every great alliance. Let us build on it. *She leans forward.*\n"
                "Tell me what you know about Elena, and I will tell you what I know.\n"
                "Together, we may see the whole picture.\"",
                {{"\"She's ambitious and calculating beneath the charm.\"",
                  "vivienne_share_elena", nullptr, nullptr},
                 {"\"I'd rather hear what you know first.\"", "vivienne_you_first",
                  nullptr, nullptr}});

        addNode(state, "vivienne_share_elena", "Baroness Vivienne",
                "\"*She nods.*\n"
                "Calculating. Yes, I've noticed that too. She never wastes a\n"
                "conversation. Every word is an investment. *She taps her chin.*\n"
                "What I can add is this: she has been corresponding with Lord\n"
                "Ashworth's younger brother. Letters, hand-delivered by a servant\n"
                "she thinks no one notices. *She smirks.* But I notice everything.\"",
                {{"\"Lord Ashworth's brother? Why?\"", "vivienne_ashworth_letters",
                  nullptr, nullptr},
                 {"\"Can you intercept these letters?\"", "vivienne_intercept",
                  nullptr, [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].suspicion += 5; }}});

        addNode(state, "vivienne_ashworth_letters", "Baroness Vivienne",
                "\"The younger Ashworth is on the Academy's admissions council.\n"
                "If Elena wants to study there officially, and I believe she does,\n"
                "she needs his support. But the letters seem, from what my sources\n"
                "tell me, more personal than professional. *Her eyes gleam.*\n"
                "A romantic entanglement, perhaps? That could be very useful.\"",
                {{"\"A scandal involving a noble's brother. That IS useful.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 10;
                          std::cout << colored("  [i] Elena may be romantically involved with young Lord Ashworth.", ansi::BRIGHT_CYAN) << "\n";
                  }},
                 {"\"We should be careful not to harm Lord Ashworth's family in the process.\"",
                  "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 3; }}},
                true);

        addNode(state, "vivienne_intercept", "Baroness Vivienne",
                "\"*She waves her hand dismissively.*\n"
                "Already done, my dear. Well, copies, at least. I have a very\n"
                "talented forger in my employ. The originals continue on their way,\n"
                "undisturbed. *She pulls a folded paper from her reticule.* This\n"
                "one is particularly interesting, a promise of 'undying devotion'\n"
                "from the young Ashworth. Written in code, poorly. Boys.\"",
                {{"\"Vivienne, I think this is the beginning of a beautiful alliance.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 15;
                          std::cout << colored("  [i] Baroness Vivienne has copies of Elena's correspondence.", ansi::BRIGHT_CYAN) << "\n";
                          std::cout << colored("      This could expose Elena's secret connections.", ansi::BRIGHT_CYAN) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_you_first", "Baroness Vivienne",
                "\"*She smiles, unsurprised.*\n"
                "Cautious. I respect that. Very well. *She sets down her teacup.*\n"
                "I know that Elena has been seen with the Prince's second secretary.\n"
                "I know she receives packages from outside the city, contents unknown.\n"
                "And I know that three noble families have already offered to sponsor\n"
                "her social debut. *She looks at you.* Your turn.\"",
                {{"\"Three families? Which ones?\"", "vivienne_three_families", nullptr, nullptr},
                 {"\"I know she's studying political history and adoption law at the Academy.\"",
                  "vivienne_adoption_law", nullptr, nullptr}});

        addNode(state, "vivienne_three_families", "Baroness Vivienne",
                "\"The Beaumonts, the Pemburtons, and, most worryingly, the Ashworths.\n"
                "If the Ashworths officially sponsor her, it gives her a pathway to\n"
                "legitimacy that is very difficult to challenge legally. *She looks\n"
                "at you intently.* The Ashworths are my husband's rivals in the\n"
                "northern trade routes. Anything that strengthens them weakens us.\n"
                "And you, by extension.\"",
                {{"\"Then we both have reason to act. What's your plan?\"",
                  "vivienne_propose", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 10; }}},
                true);

        addNode(state, "vivienne_adoption_law", "Baroness Vivienne",
                "\"*Her eyes widen slightly.*\n"
                "Adoption law? *She leans back, processing.* So she's not just seeking\n"
                "favor, she's seeking permanence. She wants to be legally adopted\n"
                "into a noble house. *She shakes her head.* That changes everything.\n"
                "This isn't a social climber, Lady Seraphina. This is a conqueror.\"",
                {{"\"Now you see why I'm concerned.\"", "vivienne_propose", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 15;
                          std::cout << colored("  [i] Sharing Elena's plans has earned Vivienne's full trust.", ansi::BRIGHT_GREEN) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_propose", "Baroness Vivienne",
                "\"*She straightens, all business now.*\n"
                "Here is what I propose. We coordinate our efforts. I will work the\n"
                "social angle, ensuring that the right ears hear the right whispers.\n"
                "You focus on undermining her support within your own household,\n"
                "your father's goodwill is her strongest asset. *She extends her\n"
                "hand.* Between us, we can ensure Elena's star rises no further.\n"
                "Do we have an accord?\"",
                {{"\"*Take her hand.* We have an accord, Baroness.\"",
                  "vivienne_alliance", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 20;
                  }},
                 {"\"I appreciate the offer, but I prefer to work alone.\"",
                  "vivienne_alone", nullptr, nullptr},
                 {"\"Let me think about it.\"", "", nullptr, nullptr}});

        addNode(state, "vivienne_alliance", "Baroness Vivienne",
                "\"*She squeezes your hand firmly, a genuine smile breaking through\n"
                "her usual mask.*\n"
                "Excellent. You will not regret this, Lady Seraphina. *She releases\n"
                "your hand and picks up her teacup.* I will send word through my\n"
                "footman when I have actionable intelligence. In the meantime,\n"
                "watch Elena closely. Note who she speaks to, where she goes.\n"
                "Every detail matters. *She raises her cup.* To our alliance.\"",
                {{"\"*Raise your cup.* To our alliance.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] You have formed an alliance with Baroness Vivienne.", ansi::BRIGHT_GREEN) << "\n";
                          std::cout << colored("      She will work to undermine Elena's social support.", ansi::BRIGHT_GREEN) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_alone", "Baroness Vivienne",
                "\"*She withdraws her hand, expression cooling slightly.*\n"
                "I see. Well, the offer remains open, Lady Seraphina. The road you\n"
                "walk is harder alone. *She sips her tea.* When you change your\n"
                "mind, and you will, you know where to find me.\"",
                {{"\"Thank you for your time, Baroness.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "vivienne_just_one", "Baroness Vivienne",
                "\"*She sets down her cup with a deliberate clink.*\n"
                "Just one girl? That is what they said about every revolution, my\n"
                "dear. It starts with one. One charming face, one convincing story,\n"
                "and suddenly the world you knew is crumbling. *She fixes you with\n"
                "a stare.* I have seen it happen in other kingdoms. I will not let\n"
                "it happen here.\"",
                {{"\"Perhaps you're right. Tell me more.\"", "vivienne_propose", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 5; }},
                 {"\"You're being dramatic.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection -= 10; }}});

        addNode(state, "vivienne_discuss", "Baroness Vivienne",
                "\"The Noble Quarter is buzzing with concern, my dear. The social\n"
                "season is approaching, the Royal Ball is on everyone's mind, and\n"
                "a commoner has been invited to dance with princes. *She arches\n"
                "an eyebrow.* The old families are worried. And worried nobles\n"
                "make desperate decisions. I thought perhaps we could guide those\n"
                "decisions in a productive direction.\"",
                {{"\"What kind of productive direction?\"", "vivienne_propose", nullptr, nullptr},
                 {"\"Are there others who share your concerns?\"",
                  "vivienne_others", nullptr, nullptr}});

        addNode(state, "vivienne_others", "Baroness Vivienne",
                "\"Several. The Pemberton matriarch is quietly furious. Lady Carstairs\n"
                "has been writing letters to the King's council. And young Lord\n"
                "Fairfax, despite his infatuation with Elena, has a mother who\n"
                "would rather see him married to a goat than a commoner. *She\n"
                "counts on her fingers.* We have allies, Lady Seraphina. What we\n"
                "lack is a leader. Someone with the name, the position, and the\n"
                "nerve to act. *She looks at you meaningfully.*\"",
                {{"\"Are you asking me to lead this effort?\"", "vivienne_lead", nullptr, nullptr},
                 {"\"That's a lot of pressure, Baroness.\"", "", nullptr, nullptr}});

        addNode(state, "vivienne_lead", "Baroness Vivienne",
                "\"I am asking you to consider it. The Aldric name carries weight\n"
                "that mine cannot match. If you stood at the center of this effort,\n"
                "openly or quietly, others would follow. *She touches your arm.*\n"
                "You have the breeding, the intelligence, and, I suspect, the\n"
                "ruthlessness when necessary. Think about it.\"",
                {{"\"I'll think about it. Thank you, Vivienne.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 10;
                          std::cout << colored("  [i] The Baroness sees you as a potential leader against Elena.", ansi::BRIGHT_CYAN) << "\n";
                  }},
                 {"\"Ruthlessness? You don't know me as well as you think.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 3; }}},
                true);

        addNode(state, "vivienne_herself", "Baroness Vivienne",
                "\"*She smooths her skirt, considering how much to reveal.*\n"
                "I am the second daughter of the Earl of Meridian, married into\n"
                "House Ashworth at nineteen. My husband, Baron Ashworth, manages\n"
                "the northern trade routes while I manage, well, everything else.\n"
                "*She smiles tightly.* In noble life, the husband holds the title\n"
                "and the wife holds the power. I suspect you will learn that soon\n"
                "enough, Lady Seraphina.\"",
                {{"\"You seem to manage quite well, Baroness.\"", "vivienne_manage",
                  nullptr, [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 5; }},
                 {"\"What does your husband think of Elena?\"", "vivienne_husband_elena",
                  nullptr, nullptr}});

        addNode(state, "vivienne_manage", "Baroness Vivienne",
                "\"*A genuine smile.*\n"
                "I have had to. When you marry into a house that is not your own,\n"
                "you learn to make yourself indispensable, or you become irrelevant.\n"
                "I chose the former. *She pours you more tea.* I see something\n"
                "similar in you, Lady Seraphina. You are not content to be a\n"
                "decoration. Good. Decorations can be replaced.\"",
                {{"\"I have no intention of being replaced.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 10; }}},
                true);

        addNode(state, "vivienne_husband_elena", "Baroness Vivienne",
                "\"My husband? *She waves dismissively.* He thinks she's charming\n"
                "and harmless. Men are often blind to political threats that wear\n"
                "pretty faces. *Her expression hardens.* His brother, however,\n"
                "seems to be quite taken with her. Which concerns me deeply for\n"
                "entirely different reasons.\"",
                {{"\"The younger Ashworth's interest could complicate things.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] Vivienne's brother-in-law is romantically interested in Elena.", ansi::BRIGHT_CYAN) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_influence", "Baroness Vivienne",
                "\"Influence? *She arches an eyebrow.* I have been called many things,\n"
                "my dear. Influential, ambitious, terrifying. All accurate. *She\n"
                "smiles.* The Noble Quarter social scene runs on information, favors,\n"
                "and carefully maintained relationships. I have cultivated all three\n"
                "over fifteen years. What I cannot do directly, I can arrange through\n"
                "three degrees of separation.\"",
                {{"\"I could use someone with your connections.\"", "vivienne_propose",
                  nullptr, [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 5; }},
                 {"\"That sounds both impressive and dangerous.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 3; }}});

        addNode(state, "vivienne_elena", "Baroness Vivienne",
                "\"*Her eyes flash with intensity.*\n"
                "Concerns? I have more than concerns, Lady Seraphina. I have evidence\n"
                "that Elena is not the simple, sweet commoner she pretends to be.\n"
                "She has been meeting with foreign merchants, sending letters under\n"
                "assumed names, and cultivating allies among the lesser nobility\n"
                "with disturbing efficiency. *She leans forward.* This girl has\n"
                "a plan, and we are all part of it.\"",
                {{"\"What kind of plan?\"", "vivienne_elena_plan", nullptr, nullptr},
                 {"\"Foreign merchants? Tell me more.\"", "vivienne_foreign", nullptr, nullptr},
                 {"\"You've been watching her closely.\"", "vivienne_watching", nullptr, nullptr}});

        addNode(state, "vivienne_elena_plan", "Baroness Vivienne",
                "\"I believe she intends to be adopted into a noble house, gain\n"
                "legal standing, and then leverage her popularity to claim a\n"
                "position of real power. Perhaps marriage to a titled lord, perhaps\n"
                "a seat on the council. *She shakes her head.* It is brilliant,\n"
                "really. She has made herself so beloved that opposing her would\n"
                "make the opposer look like the villain.\"",
                {{"\"Then we must be smarter than she is.\"", "vivienne_propose", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["baroness_vivienne"].affection += 10;
                          std::cout << colored("  [i] Elena's endgame may be legal noble status and political power.", ansi::BRIGHT_YELLOW) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_foreign", "Baroness Vivienne",
                "\"A man from the eastern provinces has been seen delivering packages\n"
                "to her guest room. Small parcels, always wrapped in brown paper.\n"
                "My informant could not determine the contents, but the man travels\n"
                "under a false name. *She narrows her eyes.* Whatever she's\n"
                "receiving, she does not want it traced to its source.\"",
                {{"\"Suspicious packages from unknown sources. That's worth investigating.\"",
                  "", nullptr,
                  [](GameState &gs)
                  {
                          std::cout << colored("  [i] Elena receives mysterious packages from the east.", ansi::BRIGHT_YELLOW) << "\n";
                  }}},
                true);

        addNode(state, "vivienne_watching", "Baroness Vivienne",
                "\"*She does not deny it.*\n"
                "Of course I have. Any woman of sense watches a potential rival.\n"
                "You should be doing the same, my dear. *She fixes you with a\n"
                "stare.* In fact, I suspect you already are. Why else would you\n"
                "be here? *A knowing smile.* We are more alike than you think.\"",
                {{"\"Perhaps we are. Let's talk strategy.\"", "vivienne_propose", nullptr,
                  [](GameState &gs)
                  { gs.npcs["baroness_vivienne"].affection += 10; }},
                 {"\"I'm just gathering information.\"", "", nullptr, nullptr}});
}