#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include <algorithm>

void registerElena(GameState &state)
{
        NPC n;
        n.id = "elena";
        n.name = "Elena";
        n.title = "The Heroine";
        n.description = "A charming commoner who has caught the nobility's eye. She radiates\n"
                        "warmth and grace. Your rival.";
        n.current_room = "guest_room";
        n.affection = 30;
        n.suspicion = 0;
        n.disposition = Disposition::Neutral;
        n.is_heroine = true;
        n.dialogue_root = "elena_root";
        n.traits = {Trait::Perceptive, Trait::LightSleeper};
        n.schedule = {
            {7, "garden"},
            {8, "dining_room"},
            {9, "library"},
            {11, "courtyard"},
            {12, "dining_room"},
            {13, "guest_room"},
            {14, "garden"},
            {16, "courtyard"},
            {17, "library"},
            {19, "dining_room"},
            {21, "guest_room"},
        };
        n.associates = {"duke_aldric", "cedric", "rosalind", "butler_graves", "maid_clara"};
        state.npcs[n.id] = n;
        if (state.rooms.count(n.current_room))
                state.rooms[n.current_room].npc_ids.push_back(n.id);

        addNode(state, "elena_root", "Elena",
                "\"Oh! Lady Seraphina, what a pleasant surprise. *She curtsies gracefully.*\n"
                "To what do I owe this visit?\"",
                {{"\"I wanted to welcome you to the estate properly.\"", "elena_welcome", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.met_elena = true;
                          gs.npcs["elena"].affection += 5;
                  }},
                 {"\"I've been hearing a lot about you.\" (Probe)", "elena_probe", nullptr,
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"Stay away from my family.\" (Threaten)", "elena_threaten", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.met_elena = true;
                          gs.npcs["elena"].suspicion += 15;
                  }},
                 {"\"I'd love for you to join me for tea sometime.\"", "elena_tea_invite",
                  [](const GameState &gs)
                  {
                          return gs.quest.invited_elena && gs.quest.wrote_invitation && !gs.quest.elena_arrived_dinner;
                  },
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"What are your plans while you're here?\"", "elena_plans", nullptr,
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"Tell me about yourself.\"", "elena_backstory", nullptr,
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"I know about your letters, Elena.\"", "elena_letters_confront",
                  [](const GameState &gs)
                  {
                          return gs.quest.elena_letters_found && !gs.quest.elena_expelled;
                  },
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"The servants have been talking about you.\"", "elena_rumors_confront",
                  [](const GameState &gs)
                  {
                          return gs.quest.rumors_spread && !gs.quest.elena_expelled;
                  },
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"I hear you've been busy making friends.\" (Suspicious)", "elena_influence",
                  [](const GameState &gs)
                  {
                          return gs.quest.met_elena && gs.heroine_popularity >= 25;
                  },
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }},
                 {"\"We need to talk about what you've been doing.\" (Retaliation)", "elena_retaliation_confront",
                  [](const GameState &gs)
                  {
                          return gs.quest.elena_retaliating;
                  },
                  [](GameState &gs)
                  { gs.quest.met_elena = true; }}});

        addNode(state, "elena_welcome", "Elena",
                "\"How kind! *She smiles warmly.* I must say, this estate is magnificent.\n"
                "Your father has been very generous. I hope we can be friends, my lady.\n"
                "The gardens here remind me of a painting I once saw in the capital,\n"
                "all those roses in full bloom.\"",
                {{"\"Perhaps we can. The gardens are my mother's legacy.\"", "elena_welcome_gardens", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"Friends is a strong word. But civility costs nothing.\"", "elena_welcome_civil", nullptr,
                  nullptr},
                 {"\"Don't get comfortable. Guests don't stay forever.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}});

        addNode(state, "elena_welcome_gardens", "Elena",
                "\"Your mother? *Her expression softens with genuine tenderness.* I didn't\n"
                "know. The estate must hold many memories for you. *She gazes toward the\n"
                "window.* My own mother tended a small patch of wildflowers behind our\n"
                "cottage. Nothing so grand, but they were beautiful in their own way.\"",
                {{"\"She would have liked you, I think.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.heroine_popularity += 2;
                  }},
                 {"\"Don't compare your cottage garden to this estate.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 5;
                          gs.npcs["elena"].affection -= 5;
                  }}},
                true);

        addNode(state, "elena_welcome_civil", "Elena",
                "\"*She tilts her head, studying you.* Civility. Yes, I suppose that's a\n"
                "start. *A faint smile.* You're more cautious than they told me you'd be.\n"
                "The servants said the duke's daughter was fierce and proud. But I think\n"
                "there's more to you than that.\"",
                {{"\"Who told you about me?\"", "elena_welcome_who_told", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }},
                 {"\"You shouldn't believe everything servants say.\"", "", nullptr, nullptr}});

        addNode(state, "elena_welcome_who_told", "Elena",
                "\"Oh, everyone, really. *She counts on her fingers.* The cook spoke of your\n"
                "refined palate. Maid Clara mentioned how you command a room. Even your\n"
                "brother mentioned, somewhat reluctantly, that you're the sharpest mind\n"
                "in the family. *She meets your eyes.* Should I not have asked about you?\"",
                {{"\"You've been thorough. I'm impressed, and concerned.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"My family speaks too freely with strangers.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }}},
                true);

        addNode(state, "elena_probe", "Elena",
                "\"Oh? *She laughs softly.* The nobles have been very kind. I'm just a\n"
                "commoner trying to find my place. Surely someone of your stature has\n"
                "nothing to worry about from someone like me?\"",
                {{"\"Of course not. I was merely curious.\"", "elena_probe_curious", nullptr, nullptr},
                 {"\"Don't play innocent with me.\"", "elena_confrontation", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"The Prince sent you flowers. That's not 'just' anything.\"", "elena_probe_prince", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}});

        addNode(state, "elena_probe_curious", "Elena",
                "\"*She relaxes slightly.* Curiosity is natural, my lady. You're the duke's\n"
                "daughter, after all. It must be strange, having an outsider suddenly\n"
                "appear in your home. *She fidgets with her sleeve.* If you'd like, I\n"
                "could tell you about myself directly, rather than relying on rumors.\"",
                {{"\"Go ahead then. Tell me who you really are.\"", "elena_backstory", nullptr, nullptr},
                 {"\"Rumors are often more honest than the people they describe.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_probe_prince", "Elena",
                "\"The Prince? *A faint blush crosses her cheeks.* He's been very kind.\n"
                "We met at a charity garden event in the capital. He mentioned my singing\n"
                "reminded him of birdsong. *She pauses.* I assure you, my lady, I did not\n"
                "seek his attention. It simply... happened.\"",
                {{"\"Things don't 'simply happen' in court politics.\"", "elena_probe_prince_politics", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"The Prince has a weakness for pretty faces. It will pass.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection -= 5;
                          gs.heroine_popularity += 3;
                  }}});

        addNode(state, "elena_probe_prince_politics", "Elena",
                "\"*Her expression becomes guarded.* Court politics? My lady, I am a\n"
                "seamstress's daughter. I know nothing of political maneuvering. *She\n"
                "smooths her skirt.* Though I am beginning to learn that every kindness\n"
                "in noble society comes with a price. Even yours, perhaps.\"",
                {{"\"At least you're learning quickly.\"", "", nullptr, nullptr},
                 {"\"My kindness comes free. My patience does not.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_threaten", "Elena",
                "\"*Her smile fades for just a moment before returning, brighter than before.*\n"
                "My lady, I have no designs on your family. I'm merely a guest. But I\n"
                "appreciate your... directness. *She straightens her posture.* In my\n"
                "village, we had a saying: the rose that fears the weed reveals which\n"
                "one truly has shallow roots.\"",
                {{"\"Did you just compare me to a weed?\"", "elena_threaten_weed", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"Remember your place, commoner.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                          gs.heroine_popularity += 3;
                  }}});

        addNode(state, "elena_threaten_weed", "Elena",
                "\"*She laughs, a clear, musical sound.* I compared myself to a weed,\n"
                "actually. Weeds grow anywhere, survive anything. Roses need careful\n"
                "tending. *She curtsies.* Take that as you will, my lady.\"",
                {{"*Clench your fists as she walks away*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 5; }}},
                true);

        addNode(state, "elena_confrontation", "Elena",
                "\"*She meets your gaze steadily, all pretense of warmth fading.* I assure\n"
                "you, Lady Seraphina, I am exactly who I appear to be. A girl who was\n"
                "given an opportunity and seized it. *She steps closer.* Perhaps it is\n"
                "your own heart you should examine. Why does my presence frighten you so?\"",
                {{"\"I'm not frightened of you.\"", "elena_confrontation_denial", nullptr, nullptr},
                 {"\"Because I can see what others can't.\"", "elena_confrontation_see", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"*Leave in silence*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 5; }}});

        addNode(state, "elena_confrontation_denial", "Elena",
                "\"*A knowing smile.* Of course not. A duke's daughter fears nothing.\n"
                "*She smooths a crease in her dress.* Then perhaps we can simply coexist?\n"
                "This estate is large enough for both of us.\"",
                {{"\"For now. But estates have limits.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"Perhaps. We shall see.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "elena_confrontation_see", "Elena",
                "\"*Something flickers behind her eyes, fear or anger, gone before you\n"
                "can name it.* And what is it you see, my lady? *Her voice drops to\n"
                "barely a whisper.* Be careful with accusations you cannot prove. I\n"
                "learned that lesson the hard way in the capital.\"",
                {{"\"What happened in the capital, Elena?\"", "elena_capital_secret", nullptr, nullptr},
                 {"\"Is that a threat?\"", "elena_capital_threat", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }}});

        addNode(state, "elena_capital_secret", "Elena",
                "\"*She looks away, and you catch a glimpse of something genuine, pain.*\n"
                "There was a merchant's wife who accused me of stealing. It wasn't true,\n"
                "but it didn't matter. The accusation alone was enough to ruin my mother's\n"
                "business. We nearly starved that winter. *She turns back, eyes hard.*\n"
                "Words have power, my lady. More than swords, sometimes.\"",
                {{"\"I'm sorry that happened to you.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 8; }},
                 {"\"Then you know what happens when someone oversteps.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_capital_threat", "Elena",
                "\"*She shakes her head slowly.* Not a threat. A warning, from someone\n"
                "who has been on the receiving end of false accusations. *She curtsies\n"
                "stiffly.* Good day, my lady.\"",
                {{"*Watch her leave, troubled*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 3; }}},
                true);

        addNode(state, "elena_tea_invite", "Elena",
                "\"Tea with you? *Her eyes light up, and for a moment she seems genuinely\n"
                "delighted.* Oh, that would be wonderful, Lady Seraphina! I've been hoping\n"
                "we could spend some time together. *She clasps her hands.* Shall we meet\n"
                "in the dining room tomorrow afternoon? I do so love jasmine tea.\"",
                {{"\"Tomorrow afternoon. I'll have the kitchen prepare something special.\"",
                  "elena_tea_accept", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.elena_arrived_dinner = true;
                  }},
                 {"\"I was thinking something more intimate. Just the two of us.\"",
                  "elena_tea_private", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.elena_arrived_dinner = true;
                          gs.npcs["elena"].suspicion += 3;
                  }},
                 {"\"Actually, I've changed my mind.\"", "", nullptr, nullptr}});

        addNode(state, "elena_tea_accept", "Elena",
                "\"*She beams.* How lovely! I'll wear my best dress. Oh, I know this\n"
                "might sound odd, but could we have some of those little cucumber\n"
                "sandwiches? The chef made them once and I've been dreaming about them\n"
                "since. *She laughs.* You can take the girl out of the village...\"",
                {{"*Laugh* \"I'll see what I can arrange.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"I'll manage the menu. You just need to show up.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "elena_tea_private", "Elena",
                "\"*She studies you for a beat too long.* Just the two of us? *A careful\n"
                "smile.* That sounds... intimate. Are you sure, my lady? People might\n"
                "talk. *She tilts her head.* But then, a duke's daughter doesn't worry\n"
                "about idle gossip, does she?\"",
                {{"\"Let them talk. Tomorrow, then.\"", "", nullptr, nullptr},
                 {"\"You let me worry about what people say.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }}},
                true);

        addNode(state, "elena_plans", "Elena",
                "\"*She clasps her hands together thoughtfully.*\n"
                "Well, the Duke has been kind enough to let me stay while I study the\n"
                "noble arts. I hope to learn etiquette, literature, perhaps some music.\n"
                "Eventually I dream of earning a place at the Royal Academy.\"",
                {{"\"The Royal Academy? That's quite ambitious for a commoner.\"",
                  "elena_plans_ambitious", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"That sounds lovely. I wish you the best.\"",
                  "elena_plans_kind", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"My father is too generous with his charity.\"",
                  "elena_plans_cold", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                  }},
                 {"\"What would you study at the Academy?\"",
                  "elena_plans_study", nullptr, nullptr}});

        addNode(state, "elena_plans_ambitious", "Elena",
                "\"*A flicker of something crosses her face, determination perhaps.*\n"
                "Ambitious? Perhaps. But is that not what this world rewards? Surely\n"
                "you of all people understand that, my lady. *She holds your gaze.*\n"
                "After all, ambition runs in the Aldric blood.\"",
                {{"\"Touche. We shall see how far ambition takes you.\"", "", nullptr, nullptr},
                 {"\"Ambition without breeding is just desperation.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 5;
                          gs.npcs["elena"].affection -= 8;
                          gs.heroine_popularity += 3;
                  }}},
                true);

        addNode(state, "elena_plans_kind", "Elena",
                "\"*She beams, genuine warmth in her expression.*\n"
                "Thank you, Lady Seraphina! That truly means a lot coming from you.\n"
                "Perhaps you could recommend some books from the library? I've been\n"
                "working through the histories, but I'd love guidance from someone\n"
                "who grew up with this knowledge.\"",
                {{"\"Of course. I'll leave a list for you.\"", "elena_plans_booklist", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"You'll have to find your own way. That's part of learning.\"", "", nullptr, nullptr}});

        addNode(state, "elena_plans_booklist", "Elena",
                "\"*She claps her hands with delight.* Oh, thank you! I've been reading\n"
                "the Aldric family chronicle, actually. Your great-grandmother, Duchess\n"
                "Aveline, she's fascinating. Did you know she once challenged a baron\n"
                "to a duel? *She laughs.* I see where you get your fire from.\"",
                {{"\"You've read the family chronicle? That's... thorough.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"Great-grandmother Aveline was extraordinary. The best of us.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }}},
                true);

        addNode(state, "elena_plans_cold", "Elena",
                "\"*Her smile wavers for only a heartbeat.*\n"
                "The Duke sees potential in everyone, my lady. Even those who might not\n"
                "see it in themselves. *She curtsies stiffly.* I hope one day you'll see\n"
                "me as more than just your father's charity case.\"",
                {{"*Watch her leave*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 3; }},
                 {"\"Wait, Elena. That was uncalled for.\"", "elena_plans_apologize", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 5;
                          gs.npcs["elena"].suspicion -= 3;
                  }}});

        addNode(state, "elena_plans_apologize", "Elena",
                "\"*She turns back, surprised.* You're apologizing? *She studies your\n"
                "face carefully.* Thank you, my lady. That takes more courage than most\n"
                "realize. *A small, genuine smile.* Perhaps there's hope for us yet.\"",
                {{"\"Don't read too much into it.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "elena_plans_study", "Elena",
                "\"*Her eyes light up.* Literature, mostly. I love stories, the older\n"
                "the better. There's a collection of Ashworth ballads in your library\n"
                "that I'd give anything to study properly. And music, of course. I\n"
                "sing a little. *She blushes.* Well, more than a little.\"",
                {{"\"You sing? I'd like to hear that sometime.\"", "elena_plans_sing", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"The Ashworth ballads? Those are quite rare.\"", "elena_plans_ashworth", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }}});

        addNode(state, "elena_plans_sing", "Elena",
                "\"*She flushes a deeper shade of rose.* You'd want to hear me sing?\n"
                "Most nobles think it's a common pastime, beneath their attention.\n"
                "*She hums a few bars of a melody, hauntingly beautiful.* That's a\n"
                "lullaby my mother used to sing. It's about a girl who outsmarted a\n"
                "wolf by singing it to sleep.\"",
                {{"\"That was beautiful. Your mother taught you well.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 8; }},
                 {"\"A girl outsmarting a wolf. How fitting.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_plans_ashworth", "Elena",
                "\"Are they? *She seems startled.* I found them on a bottom shelf behind\n"
                "some old tax records. The binding was dusty, I don't think anyone had\n"
                "touched them in years. *She pauses.* I hope that's alright? I've been\n"
                "very careful with the pages.\"",
                {{"\"The library is open to guests. Just be careful with old texts.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }},
                 {"\"You seem to be very good at finding things others overlook.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_backstory", "Elena",
                "\"*She tucks a strand of hair behind her ear.*\n"
                "There isn't much to tell, really. I grew up in a small village to the\n"
                "south. My mother was a seamstress, my father a merchant. When he passed,\n"
                "we lost everything. I came to the capital seeking work and, well...\n"
                "the Duke found me and saw something worth nurturing, I suppose.\"",
                {{"\"I'm sorry about your father. That must have been difficult.\"",
                  "elena_backstory_sympathy", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 10; }},
                 {"\"A convenient story. How did a seamstress's daughter learn such graces?\"",
                  "elena_backstory_doubt", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"My father has a habit of collecting strays.\"",
                  "elena_backstory_cruel", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 15;
                          gs.npcs["elena"].affection -= 10;
                  }},
                 {"\"What was your village like?\"",
                  "elena_backstory_village", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }}});

        addNode(state, "elena_backstory_sympathy", "Elena",
                "\"*Her eyes glisten.* Thank you, my lady. You know, everyone warned me\n"
                "that the duke's daughter would be cold and cruel. But you're not like\n"
                "that at all. *She reaches out and squeezes your hand gently.*\n"
                "Perhaps we really could be friends.\"",
                {{"\"Perhaps we could.\" *Squeeze back*", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"*Pull your hand away* \"Don't get too comfortable.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"What happened after he died? How did you survive?\"", "elena_backstory_survival", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }}});

        addNode(state, "elena_backstory_survival", "Elena",
                "\"*She withdraws her hand, lost in memory.* We sold everything. The shop,\n"
                "the house, even mother's loom. I took work as a laundress, then a\n"
                "serving girl at a tavern. *She touches the fabric of her dress.* I\n"
                "never imagined wearing silk. Some nights I still wake up expecting\n"
                "rough wool and cold floors.\"",
                {{"\"That kind of hardship builds character.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"And yet here you are, in silk, dining with a duke.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_backstory_doubt", "Elena",
                "\"*She straightens, a practiced composure settling over her features.*\n"
                "My mother taught me to sew, and sewing teaches patience. The Duke's\n"
                "tutors have been generous with their time. Is it so hard to believe\n"
                "that someone could learn, my lady? *She holds your gaze.* Or does\n"
                "nobility believe that grace is something you're born with?\"",
                {{"\"People don't change that quickly. I'll be watching.\"", "elena_backstory_watching", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"I suppose I underestimated you. Forgive me.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }}});

        addNode(state, "elena_backstory_watching", "Elena",
                "\"*A flash of something, anger perhaps, crosses her face before she\n"
                "composes herself.* Then watch, my lady. You'll find nothing but a\n"
                "girl trying to better herself. *She smooths her sleeve.* Though I\n"
                "wonder, who watches the watchers?\"",
                {{"\"Is that a warning?\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }},
                 {"\"Clever. I'll give you that.\"", "", nullptr, nullptr}},
                true);

        addNode(state, "elena_backstory_cruel", "Elena",
                "\"*Her composure cracks, and for a moment you see real hurt in her eyes.\n"
                "Then the mask returns, colder than before.*\n"
                "A stray. I see. Well, this stray has claws, my lady. Do remember that.\n"
                "*She turns on her heel and walks away.*\"",
                {{"*Feel a chill run down your spine*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 5; }}},
                true);

        addNode(state, "elena_backstory_village", "Elena",
                "\"*A wistful smile crosses her face.* Small. Quiet. Everyone knew\n"
                "everyone. My father's shop was the center of the village, people\n"
                "came from miles around for his fabrics. *She pauses.* There was\n"
                "an old oak tree by the river where I used to read for hours.\n"
                "I wonder if it's still there.\"",
                {{"\"It sounds peaceful. Do you miss it?\"", "elena_backstory_miss", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"A quaint upbringing. How far you've come.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }}});

        addNode(state, "elena_backstory_miss", "Elena",
                "\"*She nods slowly.* Every day. The simplicity of it. Here, every smile\n"
                "hides something, every compliment carries a price. *She looks at you\n"
                "with startling openness.* Do you ever tire of it? The games, the\n"
                "posturing? *She catches herself.* Forgive me. That was too familiar.\"",
                {{"\"No, it's a fair question. Sometimes I do.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 8;
                          gs.npcs["elena"].suspicion -= 3;
                  }},
                 {"\"Games are all I know, Elena. And I play to win.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 8; }}},
                true);

        addNode(state, "elena_letters_confront", "Elena",
                "\"*Her hand freezes mid-reach for her teacup. The color drains from\n"
                "her face.* Letters? I... *She recovers, but not quickly enough.*\n"
                "I don't know what you mean, my lady.\"",
                {{"\"Lord Valmonte. Lord Ashworth. Ring any bells?\"", "elena_letters_names", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 15;
                          gs.heroine_popularity -= 3;
                  }},
                 {"\"I'm giving you one chance to explain yourself.\"", "elena_letters_explain", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"I haven't told my father. Yet.\"", "elena_letters_leverage", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 20;
                  }}});

        addNode(state, "elena_letters_names", "Elena",
                "\"*She closes her eyes for a long moment.* I see. *When she opens them,\n"
                "there's a frightening calm.* Those letters are not what you think. Lord\n"
                "Valmonte was my father's business partner. He owed our family money. I\n"
                "was trying to collect a debt, nothing more. *Her voice trembles slightly.*\n"
                "And Lord Ashworth is a patron of the Royal Academy. I was applying for\n"
                "a scholarship.\"",
                {{"\"A convenient explanation. I don't believe you.\"", "elena_letters_disbelief", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"If that's true, you have nothing to worry about.\"", "elena_letters_mercy", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"Then you won't mind if I have them verified?\"", "elena_letters_verify", nullptr, nullptr}});

        addNode(state, "elena_letters_disbelief", "Elena",
                "\"*Her jaw tightens.* Believe what you wish, my lady. But consider this:\n"
                "if I were truly conspiring against your family, would I keep the evidence\n"
                "under a loose floorboard? *She stands.* Perhaps someone wants you to\n"
                "find those letters. Have you considered that?\"",
                {{"\"What do you mean? Who would want that?\"", "elena_letters_conspiracy", nullptr, nullptr},
                 {"\"Nice try. But the evidence speaks for itself.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity -= 5; }}});

        addNode(state, "elena_letters_conspiracy", "Elena",
                "\"*She lowers her voice.* I've noticed things in this estate. Doors that\n"
                "should be locked standing open. Items moved in my room when I was out.\n"
                "*She meets your eyes.* Someone is watching me, and I don't think it's\n"
                "you. Not entirely. *She swallows.* There's a third player in this\n"
                "game, my lady. And neither of us knows the rules.\"",
                {{"\"You're trying to deflect. It won't work.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"That's... unsettling. Tell me more.\"", "elena_letters_third_player", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }}});

        addNode(state, "elena_letters_third_player", "Elena",
                "\"*She glances at the door, then speaks quickly.* Last week, I found\n"
                "a note slipped under my door. No signature, just a wax seal, a flower\n"
                "I didn't recognize. It said 'The Iris watches. Choose your patron wisely.'\n"
                "*She wraps her arms around herself.* I thought it was a prank at first.\n"
                "Now I'm not so sure.\"",
                {{"\"The Iris Consortium... I've heard whispers.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.npcs["elena"].suspicion -= 5;
                  }},
                 {"\"You expect me to believe someone is threatening you?\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_letters_explain", "Elena",
                "\"*She takes a slow breath.* Explain? My lady, I came here with nothing.\n"
                "The letters you found, they are from people who knew my father. I was\n"
                "trying to rebuild the connections he lost. *Her voice breaks slightly.*\n"
                "Is that so terrible? To try to restore what was taken from your family?\"",
                {{"\"I understand loss, Elena. But secrets breed suspicion.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 5;
                          gs.npcs["elena"].suspicion -= 3;
                  }},
                 {"\"Save your tears for someone who believes them.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection -= 10;
                          gs.heroine_popularity += 3;
                  }}},
                true);

        addNode(state, "elena_letters_leverage", "Elena",
                "\"*She goes very still. When she speaks, her voice is barely a whisper.*\n"
                "What do you want? *She sits down slowly, her hands trembling.* Money?\n"
                "I have none. My silence? You already have it. *She looks up at you\n"
                "with eyes that are no longer soft.* Name your price, Lady Seraphina.\n"
                "You clearly came here with one in mind.\"",
                {{"\"Stay away from my brother and sister.\"", "elena_letters_demand_family", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity -= 5; }},
                 {"\"I want you to leave this estate willingly.\"", "elena_letters_demand_leave", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity -= 8; }},
                 {"\"I want the truth. All of it.\"", "elena_letters_demand_truth", nullptr, nullptr}});

        addNode(state, "elena_letters_demand_family", "Elena",
                "\"*She nods stiffly.* Your brother and sister. *She swallows.* Rosalind\n"
                "has been so kind to me. But, very well. If that's what it takes.\n"
                "*She stands, her bearing suddenly regal despite her common birth.*\n"
                "You have my word, Lady Seraphina. For whatever that's worth to you.\"",
                {{"\"Your word. We'll see how long that lasts.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection -= 10; }}},
                true);

        addNode(state, "elena_letters_demand_leave", "Elena",
                "\"*Her eyes flash with something fierce.* Leave? And go where? Back to\n"
                "poverty? Back to starving? *She clutches the edge of the table.*\n"
                "You noble-born have no idea what you're asking. This is the only\n"
                "chance I have. *Voice cracking.* The only one.\"",
                {{"\"That's not my concern.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection -= 15;
                          gs.heroine_popularity += 5;
                  }},
                 {"\"Then give me a reason to let you stay.\"", "elena_letters_demand_truth", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }}});

        addNode(state, "elena_letters_demand_truth", "Elena",
                "\"*She's quiet for a very long time.* The truth. *She laughs bitterly.*\n"
                "Fine. My father wasn't just a merchant. He was a minor noble, a fourth\n"
                "son from a disgraced branch of House Ashworth. When the scandal broke,\n"
                "we were stripped of everything. My 'commoner' story is real, but it\n"
                "didn't start that way. *She looks at you defiantly.* I have noble blood,\n"
                "Seraphina. Diluted, disgraced, but real.\"",
                {{"\"An Ashworth. That changes everything.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection -= 5;
                          gs.heroine_popularity += 5;
                  }},
                 {"\"Thank you for being honest. I won't use this against you. Yet.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.npcs["elena"].suspicion -= 5;
                  }}},
                true);

        addNode(state, "elena_letters_mercy", "Elena",
                "\"*She blinks, surprised.* You, you believe me? *She pulls out a\n"
                "handkerchief and dabs her eyes.* Thank you, my lady. I know we are\n"
                "not friends. But perhaps we don't have to be enemies, either.\"",
                {{"\"We're not enemies. But trust must be earned.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.npcs["elena"].suspicion -= 5;
                  }},
                 {"\"Don't thank me yet. I'm keeping those letters.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_letters_verify", "Elena",
                "\"*She pales.* Verified? *A long pause.* If you must. But please, my\n"
                "lady, be discreet. If word gets out that I've been writing to nobles,\n"
                "the gossip alone could destroy me. *She wrings her hands.* That would\n"
                "please you, wouldn't it?\"",
                {{"\"It would. But I'd rather the truth first.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }},
                 {"\"I'll be discreet. Unlike some people.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_rumors_confront", "Elena",
                "\"*Her expression hardens, the warmth draining from her eyes.* Yes, I've\n"
                "heard the rumors. Fascinating tales. Apparently I'm everything from a\n"
                "spy to a witch. *She crosses her arms.* I don't suppose you'd know\n"
                "anything about where those stories started?\"",
                {{"\"Rumors have a way of starting themselves.\"", "elena_rumors_deflect", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"I won't insult you by denying it.\"", "elena_rumors_honest", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 15;
                  }},
                 {"\"Those rumors existed long before I said a word.\"", "elena_rumors_deny", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}});

        addNode(state, "elena_rumors_deflect", "Elena",
                "\"*She laughs, but there's no warmth in it.* How philosophical. Did they\n"
                "also 'start themselves' when Graves whispered them to the stable boy?\n"
                "*She steps closer.* I'm not blind, my lady. And I'm not helpless.\n"
                "The Duke trusts me. The Prince trusts me. Do you really want to test\n"
                "whose word carries more weight?\"",
                {{"\"Is that a threat?\"", "elena_rumors_threat_response", nullptr, nullptr},
                 {"\"You're right, this was foolish. I'll call off the rumors.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 5;
                          gs.heroine_popularity += 5;
                  }}});

        addNode(state, "elena_rumors_threat_response", "Elena",
                "\"*She shakes her head slowly.* No. A promise. I grew up in a village\n"
                "where words could ruin a family overnight. I survived that. *Her eyes\n"
                "glitter.* I'll survive this too. And when the truth comes out, my\n"
                "lady, whose reputation do you think will suffer more?\"",
                {{"*Say nothing, but feel the weight of her words*", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 5; }}},
                true);

        addNode(state, "elena_rumors_honest", "Elena",
                "\"*She stares at you, genuinely taken aback.* You admit it? *She\n"
                "uncrosses her arms.* I expected denial. Deflection. Not honesty.\n"
                "*She's quiet for a moment.* Why, Seraphina? What have I done to\n"
                "you that warrants this kind of cruelty?\"",
                {{"\"You exist. In my world, that's enough.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection -= 10;
                          gs.heroine_popularity += 5;
                  }},
                 {"\"I was afraid. Of losing everything to you.\"", "elena_rumors_vulnerable", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 10; }}});

        addNode(state, "elena_rumors_vulnerable", "Elena",
                "\"*Her expression softens, and you see something unexpected: understanding.*\n"
                "You were afraid. *She sits down.* Do you think I'm not? Every day in\n"
                "this place, I'm terrified someone will realize I don't belong. That\n"
                "this dress is borrowed, and so is this life. *She meets your eyes.*\n"
                "We're not so different, you and I. Both of us fighting not to fall.\"",
                {{"\"We are nothing alike.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection -= 5; }},
                 {"\"Maybe you're right. Maybe we're both just surviving.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 15;
                          gs.npcs["elena"].suspicion -= 10;
                  }}},
                true);

        addNode(state, "elena_rumors_deny", "Elena",
                "\"*She holds your gaze, searching for the lie.* Before you said a word.\n"
                "I see. *She smooths her dress.* Then perhaps I have more enemies than\n"
                "I realized. *Her voice drops.* Or perhaps you're simply better at this\n"
                "game than I gave you credit for.\"",
                {{"\"I'll take that as a compliment.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"Be careful who you accuse, Elena.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }}},
                true);

        addNode(state, "elena_influence", "Elena",
                "\"*She sets down the book she was reading.* Making friends? *A measured\n"
                "smile.* I've been making conversation, my lady. Surely that's not a\n"
                "crime. The servants are lovely, your brother is charming, and your\n"
                "sister is an absolute treasure.\"",
                {{"\"Charming my family is not 'making conversation.'\"", "elena_influence_family", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"The Prince's flowers suggest more than conversation.\"", "elena_influence_prince", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 8; }},
                 {"\"You're playing everyone here and you know it.\"", "elena_influence_accusation", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                  }}});

        addNode(state, "elena_influence_family", "Elena",
                "\"*She stands, her posture stiffening.* Charming? I was being kind.\n"
                "Should I be cold instead? Ignore them? *She gestures broadly.* What\n"
                "would you have me do, Lady Seraphina? Sit in my room and stare at\n"
                "the walls until you decide whether I'm worthy of breathing your air?\"",
                {{"\"Don't be dramatic. Just, know your boundaries.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 3; }},
                 {"\"...You have a point. I overreacted.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 8;
                          gs.npcs["elena"].suspicion -= 5;
                  }}},
                true);

        addNode(state, "elena_influence_prince", "Elena",
                "\"*She touches her cheek, a gesture you can't tell is practiced or\n"
                "natural.* The Prince is generous to many people. I didn't ask for\n"
                "his attention. *She pauses.* But I won't pretend it doesn't matter.\n"
                "Royal favor can change a commoner's life forever. Surely you\n"
                "understand that kind of ambition.\"",
                {{"\"Royal favor can also paint a target on your back.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 5;
                          gs.heroine_popularity += 3;
                  }},
                 {"\"Just be careful. The Prince is fickle.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 3; }}},
                true);

        addNode(state, "elena_influence_accusation", "Elena",
                "\"*Her eyes narrow, and for a moment the mask slips completely. Beneath\n"
                "is someone sharp, calculating, dangerous.* Playing everyone? *Her voice\n"
                "drops.* My lady, if I were playing a game, you would have lost already.\n"
                "*She catches herself, the warmth returning like a mask donned.* Forgive\n"
                "me. That was unkind. I simply, I don't enjoy being accused.\"",
                {{"\"There she is. Behind the smile. I knew it.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                          gs.heroine_popularity += 5;
                  }},
                 {"\"Interesting. For a moment, you almost seemed honest.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_retaliation_confront", "Elena",
                "\"*She doesn't bother with a curtsy. Her expression is flat, controlled,\n"
                "dangerous.* Lady Seraphina. I was wondering when you'd come. *She gestures\n"
                "to a chair.* Sit. We should talk honestly, for once. No masks, no games.\n"
                "You've been scheming against me, and I've been defending myself. Where\n"
                "does it end?\"",
                {{"\"It ends when you leave this estate.\"", "elena_ret_demand_leave", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"You started retaliating first.\"", "elena_ret_blame", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"A truce, then. What are your terms?\"", "elena_ret_truce", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 5; }},
                 {"\"Honestly? I don't know anymore.\"", "elena_ret_honest", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 10; }}});

        addNode(state, "elena_ret_demand_leave", "Elena",
                "\"*She laughs, a cold sound.* Leave? Where the Duke protects me, the\n"
                "Prince favors me, and even your own brother takes my side? *She leans\n"
                "forward.* I have nowhere else to go, and you have no authority to\n"
                "remove me. Only your father can do that, and he won't. Not without\n"
                "proof of wrongdoing.\"",
                {{"\"Then I'll find proof.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                  }},
                 {"\"You underestimate me, Elena.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}},
                true);

        addNode(state, "elena_ret_blame", "Elena",
                "\"*She rises from her chair.* Retaliating? I defended myself. You spread\n"
                "rumors, turned servants against me, tried to embarrass me at every turn.\n"
                "*Her voice trembles with restrained fury.* What was I supposed to do?\n"
                "Smile and curtsy while you destroyed my reputation? *She takes a breath.*\n"
                "I did what any cornered animal does. I bit back.\"",
                {{"\"At least you admit you're dangerous.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }},
                 {"\"I suppose I pushed you to this. Fair enough.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 8;
                          gs.npcs["elena"].suspicion -= 5;
                  }}},
                true);

        addNode(state, "elena_ret_truce", "Elena",
                "\"*She blinks, clearly not expecting this.* A truce? *She studies you\n"
                "carefully.* My terms are simple. Stop the rumors. Stop turning people\n"
                "against me. Let me study in peace. *She pauses.* In return, I'll stop\n"
                "writing to the Prince about, well, certain incidents at this estate.\n"
                "The borrowed books. The misplaced belongings. The 'accidental' food\n"
                "poisoning.\"",
                {{"\"You've been writing to the Prince about me?!\"", "elena_ret_prince_letters", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 10; }},
                 {"\"Fine. Truce. But I'll be watching.\"", "elena_ret_truce_accept", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.quest.elena_retaliating = false;
                          gs.quest.elena_retaliation_count = 0;
                  }}});

        addNode(state, "elena_ret_prince_letters", "Elena",
                "\"*A thin smile.* Insurance, my lady. Every commoner needs some. *She\n"
                "taps the desk.* The letters haven't been sent yet. Accept the truce,\n"
                "and they never will be. Refuse, and the Prince will learn exactly how\n"
                "the Aldric family treats its guests.\"",
                {{"\"You're blackmailing a duke's daughter?\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 10;
                          gs.heroine_popularity += 5;
                  }},
                 {"\"Clever. I'll accept the truce, for now.\"", "elena_ret_truce_accept", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 5;
                          gs.quest.elena_retaliating = false;
                          gs.quest.elena_retaliation_count = 0;
                  }}},
                true);

        addNode(state, "elena_ret_truce_accept", "Elena",
                "\"*She extends her hand, the gesture strangely formal.* Then we have an\n"
                "agreement. *You shake hands, and her grip is firmer than expected.*\n"
                "I want you to know, I never wanted this war. *She looks tired,\n"
                "suddenly.* I just wanted to learn. To be something more than a\n"
                "seamstress's daughter. Is that so terrible?\"",
                {{"\"No. It's not terrible at all.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].affection += 10;
                          gs.heroine_popularity -= 5;
                  }},
                 {"\"Time will tell. Don't make me regret this.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["elena"].suspicion += 3;
                  }}},
                true);

        addNode(state, "elena_ret_honest", "Elena",
                "\"*Something in your voice stops her cold. She sits back down slowly.*\n"
                "You don't know? *She searches your face.* Neither do I. *She laughs,\n"
                "and this time it sounds genuine, exhausted.* Look at us. A duke's\n"
                "daughter and a commoner, both too stubborn to stop fighting and too\n"
                "tired to keep going. *She rests her head in her hands.* What a pair\n"
                "we make.\"",
                {{"\"I'm tired of this too, Elena.\"", "elena_ret_truce_accept", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].affection += 15; }},
                 {"\"Don't mistake honesty for weakness.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["elena"].suspicion += 5; }}});
}