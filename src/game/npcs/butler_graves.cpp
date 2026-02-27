#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include <algorithm>

namespace game::npcs
{

    void buildGravesDialogue(GameState &state)
    {
        addNode(state, "graves_root", "Butler Graves",
                "Graves stands with impeccable posture near the hallway entrance, his silver hair "
                "combed precisely and his uniform without a single crease. He inclines his head just so. "
                "\"My lady. How may I be of service?\"",
                {
                    {"What is happening in the household today?", "graves_household", nullptr, nullptr},
                    {"Tell me about yourself, Graves.", "graves_backstory", nullptr, nullptr},
                    {"What have you observed about Elena?", "graves_elena", nullptr, nullptr},
                    {"I need you to deliver something.", "graves_deliver", nullptr, nullptr},
                    {"I need to hire you for a task.", "graves_hire", [](const GameState &)
                     { return true; },
                     {}},
                    {"What do you know about the staff's loyalty?", "graves_loyalty", nullptr, nullptr},
                    {"[After rumors spread] How are the rumors working?", "graves_post_rumors", [](const GameState &gs)
                     { return gs.quest.rumors_spread; },
                     {}},
                    {"[After Elena's expulsion] How is the household?", "graves_post_expulsion", [](const GameState &gs)
                     { return gs.quest.elena_expelled; },
                     {}},
                    {"[After body discovered] Graves, I need your discretion.", "graves_post_death", [](const GameState &gs)
                     { return gs.quest.body_discovered; },
                     {}},
                    {"That will be all.", "graves_farewell", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_household", "Butler Graves",
                "Graves produces a small notebook and consults it with practiced ease. \"The Duke has "
                "a meeting with the estate accountant at noon. Lord Cedric departed for his morning ride "
                "at seven and should return by ten. Lady Rosalind has her lessons with the tutor until "
                "midday.\" He turns a page. \"Chef Marcel reports that the larder is well-stocked, though "
                "he has noted some inventory discrepancies. Maid Clara is managing the cleaning rotation, "
                "though she has been more talkative than usual.\" He closes the notebook. \"Captain Roderick "
                "made his rounds at dawn and reported nothing unusual, though he seemed... preoccupied.\"",
                {
                    {"Inventory discrepancies?", "graves_inventory", nullptr, nullptr},
                    {"Why is Clara more talkative?", "graves_clara_gossip", nullptr, nullptr},
                    {"What was Roderick preoccupied about?", "graves_roderick_mood", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_inventory", "Butler Graves",
                "\"Chef Marcel has reported missing wine, cheese, and preserves from the cellar stores. "
                "Small quantities each time, but consistent over the past week.\" Graves's expression "
                "remains neutral, but his eyes are sharp. \"I have increased the frequency of cellar "
                "inspections. However, the thefts are occurring during hours when the cellar should be "
                "empty and locked.\" He pauses meaningfully. \"Someone either has a key they should not "
                "have, or knows another way in.\"",
                {
                    {"Could Elena be involved?", "graves_inventory_elena", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_inventory_elena", "Butler Graves",
                "\"I would not presume to accuse a guest of the Duke without evidence, my lady.\" "
                "His tone is carefully measured. \"However, I can confirm that the guest room key does "
                "not grant access to the cellar. If our guest is involved, she has found alternative "
                "means.\" He straightens an already straight cuff. \"I will continue to monitor the "
                "situation with discretion.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_clara_gossip", "Butler Graves",
                "\"Clara is... Clara.\" For the briefest moment, something like fondness crosses his "
                "face before the mask resettles. \"She has been gathering information with more enthusiasm "
                "than usual. I believe she senses tension in the household and is, in her way, trying to "
                "understand it.\" He clears his throat. \"She is loyal, my lady. Unfocused at times, but "
                "loyal. Her gossiping is not malicious, merely... unfiltered.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_roderick_mood", "Butler Graves",
                "\"The Captain has been reviewing security protocols with unusual intensity lately. "
                "He requested additional lanterns for the night watch and asked me about the cellar "
                "entrance locks.\" Graves considers his words. \"I have served alongside Captain Roderick "
                "for many years. When he is preoccupied, it means he has noticed something that does not "
                "fit his understanding of how the estate should work. He is not one to alarm others without "
                "cause, but his silence speaks louder than most men's shouts.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_backstory", "Butler Graves",
                "Graves is quiet for a moment, as if deciding how much formality to shed. \"I have "
                "served the Aldric family for twenty-seven years, my lady. I began as a junior footman "
                "under the previous butler, Mr. Hartwick, when your grandfather was Duke.\" His voice "
                "carries a note of reverence. \"Hartwick was a man of extraordinary discipline. He taught "
                "me that a butler is not merely a servant, but the spine of a household. Without the spine, "
                "everything collapses.\"",
                {
                    {"What happened to Hartwick?", "graves_hartwick", nullptr, nullptr},
                    {"You knew my grandfather well?", "graves_grandfather", nullptr, nullptr},
                    {"Did you know my mother?", "graves_mother", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hartwick", "Butler Graves",
                "\"Mr. Hartwick retired fifteen years ago, when his eyesight began to fail. He could no "
                "longer read the wine labels, he said, and a butler who cannot distinguish a Burgundy from "
                "a Bordeaux has no business serving at table.\" A rare ghost of a smile. \"He lives in a "
                "cottage on the estate's south border. I visit him monthly. He still criticizes how I fold "
                "the napkins.\" The smile fades. \"He is the closest thing to a father I have ever known. "
                "My own family... were not people I wish to discuss.\"",
                {
                    {"I understand. You do not have to say more.", "graves_hartwick_respect", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "butler_graves")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hartwick_respect", "Butler Graves",
                "Graves inclines his head, and for a moment you see something vulnerable beneath "
                "the polished exterior. \"Thank you, my lady. You have your mother's grace in that regard. "
                "She never pressed where pressing was unwelcome.\" He straightens. \"But I carry "
                "the lesson: a household is only as strong as the loyalty of those who keep it running. "
                "I have dedicated my life to ensuring this one stands firm.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_grandfather", "Butler Graves",
                "\"Your grandfather was a formidable man, my lady. Stern in public, generous in private. "
                "He knew every servant by name and treated us with a dignity that was, frankly, unusual "
                "for a Duke of his era.\" Graves's posture somehow becomes even straighter. \"He once "
                "dismissed a visiting lord from the estate for striking a stable boy. 'A man who beats "
                "those in his service,' he said, 'is not a man I will call guest.'\" He pauses. "
                "\"I have modeled my service on his example ever since.\"",
                {
                    {"He sounds like a good man.", "graves_root", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "butler_graves")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_mother", "Butler Graves",
                "Graves's composure wavers, just barely. \"Your mother, the late Duchess Helena, was "
                "the heart of this household.\" His voice is steady but quieter. \"She had a way of making "
                "everyone feel seen, from the Duke himself to the lowest scullery maid. The kitchen always "
                "had fresh flowers because she insisted. The servants' quarters had proper heating because "
                "she demanded it.\" He pauses. \"When she passed, something left this house that has never "
                "returned. We continue as she would have wished, but the warmth is... maintained now, rather "
                "than natural.\"",
                {
                    {"I miss her too.", "graves_mother_miss", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "butler_graves")
                             {
                                 n.second.affection += 15;
                                 break;
                             }
                         }
                     }},
                    {"She would want us to be strong.", "graves_mother_strength", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_mother_miss", "Butler Graves",
                "For the first and perhaps only time, Graves's mask slips completely. His eyes glisten, "
                "and he turns slightly away. \"Forgive me, my lady. Even after all these years.\" He takes "
                "a measured breath. \"She made me promise, near the end, to watch over her children. "
                "I have kept that promise every day since. Whatever you need, whatever this household faces, "
                "I am here. Not merely as butler, but as someone who loved your mother dearly.\"",
                {
                    {"Thank you, Graves.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_mother_strength", "Butler Graves",
                "\"Indeed she would, my lady.\" He composes himself with practiced efficiency. "
                "\"Duchess Helena faced every challenge with grace and determination. I see the same "
                "qualities in you, when you choose to employ them.\" He meets your eyes. \"She would "
                "be proud of how you are handling the current... situation. I believe that sincerely.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena", "Butler Graves",
                "Graves considers his words with the care of a man who understands that information "
                "is currency. \"The guest, Miss Elena, has been... remarkably efficient in her integration "
                "into this household.\" His tone is neutral but loaded. \"She rises early, assists where "
                "she is not asked, and makes herself indispensable to those around her. The staff respond "
                "to her warmly. The Duke has mentioned her favorably at breakfast twice this week.\"",
                {
                    {"You sound like you admire her.", "graves_elena_admire", nullptr, nullptr},
                    {"Or you find her suspicious.", "graves_elena_suspicious", nullptr, nullptr},
                    {"Has she been anywhere she should not be?", "graves_elena_movements", nullptr, nullptr},
                    {"Has she asked about the family?", "graves_elena_questions", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_admire", "Butler Graves",
                "\"Admire? No, my lady. I observe.\" His expression is unreadable. \"Admiration implies "
                "an emotional judgment, and I prefer to deal in facts. The fact is that Miss Elena has, "
                "in a remarkably short time, established relationships with nearly every member of this "
                "household. That is either a sign of genuine warmth or a deliberate strategy.\" He pauses. "
                "\"In my experience, genuine warmth does not require such precision.\"",
                {
                    {"You think she is strategic.", "graves_elena_strategic", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_strategic", "Butler Graves",
                "\"I think she is intelligent, my lady. And intelligence in service of ambition is a "
                "tool that should be respected and watched very carefully.\" He adjusts his cuffs. "
                "\"I have managed this household through three generations of Aldric politics. I know "
                "ambition when I see it. Miss Elena's ambition is... significant.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_suspicious", "Butler Graves",
                "\"Suspicious is too strong. Let us say... attentive.\" He chooses words like a diplomat. "
                "\"A good butler notices patterns. Miss Elena's pattern is one of systematic relationship-"
                "building. She began with the servants, moved to the family's peripheral members, and is "
                "now working toward the Duke himself.\" He tilts his head. \"It is the same approach I "
                "would use if I were trying to secure a permanent place in a household not my own. "
                "The difference is, I would not be so obvious about it.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_movements", "Butler Graves",
                "\"I maintain a record of all guest movements as a matter of protocol.\" He opens his "
                "notebook to a specific page. \"Miss Elena has been observed in the library on four "
                "occasions outside of reading hours. She visited the garden at dawn three times this "
                "week. She spent twenty minutes in the hallway near the Duke's study on Tuesday, though "
                "she did not enter.\" He looks up. \"Most concerning, she was near the servants' quarters "
                "at an hour when the corridor should have been empty. She claimed she was lost.\"",
                {
                    {"Lost? In a corridor she has walked every day?", "graves_elena_lost", nullptr, nullptr},
                    {"Keep tracking her.", "graves_elena_track", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "butler_graves")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_lost", "Butler Graves",
                "\"Precisely, my lady. The servants' corridor is a straight line from the kitchen to "
                "the quarters. There is nowhere to become lost unless one is deliberately looking for "
                "something.\" His voice is dry. \"I escorted her back to the guest room personally and "
                "noted that she glanced at every door we passed, as if cataloguing them.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_track", "Butler Graves",
                "\"Consider it done, my lady. I will maintain detailed records of her movements "
                "and report anything that deviates from her established patterns. The household is "
                "my domain, and nothing passes through it without my notice.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_elena_questions", "Butler Graves",
                "\"She has asked about the family history on several occasions, framed as polite "
                "interest in the estate.\" Graves's tone sharpens slightly. \"She inquired about "
                "the late Duchess, your mother, particularly about her social connections before marriage. "
                "She asked Lady Rosalind about the family's political alliances. And she asked me, "
                "directly, about the Duke's daily routine.\" He meets your eyes. \"I provided only "
                "what is public knowledge. But her questions were specific enough to suggest she already "
                "knew some of the answers.\"",
                {
                    {"She is gathering intelligence.", "graves_root", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_deliver", "Butler Graves",
                "\"I am at your disposal, my lady. What needs to be delivered, and to whom?\"",
                {
                    {"Deliver an invitation to Elena for dinner.", "graves_deliver_invitation",
                     [](const GameState &gs)
                     {
                         for (const auto &item : gs.player.inventory)
                         {
                             if (item == "invitation_letter")
                             {
                                 return true;
                             }
                         }
                         return false;
                     },
                     [](GameState &gs)
                     {
                         auto &inv = gs.player.inventory;
                         inv.erase(
                             std::remove(inv.begin(), inv.end(),
                                         std::string("invitation_letter")),
                             inv.end());
                         gs.quest.elena_arrived_dinner = true;
                     }},
                    {"Deliver a message to the servants.", "graves_deliver_servants", nullptr, nullptr},
                    {"Never mind.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_deliver_invitation", "Butler Graves",
                "Graves takes the invitation with white-gloved hands, examines the seal, and nods. "
                "\"I will deliver this to Miss Elena's quarters immediately, my lady. I will ensure she "
                "understands the formality of the occasion and is prepared appropriately.\" He pauses. "
                "\"Shall I also inform Chef Marcel to set an additional place at table? And should I "
                "brief the serving staff on any particular... protocol for the evening?\"",
                {
                    {"Full formal service. Make it imposing.", "graves_formal_dinner", nullptr, nullptr},
                    {"Keep it relaxed. I want her comfortable.", "graves_casual_dinner", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_formal_dinner", "Butler Graves",
                "\"Full formal service. Very good, my lady.\" There is the faintest hint of approval. "
                "\"I will arrange the extended silverware setting, the crystal glassware, and the formal "
                "candelabra. Every course will be announced, every glass filled by a different servant. "
                "It will be a display of the Aldric household at its most... overwhelming.\" He permits "
                "himself a thin smile. \"If the goal is to remind our guest of the distance between "
                "her world and ours, there is no better tool than a perfectly executed formal dinner.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_casual_dinner", "Butler Graves",
                "Graves's eyebrows rise, just barely. \"A relaxed dinner, my lady? That is... unusual, "
                "for an Aldric family event with a guest.\" But he nods. \"Very well. Simple place "
                "settings, a single wine, family-style serving. I will instruct the staff to be warm "
                "and unobtrusive.\" He considers. \"A comfortable guest is sometimes a more revealing "
                "one. An astute approach, if I may say so.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_deliver_servants", "Butler Graves",
                "\"A message to the servants?\" He straightens. \"I can assemble the senior staff in "
                "the servants' hall within the hour, or I can convey a message discreetly to specific "
                "individuals. What is the nature of the communication?\"",
                {
                    {"Tell them to keep their distance from Elena.", "graves_distance_elena", nullptr, [](GameState &gs)
                     {
                         gs.heroine_popularity -= 3;
                     }},
                    {"Tell them I appreciate their service.", "graves_appreciate", nullptr, [](GameState &gs)
                     {
                         gs.player.reputation += 3;
                         gs.quest.servants_loyal = true;
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_distance_elena", "Butler Graves",
                "\"I understand, my lady. I will frame it as a matter of professional propriety. "
                "'The guest is to be treated with respect but not familiarity. All interactions are to "
                "remain formal and task-oriented.'\" He closes his notebook. \"It will be effective. "
                "The staff trust my directives, and most will comply without question. Clara may need "
                "additional... emphasis.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_appreciate", "Butler Graves",
                "Something shifts in Graves's expression, a softening that is gone almost before "
                "it appears. \"That is... a kind gesture, my lady. And a wise one. Staff who feel "
                "valued are staff who serve with dedication rather than mere duty.\" He bows. "
                "\"I will convey your gratitude at the evening assembly. It will mean more than "
                "you might expect.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hire", "Butler Graves",
                "Graves folds his hands behind his back, a posture you have come to recognize as "
                "his negotiating stance. \"I serve this household freely, my lady, as is my duty. "
                "However, certain tasks fall outside the traditional scope of a butler's responsibilities. "
                "For those, compensation ensures... discretion.\"",
                {
                    {"Spread rumors about Elena. (15 gold)", "graves_hire_rumors", [](const GameState &gs)
                     {
                         return gs.player.gold >= 15 && !gs.quest.rumors_spread;
                     },
                     {}},
                    {"Monitor all of Elena's correspondence. (20 gold)", "graves_hire_letters", [](const GameState &gs)
                     { return gs.player.gold >= 20; }, [](GameState &gs)
                     {
                    gs.player.gold -= 20;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "butler_graves") {
                            n.second.affection += 5;
                            break;
                        }
                    } }},
                    {"Restrict Elena's access to certain rooms. (10 gold)", "graves_hire_restrict", [](const GameState &gs)
                     { return gs.player.gold >= 10; }, [](GameState &gs)
                     {
                    gs.player.gold -= 10;
                    gs.heroine_popularity -= 2; }},
                    {"Gather intelligence from the servants. (15 gold)", "graves_hire_intel", [](const GameState &gs)
                     { return gs.player.gold >= 15; }, [](GameState &gs)
                     {
                    gs.player.gold -= 15;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "butler_graves") {
                            n.second.affection += 5;
                            break;
                        }
                    } }},
                    {"Never mind.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hire_rumors", "Butler Graves",
                "Graves accepts the gold with the same dignity with which he accepts a dinner order. "
                "\"Rumors are a delicate instrument, my lady. Too crude and they are dismissed. Too "
                "subtle and they go unnoticed.\" He tucks the coins away. \"I will plant concerns among "
                "the senior servants first. Questions about Miss Elena's background, her true intentions, "
                "why a commoner would be given such unprecedented access to a noble household.\" He pauses. "
                "\"Within three days, the whispers will reach the Duke's ears through natural channels. "
                "No one will trace them back to either of us.\"",
                {
                    {"Perfect.", "graves_rumors_done", nullptr, [](GameState &gs)
                     {
                         gs.player.gold -= 15;
                         gs.quest.rumors_spread = true;
                         gs.heroine_popularity -= 5;
                         gs.player.suspicion += 3;
                     }},
                },
                false);

        addNode(state, "graves_rumors_done", "Butler Graves",
                "\"Consider it done, my lady. The household will begin to question what it has "
                "so readily accepted. And doubt, once planted, is remarkably difficult to uproot.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hire_letters", "Butler Graves",
                "\"All correspondence that enters or leaves the estate passes through the mail room, "
                "which I oversee.\" He speaks as if this were the most natural arrangement. \"I can "
                "create copies of any letters addressed to or from Miss Elena before they are delivered. "
                "She will never know her correspondence has been read.\" He adjusts his cuffs. "
                "\"I should mention that I have already noticed she receives letters sealed with an "
                "unusual mark, a flower pressed into the wax. Not a family crest I recognize.\"",
                {
                    {"A flower seal? Describe it.", "graves_flower_seal", nullptr, nullptr},
                    {"Just keep copies for me.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_flower_seal", "Butler Graves",
                "\"An iris, I believe. Stylized, not a personal design but something more formal. "
                "Like a guild mark or an organization's seal.\" He frowns. \"I have seen it once before, "
                "years ago, on correspondence that passed through the capital's political circles. "
                "It was associated with a group known as the Iris Consortium, though details were scarce "
                "even then.\" He meets your eyes. \"If Miss Elena is connected to such people, her "
                "presence here may have implications beyond mere social climbing.\"",
                {
                    {"The Iris Consortium. I have heard of them.", "graves_iris_known", [](const GameState &gs)
                     { return gs.quest.elena_letters_found; },
                     {}},
                    {"Find out everything you can.", "graves_root", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "butler_graves")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_iris_known", "Butler Graves",
                "\"Then you know more than most, my lady. The Consortium operates in shadows, "
                "connecting people of influence across provincial lines. If Elena is their agent, "
                "then her target is not merely your reputation or social standing.\" His voice drops. "
                "\"It is the Aldric family's political position itself. And perhaps the Duke's seat.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hire_restrict", "Butler Graves",
                "\"Easily arranged, my lady. As butler, I control the household keys. I can ensure "
                "that certain doors are locked during hours when Miss Elena is known to wander.\" "
                "He produces a heavy ring of keys. \"The library, the Duke's study, the cellar, "
                "the servants' quarters, all can be made inaccessible with a simple change in "
                "the locking schedule. She will find closed doors where there were open ones, "
                "and I will express polite regret about 'security concerns.'\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_hire_intel", "Butler Graves",
                "\"Intelligence from the servants?\" He nods approvingly. \"The servants hear and see "
                "everything, my lady. They move through rooms as if invisible, and people speak freely "
                "in their presence.\" He takes the gold. \"I will conduct quiet interviews over the "
                "coming days. Who Elena speaks with, what she asks about, where she goes when she thinks "
                "no one is watching. The servants' network is more effective than any spy ring, because "
                "no one suspects the people who bring the tea.\"",
                {
                    {"Report back as soon as you learn anything.", "graves_intel_report", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_intel_report", "Butler Graves",
                "\"I already have preliminary findings, my lady. The kitchen maid reports that Elena "
                "asked about the cellar locks. The laundry girl noticed Elena examining your brother's "
                "riding schedule, which is posted in the servants' hall. And the gardener's boy saw "
                "Elena speaking with someone at the estate boundary wall after dark.\" He closes his "
                "notebook. \"Someone outside the household. They exchanged what appeared to be papers.\"",
                {
                    {"Papers? At the wall?", "graves_intel_wall", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_intel_wall", "Butler Graves",
                "\"At the southeast corner, where the wall is lowest and the garden path runs close. "
                "The boy could not see clearly in the dark, but he described Elena handing a folded "
                "document to a figure on the other side, who gave her something flat in return.\" "
                "Graves's expression is grave. \"Another letter, most likely. My lady, if Elena is "
                "passing information to contacts outside the estate, this is more serious than social "
                "maneuvering. This is espionage.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_loyalty", "Butler Graves",
                "Graves pauses, weighing his response. \"The staff's loyalty is divided, my lady. "
                "I will be frank with you.\" He folds his hands precisely. \"The senior servants, "
                "myself, Captain Roderick, Chef Marcel, we are loyal to the Aldric family without "
                "question. We have served too long and owe too much to waver.\" He pauses. "
                "\"The junior staff are more... impressionable. Elena has made inroads with the younger "
                "servants. The scullery maids, the stable boys, the laundry girls. They see her as a "
                "kindred spirit, someone who rose from common origins.\"",
                {
                    {"How do I win them back?", "graves_loyalty_win", nullptr, nullptr},
                    {"Is Clara loyal?", "graves_clara_loyalty", nullptr, nullptr},
                    {"Is Thorne reliable?", "graves_thorne_loyalty", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_loyalty_win", "Butler Graves",
                "\"Kindness, my lady. Not grand gestures, those seem calculating. Small, genuine acts. "
                "Learn a name. Ask after a child's illness. Ensure their quarters are warm and their meals "
                "are adequate.\" He meets your eyes. \"Your mother won the staff's devotion not through "
                "her rank, but through her attention. Elena is copying that approach. You must reclaim it "
                "as your own.\" He pauses. \"Alternatively, you can ensure that the servants understand "
                "where their employment and their security truly rest. Loyalty born of trust is strongest, "
                "but loyalty born of pragmatism is more reliable.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_clara_loyalty", "Butler Graves",
                "\"Clara is loyal to the household, and specifically to you, my lady. She gossips, "
                "yes, but she gossips in your favor more often than not.\" He allows himself a moment "
                "of candor. \"She is easily influenced, which means she could be swayed by Elena's charm "
                "if left unchecked. But she is also perceptive in her way, she notices things that others "
                "miss because she is always watching, always listening.\" He pauses. \"Keep her close, "
                "and keep her feeling valued. She will be your most willing informant.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_thorne_loyalty", "Butler Graves",
                "\"Thorne is a private man. He keeps to his garden, speaks little, and trusts no one "
                "easily.\" Graves chooses his words with care. \"He is loyal to the estate itself, to "
                "the land and the history, rather than to any individual. He will do what he believes "
                "protects the Aldric legacy, even if it means acting without orders.\" He pauses. "
                "\"That independence makes him valuable but unpredictable. I would not rely on him for "
                "tasks that require strict obedience. But for information about what moves through "
                "the grounds, there is no one better.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_post_rumors", "Butler Graves",
                "Graves permits himself a look of professional satisfaction. \"The rumors have taken "
                "root, my lady. The kitchen staff have been discussing Elena's background with increasing "
                "skepticism. The Duke's valet mentioned that His Grace asked pointed questions about "
                "Elena's references at breakfast.\" He consults his notebook. \"Heroine popularity among "
                "the servants has dropped noticeably. She is still well-liked, but the unconditional warmth "
                "has cooled to cautious courtesy.\"",
                {
                    {"Good. Keep the pressure on.", "graves_rumors_continue", nullptr, nullptr},
                    {"Is there any risk of it coming back to me?", "graves_rumors_risk", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_rumors_continue", "Butler Graves",
                "\"I will maintain the campaign with the same subtlety. A comment here, a raised eyebrow "
                "there. The beauty of well-crafted rumors is that they generate their own momentum. "
                "People will begin filling in details I never provided, each imagining the worst "
                "interpretation.\" He nods. \"By week's end, the household will be openly questioning "
                "why a commoner is given such privileges under this roof.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_rumors_risk", "Butler Graves",
                "\"The risk is minimal, my lady. I have been managing household information for decades. "
                "The seeds were planted through proxy, nothing traces directly to either of us.\" He "
                "considers. \"The only vulnerability is if someone were to interview every servant "
                "individually and reconstruct the timeline of when each rumor appeared. But that would "
                "require Captain Roderick's thoroughness and Clara's curiosity combined, and fortunately "
                "those two rarely cooperate.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_post_expulsion", "Butler Graves",
                "Graves nods slowly, his expression measured. \"The household is adjusting, my lady. "
                "The Duke's decision to expel Miss Elena was received with mixed reactions. The senior "
                "staff are relieved. The junior staff are disrupted, some are angry, believing Elena was "
                "treated unfairly.\" He straightens a painting on the wall that was already perfectly "
                "straight. \"I have maintained order through routine. When people do not know what to feel, "
                "they find comfort in structure. Meals at the regular hour. Duties unchanged. The household "
                "clock continues to tick.\"",
                {
                    {"Any concerns about the staff?", "graves_exp_staff", nullptr, nullptr},
                    {"Has anyone tried to contact Elena since?", "graves_exp_contact", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_exp_staff", "Butler Graves",
                "\"Two of the scullery maids wept. One of the stable boys was overheard saying "
                "unkind things about the family, which I addressed firmly and privately.\" His jaw "
                "tightens. \"Clara has been useful in this regard, reminding the younger servants that "
                "the Duke's decisions are not open to debate. Chef Marcel's kitchen runs on discipline, "
                "which helps. Thorne, as always, says nothing.\" He pauses. \"Give it a week, my lady. "
                "The household will settle. It always does.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_exp_contact", "Butler Graves",
                "\"I have been monitoring all correspondence, as you would expect.\" He opens his "
                "notebook. \"No letters have arrived addressed to Miss Elena since her departure. "
                "However, the stable boy, the one who spoke out, attempted to send a letter to an "
                "address in the capital. I intercepted it.\" He produces a folded paper. \"It contained "
                "a sympathetic account of Elena's expulsion and a request for 'further instructions.' "
                "It appears Miss Elena had at least one loyal agent remaining in this household.\"",
                {
                    {"The stable boy is her spy?", "graves_exp_spy", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_exp_spy", "Butler Graves",
                "\"Unwitting, most likely. A young man charmed by a beautiful woman's attention, "
                "not a trained operative.\" He folds the letter carefully. \"I have two options: "
                "dismiss him, which sends a clear message, or keep him in place and feed him "
                "information we want Elena to receive.\" He meets your eyes. \"The latter is more "
                "useful, if more complicated. Your choice, my lady.\"",
                {
                    {"Keep him. Feed him what we want Elena to hear.", "graves_exp_keep", nullptr, [](GameState &gs)
                     {
                         gs.player.reputation += 2;
                     }},
                    {"Dismiss him immediately.", "graves_exp_dismiss", nullptr, [](GameState &gs)
                     {
                         gs.player.suspicion += 2;
                     }},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_exp_keep", "Butler Graves",
                "\"A strategic choice, my lady. I will ensure the boy believes he is acting on his "
                "own initiative while every piece of information he sends is carefully curated by me.\" "
                "The ghost of a smile appears. \"Your grandfather would have made the same decision. "
                "He understood that a known spy is more valuable than an unknown one.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_exp_dismiss", "Butler Graves",
                "\"Understood. I will handle it today. He will be given a month's wages and a reference "
                "that says nothing remarkable.\" His expression is practical. \"It closes one information "
                "channel but sends a clear signal that disloyalty has consequences. The remaining staff "
                "will take note.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_post_death", "Butler Graves",
                "Graves stands absolutely still. The composure he wears like armor has never seemed more "
                "rigid. \"My lady.\" His voice is steady but stripped of its usual warmth. \"The household "
                "is in shock. I have confined the staff to their quarters pending the Duke's orders. "
                "Captain Roderick is securing the estate. Chef Marcel has closed the kitchen.\" He meets "
                "your eyes, and in them you see something you have never seen before: fear. \"Whatever "
                "happened, whatever the circumstances, the household must present a unified front. "
                "Cracks invite investigation, and investigation invites ruin.\"",
                {
                    {"Can you manage the staff?", "graves_death_staff", nullptr, nullptr},
                    {"What should I tell Father?", "graves_death_duke", nullptr, nullptr},
                    {"You know nothing. Remember that.", "graves_death_silence", nullptr, nullptr},
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_death_staff", "Butler Graves",
                "\"I have already begun. Each servant will be spoken to individually. Their accounts "
                "will be consistent: they saw nothing unusual, heard nothing, and retired at the normal "
                "hour.\" He swallows. \"The truth is, most of them genuinely saw nothing. The household "
                "routine provides its own alibi. It is the gaps in that routine that concern me, and "
                "those gaps, I will ensure are filled with plausible activity.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_death_duke", "Butler Graves",
                "\"The Duke will want answers, my lady. He is not a man who accepts mystery easily.\" "
                "Graves considers carefully. \"I would suggest presenting it as a tragic accident. "
                "A fall, a sudden illness, something that invites sympathy rather than investigation. "
                "If outside authorities become involved, if the magistrate sends an investigator, "
                "the entire household comes under scrutiny.\" He pauses. \"And scrutiny, my lady, "
                "is something none of us can afford right now.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_death_silence", "Butler Graves",
                "Graves holds your gaze for a long, weighted moment. \"I have served this household "
                "for twenty-seven years, my lady. In that time, I have heard nothing, seen nothing, "
                "and remembered nothing that was not in the family's interest.\" He bows, a fraction "
                "deeper than usual. \"That tradition continues. Whatever you need forgotten will be "
                "forgotten. Whatever you need remembered will be documented.\" He straightens. "
                "\"I serve the Aldric household. That is all anyone needs to know.\"",
                {
                    {"Back to other matters.", "graves_root", nullptr, nullptr},
                },
                false);

        addNode(state, "graves_farewell", "Butler Graves",
                "Graves bows with exact precision. \"My lady. The household stands ready "
                "at your convenience.\"",
                {}, true);
    }

}


void registerButlerGraves(GameState &state)
{
    NPC n;
    n.id = "butler_graves";
    n.name = "Butler Graves";
    n.title = "Head Butler";
    n.description = "The impeccable head butler of the Aldric estate. His loyalty is absolute\n"
                    "and his knowledge of the household, encyclopedic.";
    n.current_room = "hallway";
    n.affection = 50;
    n.suspicion = 5;
    n.disposition = Disposition::Loyal;
    n.dialogue_root = "graves_root";
    n.traits = {Trait::Loyal_Trait, Trait::Secretive, Trait::EarlyBird};
    n.hireable = true;
    n.hire_cost = 15;
    n.schedule = {
        {5, "kitchen"},
        {6, "hallway"},
        {8, "dining_room"},
        {9, "hallway"},
        {11, "grand_hall"},
        {12, "dining_room"},
        {13, "hallway"},
        {15, "fathers_study"},
        {17, "hallway"},
        {19, "dining_room"},
        {21, "hallway"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildGravesDialogue(state);
}
