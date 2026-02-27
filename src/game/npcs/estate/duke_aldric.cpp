#include "game.hpp"
#include "game/dialogue_helpers.hpp"

namespace game::npcs
{

    void buildDukeDialogue(GameState &state)
    {
        addNode(state, "duke_root", "Duke Aldric",
                "Duke Aldric sits behind his mahogany desk, surrounded by maps and ledgers. His silver-"
                "streaked hair is combed back severely, and the lines on his face speak of decades of "
                "responsibility. He looks up from his papers, his expression shifting from intense focus "
                "to something softer as he sees you. \"Seraphina. Come in. I always have time for my "
                "daughter.\"",
                {
                    {"How are you, Father?", "duke_wellbeing", nullptr, nullptr},
                    {"I want to discuss Elena.", "duke_elena", nullptr, nullptr},
                    {"I have something important to show you.", "duke_evidence", nullptr, nullptr},
                    {"Tell me about the family's history.", "duke_history", nullptr, nullptr},
                    {"I am worried about my reputation.", "duke_reputation", nullptr, nullptr},
                    {"I need your advice.", "duke_advice", nullptr, nullptr},
                    {"Can we talk about the Royal Ball?", "duke_ball", nullptr, nullptr},
                    {"[After Elena's expulsion] About Elena's departure...", "duke_post_expulsion",
                     [](const GameState &gs)
                     { return gs.quest.elena_expelled; }, nullptr},
                    {"[After body discovered] Father, something terrible happened.", "duke_post_death",
                     [](const GameState &gs)
                     { return gs.quest.body_discovered; }, nullptr},
                    {"I should let you work.", "duke_farewell", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_wellbeing", "Duke Aldric",
                "The Duke sets down his pen and gives you his full attention, a rare gesture. \"I am "
                "well enough, though this province generates more paperwork than a war campaign.\" A "
                "brief, tired smile. \"The real question is how you are, Seraphina. You have seemed... "
                "preoccupied lately. Graves tells me you have been pacing the hallways at odd hours.\"",
                {
                    {"I have a lot on my mind.", "duke_mind", nullptr, nullptr},
                    {"I am fine, Father. Just restless.", "duke_fine", nullptr, nullptr},
                    {"Do you remember what Mother would say when things were hard?", "duke_mother_memory", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_mind", "Duke Aldric",
                "\"As do I. As does everyone in this household, it seems.\" He leans back. \"When I was "
                "your age, my father told me that worry is a tax paid on problems that may never arrive. "
                "I thought it was dismissive at the time.\" He pauses. \"Now I understand he meant that "
                "worry should be transformed into action. If something troubles you, address it. The Aldric "
                "way is not to brood, it is to act.\"",
                {
                    {"You are right. I will act.", "duke_root", nullptr,
                     [](GameState &gs) {}},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_fine", "Duke Aldric",
                "He studies you with the eyes of a man who has spent decades reading people. \"You are "
                "many things, Seraphina, but 'fine' is not among them at this moment.\" His tone is not "
                "accusatory but observant. \"When you are ready to tell me what is truly on your mind, "
                "I am here. I may not always say what you want to hear, but I will always listen.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_mother_memory", "Duke Aldric",
                "The Duke goes very still. The pen in his hand stops halfway to the inkwell. \"Your "
                "mother...\" The word comes out rough, as if rarely used. He sets the pen down carefully. "
                "\"Helena would say, 'The world bends for those who insist gently.' She believed that "
                "strength did not require volume or violence.\" His eyes drift to a small portrait on "
                "the desk that faces away from visitors. \"She was right. She was always right. About "
                "everything except how much time she had left.\"",
                {
                    {"I miss her, Father.", "duke_mother_miss", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 15;
                                 break;
                             }
                         }
                     }},
                    {"She would know what to do about Elena.", "duke_mother_elena", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_mother_miss", "Duke Aldric",
                "For a moment, the Duke is not a Duke. He is a man who lost the person he loved most. "
                "\"As do I. Every day.\" His voice is barely above a whisper. \"You have her determination, "
                "Seraphina. And her talent for seeing through people's masks. Cedric has her compassion, "
                "and Rosalind has her laughter.\" He clears his throat roughly. \"Between the three of "
                "you, she lives on. That is the only comfort I have found that means anything.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_mother_elena", "Duke Aldric",
                "\"Yes, she would.\" He picks up the small portrait and studies it. \"Helena would have "
                "invited Elena to tea within the first hour of her arrival. She would have listened, really "
                "listened, to every word. And by the end of that tea, she would have known exactly who "
                "Elena is and what she wants.\" He sets the portrait down. \"I lack that gift. I read "
                "ledgers and maps far better than I read people. It is why I rely so heavily on Graves "
                "and Cedric for counsel.\"",
                {
                    {"You could rely on me too, Father.", "duke_rely_sera", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_rely_sera", "Duke Aldric",
                "The Duke regards you with an expression that mingles surprise and something close "
                "to pride. \"You are right. I should, and I do not say that lightly.\" He nods slowly. "
                "\"You have shown more awareness of this household's dynamics than I gave you credit for. "
                "From now on, I will include you in decisions that affect the family. You have earned that.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena", "Duke Aldric",
                "The Duke's expression becomes careful, political. \"Elena. Yes, I have been meaning to "
                "discuss her with you.\" He steeples his fingers. \"She arrived with a letter of "
                "introduction from Lord Ashworth, a respected name. Her manners are impeccable, her "
                "conversation intelligent, and the Prince himself has shown interest.\" He pauses. "
                "\"But you did not come here to hear her praised. Tell me your concerns.\"",
                {
                    {"She is not who she claims to be.", "duke_elena_claim", nullptr, nullptr},
                    {"Her influence over the household is growing.", "duke_elena_influence", nullptr, nullptr},
                    {"The servants are divided in their loyalty.", "duke_elena_servants", nullptr, nullptr},
                    {"I would like to invite her to dinner formally.", "duke_elena_invite",
                     [](const GameState &gs)
                     { return !gs.quest.invited_elena; },
                     [](GameState &gs)
                     { gs.quest.invited_elena = true; }},
                    {"I think we should befriend her strategically.", "duke_elena_befriend", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_claim", "Duke Aldric",
                "\"A serious accusation, Seraphina. What evidence do you have?\" His tone shifts to "
                "the measured voice he uses in formal proceedings. \"I have verified her letter of "
                "introduction with Lord Ashworth's household. The seal is authentic.\" He raises a hand "
                "before you can respond. \"However, a letter of introduction only proves she was in "
                "contact with Ashworth. It does not prove she is who Ashworth believes her to be. "
                "There is a difference.\"",
                {
                    {"Her correspondence uses coded language.", "duke_elena_code", nullptr, nullptr},
                    {"Graves has documented unusual movements.", "duke_elena_movements", nullptr, nullptr},
                    {"The staff have reported she asks probing questions.", "duke_elena_questions", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_code", "Duke Aldric",
                "The Duke's eyebrows rise sharply. \"Coded correspondence? You have seen this yourself?\" "
                "He extends his hand. \"Show me, if you have evidence. A Duke does not act on hearsay, "
                "but coded letters are another matter entirely. That would suggest an intelligence network "
                "operating within my own walls, and that I will not tolerate.\"",
                {
                    {"Cedric intercepted a letter with an Iris seal.", "duke_elena_iris", [](const GameState &gs)
                     { return gs.quest.elena_letters_found; },
                     {}},
                    {"I do not have the letters yet.", "duke_elena_no_proof", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_iris", "Duke Aldric",
                "The Duke's face drains of color. He rises from his chair, something he rarely does "
                "during a private conversation. \"The Iris Consortium.\" His voice is hard. \"I had "
                "hoped never to hear that name again.\" He moves to the window and stands with his back "
                "to you for a moment. \"Twenty years ago, during the succession crisis, the Consortium "
                "placed agents in three noble households. Two fell. Only the Aldric family survived, "
                "because your grandfather recognized the threat in time.\" He turns. \"If they have "
                "returned, if Elena is their agent, then this goes beyond a guest overstaying her welcome. "
                "This is an act of political warfare.\"",
                {
                    {"What do we do?", "duke_elena_action", nullptr, nullptr},
                    {"Tell me more about the Consortium.", "duke_iris_history", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_action", "Duke Aldric",
                "\"We act decisively but carefully. A formal expulsion, with witnesses and documentation. "
                "She is to leave the estate within the day, with an escort to ensure she departs the "
                "province.\" His jaw sets. \"I will draft the order myself. And I will send word to Lord "
                "Ashworth demanding an explanation for introducing a Consortium agent into my household. "
                "If he was unwitting, he will be horrified. If he was complicit...\" His expression darkens "
                "further. \"Then we have a larger problem.\"",
                {
                    {"I will support you fully.", "duke_elena_expel_support", nullptr,
                     [](GameState &gs)
                     {
                         gs.quest.elena_expelled = true;
                         gs.heroine_popularity -= 30;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Perhaps we should just watch her more closely first.", "duke_elena_wait", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_expel_support", "Duke Aldric",
                "\"Good. I need the family unified on this.\" He begins writing immediately, his pen "
                "scratching across parchment with furious precision. \"Tell Cedric to stand with me when "
                "I deliver the order. Tell Graves to prepare the guest room for immediate vacating. And "
                "tell Roderick to have an escort ready at the gate.\" He looks up, and there is fierce "
                "pride in his eyes. \"You brought me the truth when others would have stayed silent. "
                "Your mother would be proud. I am proud.\"",
                {
                    {"Thank you, Father.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_wait", "Duke Aldric",
                "\"Wait?\" His voice sharpens. \"Every day she remains is a day she gathers more "
                "intelligence, builds more connections, undermines more loyalties. I understand caution, "
                "Seraphina, but there are times when delay is more dangerous than action.\" He sits back "
                "down, visibly restraining himself. \"However, if you believe there is strategic value in "
                "keeping her close and observed, I will defer to your judgment. For now. But my patience "
                "has limits.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_iris_history", "Duke Aldric",
                "The Duke settles into his chair with the heaviness of a man revisiting old battles. "
                "\"The Iris Consortium began as a merchants' guild in the capital, decades ago. They "
                "dealt in trade, information, and eventually influence. Over time, they realized that "
                "placing sympathetic agents in noble households was more profitable than any trade route.\" "
                "He steeples his fingers. \"They offer advancement to commoners with talent: education, "
                "social training, connections. In return, those agents report on noble families' weaknesses, "
                "political vulnerabilities, financial pressures. The Consortium sells this intelligence "
                "to the highest bidder, or uses it to manipulate events directly.\"",
                {
                    {"Elena fits that pattern exactly.", "duke_iris_elena_fit", nullptr, nullptr},
                    {"Could she have been sent specifically for us?", "duke_iris_targeted", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_iris_elena_fit", "Duke Aldric",
                "\"She does. A commoner of remarkable poise and education, arriving with noble references, "
                "quickly integrating into household dynamics, building relationships with staff and family "
                "alike.\" The Duke's voice is bitter. \"It is their standard approach. The agents are "
                "genuinely charming, genuinely talented, that is what makes them so effective. They are "
                "not actors playing a part. They are trained professionals who believe in their own mission.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_iris_targeted", "Duke Aldric",
                "\"Possibly. The Aldric family controls one of the wealthiest provinces, and our political "
                "alliances could tip the balance of power in the capital.\" He meets your eyes. \"And there "
                "is the matter of the succession. Your grandfather made enemies when he consolidated power "
                "after the border wars. Some of those enemies may have found the Consortium a useful tool "
                "for revenge, even decades later.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_no_proof", "Duke Aldric",
                "\"Then bring me proof, Seraphina. I cannot and will not act on suspicion alone.\" "
                "His tone is firm but not unkind. \"I understand your concerns. But expelling a guest "
                "without cause would damage our reputation far more than any infiltrator. We would appear "
                "paranoid, inhospitable, or worse, afraid of a commoner.\" He taps the desk. \"Find me "
                "evidence. Letters, documents, witness testimony. Something I can act on without political "
                "consequence.\"",
                {
                    {"I will find the proof you need.", "duke_root", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_influence", "Duke Aldric",
                "\"I am aware.\" He picks up a report from his desk. \"Graves provides me with weekly "
                "assessments. Elena's approval among the staff has risen considerably since her arrival. "
                "She is, objectively, a more popular figure in this household than any family member except "
                "perhaps Rosalind.\" He sets the report down. \"It is concerning but not unprecedented. "
                "New faces always generate excitement. The question is whether her influence fades naturally "
                "as novelty wears off, or whether it deepens into something more structural.\"",
                {
                    {"It is deepening. She is building a network.", "duke_elena_network", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_network", "Duke Aldric",
                "\"A network.\" He considers the word. \"That implies coordination and intent, not merely "
                "charm. Again, I need specifics. Who has she turned? What information has she gathered? "
                "What does she intend to do with it?\" He leans forward. \"I do not doubt your instincts, "
                "Seraphina. But instincts must be buttressed with evidence if we are to act effectively.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_servants", "Duke Aldric",
                "\"Divided loyalties among staff is a serious charge.\" The Duke's expression hardens. "
                "\"A household that does not serve its lord with unity is a household that can be subverted "
                "from within.\" He stands and paces. \"I will speak with Graves about a loyalty assessment. "
                "Discreetly. And I want Clara's name on that assessment, she hears everything.\" He pauses. "
                "\"If any servant has placed Elena's interests above this family's, I will know by "
                "week's end.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_elena_befriend", "Duke Aldric",
                "The Duke raises an eyebrow, a rare expression of surprise. \"Befriend her? Strategically?\" "
                "He considers this for a long moment. \"That is... not what I expected from you. But it "
                "shows maturity.\" He nods slowly. \"Keep your friends close and your enemies closer. "
                "Your grandfather lived by that maxim.\" He taps his chin. \"If you can position yourself "
                "as Elena's ally while maintaining the family's interests, you would have access to her "
                "plans and her contacts. It is risky, but potentially far more effective than open "
                "opposition.\"",
                {
                    {"That is exactly my thinking.", "duke_root", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence", "Duke Aldric",
                "The Duke sets down his pen and gives you his full, serious attention. \"Show me what you "
                "have found, Seraphina.\"",
                {
                    {"I found letters connecting Elena to the Iris Consortium.", "duke_evidence_letters", [](const GameState &gs)
                     { return gs.quest.elena_letters_found; },
                     {}},
                    {"Staff have reported Elena spreading rumors about us.", "duke_evidence_rumors", [](const GameState &gs)
                     { return gs.quest.rumors_spread; },
                     {}},
                    {"Elena has been accessing restricted areas.", "duke_evidence_access", nullptr, nullptr},
                    {"Actually, never mind.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence_letters", "Duke Aldric",
                "The Duke takes the letters with both hands, reading slowly and thoroughly in the manner "
                "of a man who has reviewed legal documents for decades. His expression cycles through "
                "recognition, anger, and cold determination. \"The Iris seal. Coded language. References "
                "to our political alliances and household security.\" He sets the letters down with "
                "deliberate control. \"This is sufficient. More than sufficient.\"",
                {
                    {"Expel her from the estate.", "duke_evidence_expel", nullptr,
                     [](GameState &gs)
                     {
                         gs.quest.elena_expelled = true;
                         gs.heroine_popularity -= 30;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Use them as leverage against her.", "duke_evidence_leverage", nullptr,
                     [](GameState &gs)
                     {
                         gs.heroine_popularity -= 15;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence_expel", "Duke Aldric",
                "\"Agreed. She leaves today.\" The Duke stands, straightening his coat with military "
                "precision. \"I will draft the formal expulsion order within the hour. Roderick will "
                "provide an escort to the provincial border. Her belongings will be searched before "
                "departure for any stolen documents or estate intelligence.\" He looks at you. "
                "\"You have done well, Seraphina. This household, this family, owes you a debt. "
                "I will not forget that you were the one who saw the danger clearly.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence_leverage", "Duke Aldric",
                "The Duke pauses, reconsidering. \"Leverage. You want to keep her in a position of "
                "debt rather than simply removing her.\" He strokes his chin. \"Tactically sound. "
                "If Elena knows we have her letters, she is neutralized without the spectacle of an "
                "expulsion. She becomes cooperative, even useful.\" His eyes narrow. \"But it is a "
                "dangerous game. A cornered agent may lash out, or call for reinforcements. Are you "
                "prepared for that risk?\"",
                {
                    {"I am prepared.", "duke_root", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence_rumors", "Duke Aldric",
                "\"Spreading rumors about the Aldric family?\" The Duke's voice drops to a dangerous "
                "register. \"Under my own roof? That is not merely impolite, that is an attack on our "
                "name.\" He drums his fingers on the desk. \"However, rumors are difficult to prove "
                "and easy to deny. She would claim she was misunderstood, or that the staff misheard. "
                "I need something more concrete before I confront her directly.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_evidence_access", "Duke Aldric",
                "\"Which areas?\" His attention sharpens. \"Graves manages the key schedule, and all "
                "guest access is documented. If she has been in rooms she should not have entered, "
                "Graves will have a record.\" He pulls a bell cord. \"I will have him bring the access "
                "log immediately. If her name appears where it should not, that is a concrete violation "
                "of guest protocol, something I can act on openly.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_history", "Duke Aldric",
                "The Duke's rigid posture relaxes slightly, the topic drawing him into more comfortable "
                "territory. \"The Aldric family has held this province for seven generations. We were "
                "border lords originally, granted these lands for service during the Thornwall Campaigns.\" "
                "He gestures to a faded map on the wall. \"Your great-great-grandfather turned a "
                "military outpost into a thriving estate. Each generation added something: the library, "
                "the gardens, the trade agreements with the capital.\"",
                {
                    {"Tell me about the border wars.", "duke_wars", nullptr, nullptr},
                    {"What about Mother's family?", "duke_mother_family", nullptr, nullptr},
                    {"What legacy do you want to leave?", "duke_legacy", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_wars", "Duke Aldric",
                "\"The Thornwall Campaigns were fifty years of intermittent conflict along the northern "
                "border. Raiders, territorial disputes, proxy wars between larger kingdoms.\" His voice "
                "takes on the cadence of a lecture, a topic he clearly knows thoroughly. \"Your grandfather "
                "was the last Aldric to fight in them. He earned the expanded estate through a defense of "
                "the Thornwall Pass that military historians still study.\" He pauses with something "
                "approaching reverence. \"Three hundred men held a pass against two thousand for nine "
                "days. When reinforcements arrived, your grandfather had lost half his force but not "
                "a single yard of ground.\"",
                {
                    {"That is remarkable.", "duke_root", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_mother_family", "Duke Aldric",
                "\"The Valmont family. Old money, capital connections, social influence.\" His voice is "
                "carefully controlled. \"Your mother's father was a chancellor's advisor. The marriage "
                "was arranged to strengthen both families, ours gaining political reach, theirs gaining "
                "military security.\" The control slips slightly. \"But it became more than an arrangement "
                "within a month. Helena was... extraordinary. She could have married anyone. The fact that "
                "she chose to make our match a genuine partnership rather than a political obligation was "
                "the greatest gift I have ever received.\"",
                {
                    {"Do the Valmonts still have influence?", "duke_valmont_influence", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_valmont_influence", "Duke Aldric",
                "\"Some. Your Uncle Gerard manages the Valmont affairs in the capital. He is a quiet man "
                "with a long memory.\" The Duke considers. \"If matters with Elena escalate beyond our "
                "walls, the Valmont connection could be useful. Gerard still has friends in the chancellor's "
                "office. But I would prefer to resolve this internally. External involvement always carries "
                "a price.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_legacy", "Duke Aldric",
                "The Duke is quiet for a long time. \"I want to leave you and your siblings a province "
                "that is stable, prosperous, and respected. I want the Aldric name to mean something "
                "beyond military accomplishment.\" He looks at the portrait of your mother. \"Helena wanted "
                "to build schools in the villages. I started one, in the capital settlement, but there is "
                "so much more to do.\" He meets your eyes. \"What I want most, Seraphina, is for my "
                "children to take over this responsibility and carry it with the same dedication. And the "
                "same humanity.\"",
                {
                    {"I will make you proud, Father.", "duke_root", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 15;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_reputation", "Duke Aldric",
                "\"Your reputation?\" The Duke folds his hands. \"I have heard the whispers, Seraphina. "
                "The staff talk, the village gossips, and Elena's presence has created an unfortunate "
                "comparison in people's minds.\" His voice hardens. \"A false comparison. You are the "
                "Duke's daughter, born to responsibility and trained for leadership. She is a guest "
                "with charming manners. The two are not equivalent, regardless of what popular sentiment "
                "suggests.\"",
                {
                    {"But popular sentiment matters.", "duke_rep_sentiment", nullptr, nullptr},
                    {"How do I improve my standing?", "duke_rep_improve", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_rep_sentiment", "Duke Aldric",
                "\"Unfortunately, yes.\" He concedes the point with visible reluctance. \"A noble's "
                "reputation is their currency. Without it, authority becomes empty title.\" He leans "
                "forward. \"But reputation is built on actions, not words. A single decisive act of "
                "leadership will outweigh months of Elena's social maneuvering. Show the household and "
                "the province who you are, not through comparison with her, but through your own merit.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_rep_improve", "Duke Aldric",
                "\"Start with the household. Ensure the staff see you as their advocate, not merely their "
                "lady. Attend to their concerns.\" He reaches into a drawer and produces a small ledger. "
                "\"Here are the outstanding requests from the servants' council: repairs to the quarters' "
                "roof, an additional day of rest per month, and better lamp oil for the corridors.\" He "
                "slides it across. \"Address these, and you will earn genuine loyalty that no outsider "
                "can undermine.\"",
                {
                    {"I will take care of these.", "duke_root", nullptr,
                     [](GameState &gs)
                     {
                         gs.quest.servants_loyal = true;
                     }},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_advice", "Duke Aldric",
                "\"Advice.\" He settles back, the weight of experience visible in his posture. \"On what "
                "subject? I have made enough mistakes to fill a library, which I suppose qualifies me "
                "as an advisor.\"",
                {
                    {"How do I handle someone more popular than me?", "duke_advice_popular", nullptr, nullptr},
                    {"When is it right to use deception?", "duke_advice_deception", nullptr, nullptr},
                    {"How do you make difficult decisions?", "duke_advice_decisions", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_advice_popular", "Duke Aldric",
                "\"You do not compete on their terms. That is the first and most critical rule.\" He "
                "speaks with the confidence of hard-won wisdom. \"If someone is more charming, do not "
                "try to be charming. If they are loved, do not try to be loved. Instead, be necessary. "
                "Be the person without whom the household cannot function, the person whose decisions "
                "shape daily life.\" He pauses. \"Popularity fades. Authority endures. Your mother "
                "understood this instinctively, she was beloved not because she sought love, but because "
                "her actions consistently served others.\"",
                {
                    {"That is helpful. Thank you.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_advice_deception", "Duke Aldric",
                "The Duke regards you with a long, searching look. \"Deception.\" He weighs the word. "
                "\"Your grandfather would have said 'never.' Your mother would have said 'only when no "
                "one gets hurt.' I say...\" He pauses. \"I say that deception is a tool, like any other. "
                "It is neither noble nor ignoble in itself. The question is what you use it for and "
                "whether you can live with the consequences.\" His voice drops. \"But know this: every "
                "deception carries a cost. The truth has a way of surfacing, and when it does, the penalty "
                "for the lie is always greater than the penalty for the truth would have been.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_advice_decisions", "Duke Aldric",
                "\"I gather every fact available. I consult people I trust. And then I sit alone in this "
                "room and ask myself one question: twenty years from now, which choice will I regret "
                "least?\" He taps the desk. \"Not which is morally perfect, not which is strategically "
                "optimal, but which allows me to face my children with a clear conscience.\" He meets "
                "your eyes. \"The world does not offer clean choices, Seraphina. Only choices with "
                "different costs. Select the cost you can bear and commit fully.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_ball", "Duke Aldric",
                "\"The Royal Ball. Yes, it is approaching.\" He pulls out an ornate invitation from "
                "his desk. \"Every noble family in the province will attend. The Prince will be there. "
                "The capital's most influential figures.\" He sets the invitation between you. \"It is "
                "an opportunity, Seraphina. To demonstrate the Aldric family's strength and unity. "
                "But it is also a risk if Elena attends and outshines you in front of the entire "
                "nobility.\"",
                {
                    {"She cannot be allowed to attend.", "duke_ball_exclude", nullptr, nullptr},
                    {"I will outshine her on my own merit.", "duke_ball_compete", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Can we use the ball to expose her?", "duke_ball_expose", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_ball_exclude", "Duke Aldric",
                "\"Excluding a guest who has been publicly welcomed would require justification. "
                "We cannot simply withdraw her invitation without explanation.\" He frowns. \"However, "
                "if she were to leave the estate before the ball for any reason, whether by choice or "
                "by formal action, the invitation becomes moot.\" He gives you a significant look. "
                "\"The timing of certain revelations could be managed accordingly.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_ball_compete", "Duke Aldric",
                "A rare, genuine smile crosses the Duke's face. \"That is the spirit I want to see. "
                "The Aldric family does not hide from challenges, we meet them.\" He opens a drawer "
                "and produces a small velvet box. \"Your mother's pearls. She wore them to every formal "
                "event. I have been saving them for the right moment.\" He pauses. \"I believe this "
                "is that moment.\"",
                {
                    {"Father... thank you.", "duke_root", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                },
                false);

        addNode(state, "duke_ball_expose", "Duke Aldric",
                "\"Expose her at the ball?\" The Duke considers this carefully. \"A public revelation "
                "would be devastating, both to Elena and potentially to us. If we accuse her before the "
                "entire nobility and our evidence is even slightly flawed, we become the aggressors.\" "
                "He steeples his fingers. \"But if the evidence is irrefutable, presented with dignity "
                "and restraint, it becomes a demonstration of Aldric vigilance and leadership. The question "
                "is whether you are confident enough in what we have.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_post_expulsion", "Duke Aldric",
                "The Duke stands by the window, watching the road that leads away from the estate. "
                "\"It is done. She departed this morning with Roderick's escort.\" His voice carries "
                "the weariness of a difficult decision executed. \"The household is unsettled. Some staff "
                "support the decision. Others feel we were too harsh.\" He turns to you. \"In time, they "
                "will understand. An infiltrator cannot be tolerated, regardless of how pleasant she made "
                "herself.\"",
                {
                    {"You made the right decision, Father.", "duke_exp_right", nullptr, nullptr},
                    {"How will this affect our standing?", "duke_exp_standing", nullptr, nullptr},
                    {"What about the Iris Consortium?", "duke_exp_consortium", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_exp_right", "Duke Aldric",
                "\"I know.\" But certainty does not bring comfort. \"Still, I keep thinking about your "
                "mother. She would have handled it differently, found some way to resolve it without "
                "an expulsion. She had that gift.\" He shakes his head. \"But I am not Helena. I am a "
                "soldier and an administrator. I protect what is mine with the tools I have.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_exp_standing", "Duke Aldric",
                "\"Mixed impact. Among the nobility, expelling a possible Consortium agent will be seen "
                "as decisive and protective. Lord Ashworth has already sent a letter of apology and "
                "support.\" He frowns. \"Among the common people, it may be viewed less favorably. "
                "A kind young woman removed from the Duke's household makes for an unpleasant story "
                "unless the reasons are made clear.\" He pauses. \"I am drafting a formal statement "
                "for the provincial records. The truth, stated plainly, will serve us better than silence.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_exp_consortium", "Duke Aldric",
                "\"I have sent inquiries to three other noble households that I suspect may have been "
                "targeted. If the Consortium is active again, we cannot fight them alone.\" His expression "
                "is grim. \"A coalition of noble families, sharing intelligence and watching for agents, "
                "would be the most effective response. Your grandfather formed such a coalition during "
                "the succession crisis. It may be time to revive it.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_post_death", "Duke Aldric",
                "The Duke is standing when you enter, which is unusual. His face is ashen, and the "
                "composure he wears like armor has visible cracks. \"I know.\" Two words, laden with "
                "everything. \"Roderick informed me at dawn. A guest, dead under my roof.\" He grips "
                "the back of his chair. \"In seven generations, this has never happened. The Aldric estate "
                "has been a place of sanctuary, of hospitality, of safety. And now...\" He cannot finish.",
                {
                    {"Father, I am so sorry.", "duke_death_sorry", nullptr, nullptr},
                    {"What will you do?", "duke_death_action", nullptr, nullptr},
                    {"It was an accident.", "duke_death_accident", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_death_sorry", "Duke Aldric",
                "\"Sorry does not restore a life or a family's honor.\" He says it without cruelty, simply "
                "as fact. \"I must notify the provincial magistrate. An investigation will follow. Every "
                "member of this household will be questioned.\" He looks at you with eyes that search "
                "for something he is afraid to find. \"Seraphina, whatever you know about what happened, "
                "tell me now. Before the magistrate arrives. If there is something I need to manage, "
                "I need to know before it becomes public.\"",
                {
                    {"I know nothing, Father.", "duke_death_nothing", nullptr, nullptr},
                    {"There are things you should know.", "duke_death_truth", nullptr, nullptr},
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_death_nothing", "Duke Aldric",
                "He studies you for a very long moment. \"Then the investigation will confirm that. "
                "And we will grieve appropriately and take whatever consequences follow.\" He sits down "
                "heavily. \"I have failed in the most fundamental duty of a host. Whatever else happens, "
                "that failure is mine to carry.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_death_truth", "Duke Aldric",
                "The Duke's face hardens into the expression he wears in council, the face of a man "
                "making decisions that will echo for years. \"Tell me. Everything. Leave nothing out.\" "
                "He sits and folds his hands, and for the next few minutes he is utterly still as you "
                "speak. When you finish, the silence is like a coffin lid closing. \"I see.\" His voice "
                "is a hollow shell. \"We will discuss what happens next. But first, I need a moment alone.\" "
                "He turns to the window. \"Please.\"",
                {
                    {"I understand.", "duke_root", nullptr,
                     [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "duke_aldric")
                             {
                                 n.second.affection -= 20;
                                 n.second.suspicion += 30;
                                 break;
                             }
                         }
                     }},
                },
                false);

        addNode(state, "duke_death_action", "Duke Aldric",
                "\"What I must. Notify the magistrate. Secure the estate. Ensure no evidence is disturbed.\" "
                "He is reciting protocol, the structure giving him something to hold onto. \"Roderick has "
                "already sealed the guest room. Graves is assembling the staff. Marcel has closed the "
                "kitchen.\" He pauses. \"And I will pray. I do not do it often, but this seems a moment "
                "that requires something beyond administrative procedure.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_death_accident", "Duke Aldric",
                "\"An accident.\" He repeats it flatly. \"The magistrate will determine that. Not you, "
                "not me.\" His gaze is penetrating. \"If it was truly an accident, then we bear the "
                "tragedy with dignity and cooperate fully with any investigation. If it was not...\" "
                "He lets the implication hang. \"Then God help whoever is responsible, because the law "
                "of this province will show no mercy. Not even to an Aldric.\"",
                {
                    {"Back to other matters.", "duke_root", nullptr, nullptr},
                },
                false);

        addNode(state, "duke_farewell", "Duke Aldric",
                "The Duke returns to his papers but pauses to look at you one more time. \"Take care of "
                "yourself, Seraphina. And take care of your siblings. That is the most important task "
                "anyone in this family has.\"",
                {}, true);
    }

}

void registerDukeAldric(GameState &state)
{
    NPC n;
    n.id = "duke_aldric";
    n.name = "Duke Aldric";
    n.title = "Father";
    n.description = "The stern but caring patriarch of the Aldric family. A decorated military\n"
                    "commander whose authority is absolute within the estate.";
    n.current_room = "fathers_study";
    n.affection = 60;
    n.suspicion = 0;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "duke_root";
    n.traits = {Trait::Perceptive, Trait::Strong};
    n.schedule = {
        {0, "master_bedroom"},
        {6, "master_bedroom"},
        {7, "dining_room"},
        {8, "fathers_study"},
        {12, "dining_room"},
        {13, "library"},
        {15, "fathers_study"},
        {17, "garden"},
        {19, "dining_room"},
        {20, "fathers_study"},
        {22, "master_bedroom"},
    };
    n.associates = {"cedric", "rosalind", "butler_graves", "elena", "captain_roderick"};
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildDukeDialogue(state);
}