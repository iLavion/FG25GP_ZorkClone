#include "game.hpp"
#include "game/dialogue_helpers.hpp"

namespace game::npcs
{

void buildClaraDialogue(GameState& state)
{
    addNode(state, "clara_root", "Maid Clara",
        "Clara is fluffing cushions in the hallway, though she seems more interested in looking "
        "around corners than in her work. She brightens the moment she spots you, dropping her "
        "duster with a conspiratorial grin. \"My lady! I was hoping you would come by. You would "
        "not believe what I have heard today.\"",
        {
            {"What have you heard?", "clara_gossip_hub", nullptr, nullptr},
            {"Tell me about yourself, Clara.", "clara_backstory", nullptr, nullptr},
            {"What do you know about Elena?", "clara_elena", nullptr, nullptr},
            {"I need to hire you for something.", "clara_hire",
                [](const GameState&) { return true; }, nullptr},
            {"How are the other servants?", "clara_servants", nullptr, nullptr},
            {"[After letters found] About those letters...", "clara_post_letters",
                [](const GameState& gs) { return gs.quest.elena_letters_found; }, nullptr},
            {"[After Elena's expulsion] What is everyone saying?", "clara_post_expulsion",
                [](const GameState& gs) { return gs.quest.elena_expelled; }, nullptr},
            {"[After body discovered] Clara, I need your help.", "clara_post_death",
                [](const GameState& gs) { return gs.quest.body_discovered; }, nullptr},
            {"I should go.", "clara_farewell", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_hub", "Maid Clara",
        "Clara glances both ways down the corridor before leaning in close, practically vibrating "
        "with the weight of unshared information. \"Where do I even start? I have news about "
        "everyone.\"",
        {
            {"Tell me about Lord Cedric.", "clara_gossip_cedric", nullptr, nullptr},
            {"Anything about the Prince?", "clara_gossip_prince", nullptr, nullptr},
            {"What is the kitchen gossip?", "clara_gossip_kitchen", nullptr, nullptr},
            {"What have you heard about the guest room?", "clara_gossip_guest",
                [](const GameState& gs) {
                    for (const auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            return n.second.affection >= 40;
                        }
                    }
                    return false;
                }, nullptr},
            {"Tell me the servants' gossip.", "clara_gossip_servants", nullptr, nullptr},
            {"What about Father?", "clara_gossip_duke", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_cedric", "Maid Clara",
        "Clara's eyes widen with barely suppressed excitement. \"Lord Cedric has been pacing "
        "his room at night, my lady. I hear his boots on the floor when I do the late rounds. "
        "Back and forth, back and forth.\" She lowers her voice. \"And he has been writing letters "
        "he does not send through the regular mail. He hands them directly to the stable boy for "
        "delivery. Very secretive.\" She taps her nose. \"Also, and I probably should not mention "
        "this, I found a pressed flower in one of his books when I was dusting. A white rose.\"",
        {
            {"A white rose? From the east wall?", "clara_cedric_rose", nullptr, nullptr},
            {"Who is he writing to?", "clara_cedric_letters", nullptr, nullptr},
            {"More gossip, please.", "clara_gossip_hub", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_cedric_rose", "Maid Clara",
        "\"I think so! The same ones Elena has been visiting at dawn, the white ones. But here "
        "is the interesting bit, the rose was pressed between the pages of a poetry book.\" Clara "
        "puts her hand to her heart dramatically. \"My lady, I think Lord Cedric might have "
        "feelings that are... complicated. He watches Elena with an expression I cannot quite "
        "read. Not suspicious exactly, more like someone fighting against something.\"",
        {
            {"Cedric and Elena? That is a problem.", "clara_cedric_elena_problem", nullptr, nullptr},
            {"You are reading too much into it.", "clara_reading_too_much", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_cedric_elena_problem", "Maid Clara",
        "\"I know, I know. It is terribly inconvenient.\" Clara wrings her hands but cannot hide "
        "a note of romantic excitement. \"But emotions do not follow politics, my lady. I have seen "
        "it before in other houses. The young lord falls for the person he should not, and it all "
        "gets messy.\" She becomes more serious. \"If Elena knows about his feelings, she could use "
        "them. That is the real danger, is it not?\"",
        {
            {"Exactly. Keep watching this.", "clara_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_reading_too_much", "Maid Clara",
        "\"Maybe.\" She does not sound convinced. \"But fifteen years of service has taught me "
        "to read body language like a book, my lady. People think servants are furniture. They do "
        "not guard their expressions when we are in the room.\" She shrugs. \"I could be wrong. "
        "I hope I am wrong. Lord Cedric is too good a man to be tangled up with someone who "
        "might be playing the entire household.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_cedric_letters", "Maid Clara",
        "\"I could not read them, obviously. I am no snoop.\" She pauses, clearly considering "
        "herself exactly a snoop. \"But the stable boy told me, in confidence of course, that the "
        "letters go to an address in the capital. A law office, I think. Something and something "
        "'Associates.' He could not read the full name.\" She frowns. \"Why would Lord Cedric be "
        "writing to lawyers in the capital?\"",
        {
            {"Interesting. Keep me informed.", "clara_root", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_prince", "Maid Clara",
        "\"Oh, the Prince!\" Clara practically squeals before catching herself. \"Word from the "
        "capital is that Prince Aldrich, yes same name as your father's family, different branch, "
        "he has been asking about Elena. Specifically about her stay here.\" She becomes more "
        "serious. \"His personal secretary wrote to Graves asking for a 'progress report' on "
        "Elena's wellbeing. Graves showed me the letter because he wanted my opinion on the tone.\" "
        "She pauses. \"The tone was proprietary, my lady. As if the Prince considers Elena his "
        "investment, not merely his acquaintance.\"",
        {
            {"The Prince sent her here?", "clara_prince_sent", nullptr, nullptr},
            {"What else do you know about the Prince?", "clara_prince_more", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_prince_sent", "Maid Clara",
        "\"I did not say that. But...\" She bites her lip. \"Lord Ashworth introduced Elena, yes. "
        "But what if Ashworth was acting on the Prince's behalf? A royal endorsement would be too "
        "obvious, too political. A noble's introduction is much more natural.\" She speaks with "
        "surprising analytical skill. \"If the Prince wants Elena positioned in noble households, "
        "he would use intermediaries. And Ashworth owes the crown several favors.\"",
        {
            {"You are sharper than people give you credit for.", "clara_sharp", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_sharp", "Maid Clara",
        "Clara looks genuinely touched. \"Thank you, my lady. People think I am just a gossip. "
        "And I am! But gossip is intelligence, is it not? You just have to sort the useful bits "
        "from the noise.\" She straightens proudly. \"My mother was a lady's maid in the capital "
        "before she married. She taught me that knowing things is the only power a servant has. "
        "And I have been collecting power my entire career.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_prince_more", "Maid Clara",
        "\"He is young, ambitious, and charming by all accounts. Third in line for the throne, "
        "which means he needs to build a power base of his own if he ever wants to matter.\" "
        "She lowers her voice. \"Noble families are the pieces on his game board, my lady. "
        "He courts the ones with influence and undercuts the ones who oppose him. The Aldric "
        "family, with its military heritage and provincial control, would be a significant piece "
        "to acquire.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_kitchen", "Maid Clara",
        "\"Chef Marcel is in a mood, more than usual. He caught one of the scullery maids giving "
        "Elena a pastry between meals and nearly threw a ladle at her.\" Clara giggles. \"Not at "
        "Elena, at the maid. Marcel does not waste good pastries on drama.\" She becomes more "
        "serious. \"But he also mentioned inventory problems to Graves. Wine and food going missing "
        "from the cellar. Marcel keeps meticulous records, so if he says things are disappearing, "
        "they are disappearing.\"",
        {
            {"Who do you think is taking things?", "clara_kitchen_thief", nullptr, nullptr},
            {"More gossip, please.", "clara_gossip_hub", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_kitchen_thief", "Maid Clara",
        "\"Well...\" She draws out the word, enjoying the dramatic tension. \"The cellar is "
        "locked at night, and Marcel keeps the key. But the cellar also connects to the old "
        "foundation passages, does it not? If someone knew about those, they could access the "
        "stores without a key.\" She gives you a knowing look. \"And we both know who has been "
        "exploring every corner of this estate with suspicious thoroughness.\"",
        {
            {"Elena.", "clara_kitchen_elena", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_kitchen_elena", "Maid Clara",
        "\"I am not accusing anyone, my lady. I am merely... connecting observations.\" She "
        "tries to look innocent and fails entirely. \"But yes. If I were a guest with secret "
        "knowledge of the estate's old passages, and I needed to move supplies to someone or "
        "somewhere without detection, the cellar would be the logical staging point.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_guest", "Maid Clara",
        "Clara drops her voice to barely a whisper and pulls you into an alcove. \"My lady, "
        "I clean the guest room every morning. And I have noticed things.\" Her eyes are wide. "
        "\"Elena makes her bed before I arrive, which is suspicious in itself, no guest does that. "
        "But she does not make it well enough to hide that she barely sleeps in it.\" Clara holds "
        "up a finger. \"The pillow is barely dented. The sheets are smooth. She either sleeps like "
        "the dead or she does not sleep in that bed at all.\"",
        {
            {"Where else would she sleep?", "clara_guest_where", nullptr, nullptr},
            {"What else have you found?", "clara_guest_findings", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_guest_where", "Maid Clara",
        "\"That is the question, is it not?\" Clara bites her lip. \"She could be spending her "
        "nights elsewhere in the estate, in the library reading, in the cellar doing whatever "
        "she does there, or...\" She pauses. \"Or she could be leaving the estate at night through "
        "those passages everyone whispers about. I do not know which is more unsettling.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_guest_findings", "Maid Clara",
        "Clara reaches into her apron pocket and produces a small, folded piece of paper. \"I found "
        "this behind the washstand. It must have fallen.\" She unfolds it carefully. \"It is a list "
        "of names, my lady. Noble families. Ours is on it, along with maybe eight or nine others. "
        "Some are crossed out. Some have notes beside them in a script I cannot read.\" She hands it "
        "to you. \"This is not a guest list or a social calendar. It looks like... a target list.\"",
        {
            {"This could be exactly what we need.", "clara_guest_evidence", nullptr,
                [](GameState& gs) {
                    gs.quest.elena_letters_found = true;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Put it back. She cannot know we found it.", "clara_guest_replace", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_guest_evidence", "Maid Clara",
        "\"Keep it, my lady. I have already memorized the names on it, just in case.\" She taps "
        "her temple. \"Aldric, Montfort, Blackwood, Ravenshollow, three more I did not recognize. "
        "All noble families, all with significant landholdings.\" She straightens with obvious pride. "
        "\"I told you, gossip is intelligence. And sometimes it falls right into your hands, "
        "literally.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_guest_replace", "Maid Clara",
        "\"Smart thinking, my lady. If she discovers the list is missing, she will know someone "
        "found it and become more careful.\" Clara refolds the paper precisely. \"I will place it "
        "back exactly where I found it tomorrow morning. She will never know.\" She pauses. "
        "\"But now we both know what is on it. That knowledge cannot be un-had.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_servants", "Maid Clara",
        "\"The staff is split, my lady. The older servants, Graves, Marcel, Roderick, they are "
        "loyal to the family. They have been here too long to be swayed.\" She glances around. "
        "\"But the younger ones? The scullery maids, the stable boys, the laundry girls? Elena "
        "has them wrapped around her little finger. She remembers their birthdays, for goodness' "
        "sake. I have worked here fifteen years and I cannot remember half their names.\"",
        {
            {"That is a problem.", "clara_servants_problem", nullptr, nullptr},
            {"Can you bring them back to our side?", "clara_servants_reclaim", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants_problem", "Maid Clara",
        "\"It is, my lady. A divided household leaks like a cracked pot. The young ones talk "
        "to Elena about everything: the Duke's schedule, who visits, what letters arrive, when the "
        "family argues.\" She wrings her hands. \"They do not think they are doing anything wrong. "
        "They are just chatting with a friendly woman who asks nice questions. But every answer "
        "gives her more information.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants_reclaim", "Maid Clara",
        "\"Me?\" She looks both nervous and flattered. \"I suppose I could. I have seniority, and "
        "the younger ones do look up to me, even if they also think I am a busybody.\" She considers. "
        "\"I could start holding evening gatherings in the servants' hall. Tea, biscuits, a warm fire. "
        "Create a space that is ours, where Elena is not invited. Rebuild the sense of staff unity "
        "that she has eroded.\" She nods firmly. \"Yes. I can do that.\"",
        {
            {"Do it. You have my support.", "clara_servants_rally", nullptr,
                [](GameState& gs) {
                    gs.quest.servants_loyal = true;
                    gs.heroine_popularity -= 3;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants_rally", "Maid Clara",
        "Clara squares her shoulders with determination. \"Consider it done, my lady. By week's "
        "end, the servants' hall will be the heart of this estate again, and I will be the one "
        "pouring the tea.\" She pauses. \"And if any of the young ones starts sharing household "
        "business with outsiders, they will answer to me. I may be a gossip, but I am the family's "
        "gossip, not Elena's.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_gossip_duke", "Maid Clara",
        "Clara becomes subdued, more careful. \"The Duke has been different lately, my lady. "
        "More closed off. He eats alone in the study instead of with the family. And he has been "
        "going through old correspondence, boxes of letters from years ago.\" She frowns. "
        "\"Graves said the Duke asked for the archive keys twice this week. He was looking for "
        "letters from the succession crisis period, twenty years ago.\"",
        {
            {"He is researching the Consortium.", "clara_duke_research", nullptr, nullptr},
            {"Is he alright?", "clara_duke_wellbeing", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_duke_research", "Maid Clara",
        "\"The Consortium?\" Clara's eyes go wide. \"I have heard that word whispered by "
        "Graves and Roderick when they thought no one was listening. Is that what this is about?\" "
        "She lowers her voice. \"If the Duke is digging through old crisis files, he must think "
        "something serious is happening. The Duke does not open archives for minor concerns.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_duke_wellbeing", "Maid Clara",
        "\"He is tired, my lady. Tired in the way that sleep does not fix.\" Clara's gossipy "
        "energy dims into genuine concern. \"I bring his morning tea and sometimes he is still "
        "awake from the night before, staring at papers. He has not touched the brandy though, "
        "which is a good sign. When the Duke drinks, that is when Graves and I worry.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_backstory", "Maid Clara",
        "Clara's constant energy stills for a moment. \"Me? No one ever asks about me.\" She "
        "sounds genuinely surprised. \"I came to the estate when I was fourteen. My mother was "
        "a lady's maid in the capital, as I mentioned. She trained me in the household arts, "
        "how to clean, how to organize, how to listen without appearing to.\" She smiles. "
        "\"Mother used to say, 'A good servant is invisible. A great servant is indispensable.'\"",
        {
            {"How did you end up here specifically?", "clara_backstory_arrival", nullptr, nullptr},
            {"Do you have family?", "clara_backstory_family", nullptr, nullptr},
            {"You are closer to 'indispensable' than you know.", "clara_backstory_praise", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 15;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_backstory_arrival", "Maid Clara",
        "\"My mother knew the Duchess, your mother. They grew up in adjacent households in the "
        "capital.\" Clara's voice softens. \"When my mother fell ill and could no longer work, "
        "the Duchess Helena offered me a position here. She said, 'Your mother served with grace. "
        "You carry the same gift.'\" Clara blinks rapidly. \"I was fourteen and terrified. But the "
        "Duchess was kind. She checked on me every week for my first year. Made sure I had warm "
        "clothes and enough food.\" She clears her throat. \"When she died, I felt like I lost a "
        "second mother. I have served this household with everything I have since then. For her.\"",
        {
            {"My mother was wonderful.", "clara_arrival_mother", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_arrival_mother", "Maid Clara",
        "\"She was.\" Clara's eyes are bright with unshed tears. \"And you are more like her "
        "than you know, my lady. You have the same determination. The same way of looking at "
        "people as if you can see through them.\" She dabs her eyes with her apron. \"The Duchess "
        "would not have stood for what Elena is doing. And neither will I. Whatever you need, "
        "I am here.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_backstory_family", "Maid Clara",
        "\"My mother passed five years ago. Peacefully, in her sleep.\" Clara touches a small "
        "locket at her throat. \"No father that I know of. No siblings. The household is my "
        "family.\" She manages a smile. \"Graves is the stern uncle. Marcel is the grumpy "
        "cousin. Roderick is the overprotective brother. And the Duke's children are... well...\" "
        "She blushes. \"You are the closest thing to sisters I have ever had, my lady. "
        "You and Lady Rosalind.\"",
        {
            {"That means a lot to me, Clara.", "clara_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_backstory_praise", "Maid Clara",
        "Clara's hand goes to her heart. \"My lady...\" She actually tears up. \"No one has ever "
        "said that to me. Graves thinks I talk too much. Marcel thinks I get in the way. Roderick "
        "does not think about me at all.\" She straightens, composing herself. \"Thank you. "
        "I will prove you right. Whatever this household needs, whoever threatens it, I will "
        "be the first to know and the last to stop fighting.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_elena", "Maid Clara",
        "Clara's expression becomes complicated, a mix of suspicion and reluctant admiration. "
        "\"Elena. Where do I begin?\" She pulls you closer. \"She is smart, my lady. Dangerously "
        "smart. She plays the innocent country girl perfectly, but I have caught moments when the "
        "mask slips.\"",
        {
            {"When does the mask slip?", "clara_elena_mask", nullptr, nullptr},
            {"Has she tried to befriend you?", "clara_elena_befriend", nullptr, nullptr},
            {"What does she do when she thinks no one is watching?", "clara_elena_alone", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_elena_mask", "Maid Clara",
        "\"Small moments. When she thinks no one is looking, her expression changes completely. "
        "The warmth disappears, and there is this... calculation.\" Clara shudders slightly. "
        "\"I saw it once when she was talking to Rosalind. Your sister said something about the "
        "family's summer estate, and Elena's eyes sharpened like a hawk spotting a mouse. Just for "
        "a second.\" She snaps her fingers. \"Then the sweet smile was back, and she was asking "
        "Rosalind about her favorite flowers as if nothing happened.\"",
        {
            {"She is mapping our assets.", "clara_root", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_elena_befriend", "Maid Clara",
        "\"Oh yes. Brought me a ribbon from the market. Pale blue, very pretty.\" Clara touches "
        "her hair self-consciously. \"She asked about my work, my mother, my life before the estate. "
        "All very casual, very friendly.\" Her voice hardens. \"But she also asked about the "
        "household keys, who has them, how many copies exist. She asked about the Duke's study, "
        "whether he keeps it locked, who cleans it.\" Clara crosses her arms. \"A friend asks "
        "about your life. A spy asks about your access.\"",
        {
            {"You saw through her.", "clara_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_elena_alone", "Maid Clara",
        "\"That is where it gets really interesting, my lady.\" Clara is practically whispering "
        "now. \"Late at night, when she thinks the household is asleep, I have heard her moving "
        "about. Soft footsteps, careful doorknobs, the faint sound of the guest room window "
        "opening and closing.\" She pauses for effect. \"And twice, twice, I have heard her "
        "whispering. Not to herself. To someone else. Through the window, I think. Someone "
        "outside on the grounds.\"",
        {
            {"She is meeting someone at night?", "clara_elena_night", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_elena_night", "Maid Clara",
        "\"I believe so. The guest room window faces the garden, near the east wall. If someone "
        "stood beneath it in the shadows, they could have a conversation without being easily "
        "seen.\" Her voice drops further. \"Thorne might have seen who it is. He does late rounds "
        "through the garden. But he never tells me anything. Secretive old roots, the lot of them.\" "
        "She huffs. \"But I know what I heard, my lady. Elena is not alone in whatever she is doing.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_hire", "Maid Clara",
        "Clara straightens her apron and puts on what she probably considers a businesslike "
        "expression. \"I am entirely at your service, my lady. My skills include observation, "
        "information gathering, document handling, and... creative problem solving.\" She glances "
        "around. \"What do you need?\"",
        {
            {"Watch Elena and report everything. (10 gold)", "clara_hire_watch",
                [](const GameState& gs) { return gs.player.gold >= 10; },
                [](GameState& gs) {
                    gs.player.gold -= 10;
                    gs.quest.servants_loyal = true;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Sabotage Elena's belongings. (10 gold)", "clara_hire_sabotage",
                [](const GameState& gs) {
                    for (const auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            return gs.player.gold >= 10 && n.second.affection >= 50;
                        }
                    }
                    return false;
                },
                [](GameState& gs) {
                    gs.player.gold -= 10;
                    gs.heroine_popularity -= 3;
                    gs.player.suspicion += 3;
                }},
            {"Search the guest room thoroughly. (15 gold)", "clara_hire_search",
                [](const GameState& gs) { return gs.player.gold >= 15; },
                [](GameState& gs) {
                    gs.player.gold -= 15;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Rally the servants to support the family. (10 gold)", "clara_hire_rally",
                [](const GameState& gs) { return gs.player.gold >= 10; },
                [](GameState& gs) {
                    gs.player.gold -= 10;
                    gs.quest.servants_loyal = true;
                    gs.player.reputation += 3;
                    gs.heroine_popularity -= 3;
                }},
            {"Never mind.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_hire_watch", "Maid Clara",
        "Clara pockets the gold with practiced discretion. \"Consider it done, my lady. "
        "I clean her room, I pass her in corridors, I serve at table. I am invisible and "
        "everywhere.\" She ticks off items on her fingers. \"I will track: who she talks to, "
        "what she reads, where she goes, what time she returns to her room, and any items that "
        "appear or disappear from her belongings.\" She nods firmly. \"You will have a full "
        "report within two days.\"",
        {
            {"Perfect.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_hire_sabotage", "Maid Clara",
        "Clara bites her lip but nods. \"I can do it. Nothing destructive, nothing traceable. "
        "A dress that develops a mysterious stain before a formal event. Shoes that pinch because "
        "someone inserted a pebble. Hair oil accidentally replaced with something that makes it "
        "frizzy.\" She holds up her hands. \"Small humiliations that chip away at her confidence. "
        "Death by a thousand small inconveniences. And maids never get blamed because, well, "
        "these things just happen.\"",
        {
            {"Do it.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_hire_search", "Maid Clara",
        "\"A thorough search? Now that is my specialty.\" Clara cracks her knuckles, an unsettling "
        "gesture from a slight young woman. \"I clean that room daily. I know every floorboard that "
        "creaks, every drawer that sticks, every gap between the washstand and the wall.\" She nods. "
        "\"Give me one morning when Elena is occupied elsewhere, and I will take that room apart "
        "and put it back together without a single thing out of place. Anything hidden, I will find. "
        "Letters, documents, objects, anything.\"",
        {
            {"Find me something we can use.", "clara_search_go", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_search_go", "Maid Clara",
        "\"I will report back as soon as I have something.\" Clara's expression is deadly serious "
        "for once. \"But my lady, if I find something truly damning, what do I do? Take it? Leave "
        "it? Tell Graves?\"",
        {
            {"Take it. Bring it directly to me.", "clara_root", nullptr, nullptr},
            {"Leave it but memorize everything about it.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_hire_rally", "Maid Clara",
        "\"Rally the troops! Yes, I can absolutely do that.\" She is practically bouncing. "
        "\"I will organize the evening gatherings as we discussed. Tea, warmth, togetherness. "
        "I will remind the young ones who pays their wages and who has kept this household "
        "running for generations.\" She becomes serious. \"It is not about turning them against "
        "Elena. It is about reminding them where their loyalty should lie. The Aldric family "
        "fed them, housed them, and cared for their families long before any charming stranger "
        "arrived.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants", "Maid Clara",
        "\"The staff?\" Clara takes a mental inventory. \"Graves is Graves, steady as a stone "
        "wall. Marcel is grumpier than usual, which means worried. Roderick has doubled his patrol "
        "routes, which means alarmed.\" She counts on her fingers. \"Thorne barely speaks to "
        "anyone, which is normal. The scullery maids are distracted by Elena's attention. The "
        "stable boys are nervous because they sense something is wrong but do not know what.\"",
        {
            {"And you?", "clara_servants_self", nullptr, nullptr},
            {"What about Rosalind's tutor?", "clara_servants_tutor", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants_self", "Maid Clara",
        "Clara pauses, her perpetual energy briefly stalling. \"Me? I am... scared, my lady. "
        "Not of Elena specifically, but of what she represents. Change. Disruption. The possibility "
        "that this household I love could be torn apart by someone who does not value it the way "
        "we do.\" She straightens. \"But scared does not mean helpless. My mother taught me that "
        "too. 'Fear sharpens the senses,' she said. 'Listen to it, then act.'\"",
        {
            {"You are braver than you know, Clara.", "clara_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_servants_tutor", "Maid Clara",
        "\"Mr. Pemberton? He is a quiet man who keeps to the schoolroom and the library. "
        "Speaks to no one except Rosalind and occasionally the Duke about curriculum.\" She "
        "pauses. \"Although now that you mention it, I saw Elena leaving the schoolroom last "
        "Tuesday. Pemberton was flustered, which is unusual for him. He would not tell me "
        "what they discussed.\" She frowns. \"Another thread to pull, my lady.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_post_letters", "Maid Clara",
        "Clara's voice is taut with excitement. \"My lady, I have been checking the guest room "
        "more carefully since the letters were found. And I discovered something new.\" She pulls "
        "a scrap of paper from her apron. \"A torn corner of a letter, caught behind the mirror "
        "frame. It has part of a sentence: '...the third house falls before winter. Proceed to the "
        "Montfort estate per...' The rest is torn.\" She clutches it. \"Third house. Is the Aldric "
        "estate considered the third? And Montfort, that is the family two provinces east.\"",
        {
            {"She is moving to another target after us.", "clara_letters_target", nullptr, nullptr},
            {"Show this to the Duke immediately.", "clara_letters_duke", nullptr,
                [](GameState& gs) {
                    gs.quest.duke_suspicious_elena = true;
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_letters_target", "Maid Clara",
        "\"That is what I thought!\" Clara's eyes are wide. \"We are not the end of her mission, "
        "we are one stop on a tour. The Consortium plants agents in multiple households, and Elena's "
        "job is to move from one to the next, gathering intelligence and undermining noble families.\" "
        "She grips your arm. \"My lady, if we stop her here, we might be saving the Montfort family "
        "too. And whoever comes after them.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_letters_duke", "Maid Clara",
        "\"Yes, right away. The Duke needs to see this.\" Clara folds the scrap carefully and "
        "tucks it into her pocket. \"I will bring it to Graves, who will present it to the Duke "
        "during their morning briefing. That is the proper channel.\" She pauses. \"Unless you "
        "want to present it yourself, my lady. That would carry more weight, coming from the "
        "Duke's own daughter.\"",
        {
            {"I will present it myself.", "clara_root", nullptr, nullptr},
            {"You take it through Graves.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_post_expulsion", "Maid Clara",
        "Clara is practically glowing, though she tries to be appropriately solemn. \"The staff "
        "are talking about nothing else, my lady. The older servants are relieved, openly so. "
        "Marcel actually smiled this morning. Graves has been walking with an extra inch of height. "
        "Roderick personally escorted her to the gate and, I am told, saluted the Duke on his "
        "return.\"",
        {
            {"And the younger staff?", "clara_exp_young", nullptr, nullptr},
            {"What about outside the estate?", "clara_exp_outside", nullptr, nullptr},
            {"Are you alright, Clara?", "clara_exp_self", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_exp_young", "Maid Clara",
        "\"The scullery maids are upset. Two of them cried at breakfast. The stable boy, Thomas, "
        "the one Elena was closest to, he has been sullen and silent.\" Clara's voice drops. "
        "\"I am watching him closely. Graves intercepted a letter he tried to send. The boy might "
        "still be loyal to Elena.\" She frowns. \"But the majority will come around. I have been "
        "holding the evening gatherings in the servants' hall, and attendance is growing. "
        "People want to feel they belong somewhere, and the household can provide that better "
        "than a departed guest.\"",
        {
            {"Keep up the good work.", "clara_root", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_exp_outside", "Maid Clara",
        "\"The village is buzzing. Some think the Duke was harsh. Others, the ones who have dealt "
        "with outsiders before, they nod and say 'about time.'\" She chews her lip. \"The market "
        "women are the biggest problem. They loved Elena. She bought ribbons and chatted with them "
        "every market day.\" Clara sighs. \"But the merchant class follows the noble class "
        "eventually. When the formal statement from the Duke circulates with the reasons, "
        "sentiment will shift.\"",
        {
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_exp_self", "Maid Clara",
        "Clara blinks, surprised by the question. \"Me? I am...\" She takes a breath. \"Relieved, "
        "mostly. But also a little sad? Is that strange?\" She picks at her apron. \"Elena was "
        "good company when she was not being a spy. She was funny, and kind to people who did "
        "not have to be kind to. The scullery maids' tears are not fake, my lady. She made them "
        "feel valued.\" She squares her shoulders. \"But feeling valued by a liar is a dangerous "
        "thing. Better honest indifference than false kindness.\"",
        {
            {"That is wise, Clara.", "clara_root", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_post_death", "Maid Clara",
        "Clara is pale, her usual energy replaced by a trembling stillness. She has been crying, "
        "and she does not try to hide it. \"My lady.\" Her voice shakes. \"I heard the news from "
        "Graves this morning. I... I cleaned her room just yesterday. Her things were still there. "
        "Her comb, her night clothes, the book she was reading.\" She covers her mouth. \"I did "
        "not like what she was doing, but she was a person, my lady. She was real.\"",
        {
            {"I know, Clara. I am sorry.", "clara_death_comfort", nullptr, nullptr},
            {"I need you to hold together. The staff need you.", "clara_death_duty", nullptr, nullptr},
            {"Has anyone said anything suspicious?", "clara_death_suspicious", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_death_comfort", "Maid Clara",
        "Clara nods, wiping her eyes. \"I know. I know I should not grieve someone who was "
        "working against us. But my heart does not listen to my head.\" She takes a shaky breath. "
        "\"The scullery maids are inconsolable. Thomas, the stable boy, he has not spoken all day. "
        "Even Marcel seemed shaken, and nothing shakes Marcel.\" She looks at you with red-rimmed "
        "eyes. \"My lady, whatever happened, whatever caused this, please tell me it stops here. "
        "No more. I cannot lose anyone else.\"",
        {
            {"It stops here. I promise.", "clara_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "maid_clara") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_death_duty", "Maid Clara",
        "Clara swallows hard and nods. \"You are right. You are right.\" She wipes her face "
        "roughly with her apron and stands straighter. \"The staff need someone steady. Graves "
        "is handling the Duke and Roderick is handling security. I will handle the servants.\" "
        "She takes a breath. \"Tea in the hall. Warm food. Calm voices. That is what gets people "
        "through terrible days.\" Something steadies in her eyes. \"I will not fall apart, my lady. "
        "Not while people need me.\"",
        {
            {"Thank you, Clara.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_death_suspicious", "Maid Clara",
        "Clara collects herself with visible effort, the spy-catcher in her reasserting itself. "
        "\"Yes, actually. Thomas, the stable boy, was awake at an unusual hour last night. He "
        "claims he was checking on a sick horse, but the stable master says no horse was ill.\" "
        "She frowns. \"And one of the laundry girls found a damp cloak in the washing pile this "
        "morning that she cannot account for. It does not belong to any servant she recognizes.\" "
        "She hugs herself. \"I do not want to think about what these things mean. But you asked, "
        "and I tell you what I know. That is our arrangement.\"",
        {
            {"Keep that information between us.", "clara_root", nullptr, nullptr},
            {"Back to other matters.", "clara_root", nullptr, nullptr},
        }, false);

    addNode(state, "clara_farewell", "Maid Clara",
        "Clara picks up her duster and performs a playful curtsy. \"My lady. You know where to "
        "find me. Which is everywhere, at all times, because that is what maids do.\" She winks. "
        "\"My ears are always open.\"",
        {}, true);
}

}


void registerMaidClara(GameState &state)
{
    NPC n;
    n.id = "maid_clara";
    n.name = "Maid Clara";
    n.title = "Maid";
    n.description = "A chatty, sharp-eyed maid who knows every rumor in the estate. Her gossip\n"
                    "is surprisingly accurate.";
    n.current_room = "hallway";
    n.affection = 40;
    n.suspicion = 0;
    n.disposition = Disposition::Loyal;
    n.dialogue_root = "clara_root";
    n.traits = {Trait::Gossip, Trait::Gullible, Trait::LightSleeper};
    n.hireable = true;
    n.hire_cost = 10;
    n.schedule = {
        {6, "kitchen"},
        {7, "hallway"},
        {8, "dining_room"},
        {9, "bedroom"},
        {10, "guest_room"},
        {11, "hallway"},
        {12, "dining_room"},
        {13, "servants_quarters"},
        {14, "hallway"},
        {16, "library"},
        {17, "hallway"},
        {19, "dining_room"},
        {20, "servants_quarters"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildClaraDialogue(state);
}
