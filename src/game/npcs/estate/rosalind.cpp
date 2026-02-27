#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include <algorithm>

void registerRosalind(GameState &state)
{
        NPC n;
        n.id = "rosalind";
        n.name = "Lady Rosalind";
        n.title = "Younger Sister";
        n.description = "Your naive, impressionable younger sister. She adores you... for now.";
        n.current_room = "siblings_room";
        n.affection = 80;
        n.suspicion = 0;
        n.disposition = Disposition::Loyal;
        n.dialogue_root = "rosalind_root";
        n.traits = {Trait::Gullible, Trait::DeepSleeper};
        n.schedule = {
            {0, "siblings_room"},
            {8, "master_bedroom"},
            {9, "garden"},
            {11, "dining_room"},
            {13, "library"},
            {14, "courtyard"},
            {16, "siblings_room"},
            {19, "dining_room"},
            {20, "siblings_room"},
        };
        n.associates = {"duke_aldric", "cedric", "butler_graves", "maid_clara", "elena"};
        state.npcs[n.id] = n;
        if (state.rooms.count(n.current_room))
                state.rooms[n.current_room].npc_ids.push_back(n.id);

        addNode(state, "rosalind_root", "Lady Rosalind",
                "\"Sister! *She jumps up and hugs you.* I missed you! Come sit with me!\"",
                {{"\"Rosalind, have you been spending time with Elena?\"", "rosalind_elena", nullptr, nullptr},
                 {"*Hug her back* \"I missed you too, little one.\"", "rosalind_hug", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 5; }},
                 {"\"What have you been up to today?\"", "rosalind_day", nullptr, nullptr},
                 {"\"Tell me about your drawings.\"", "rosalind_drawings", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Not now, Rosalind.\" *Push her away*", "rosalind_rejected", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 10; }},
                 {"\"I need to talk to you about something important.\"", "rosalind_serious",
                  [](const GameState &gs)
                  {
                          return gs.quest.elena_letters_found || gs.quest.elena_expelled || gs.quest.elena_dead;
                  },
                  nullptr}});

        addNode(state, "rosalind_hug", "Lady Rosalind",
                "\"*She squeezes tighter.* You give the best hugs, sister. *She pulls back\n"
                "and looks at you with big, earnest eyes.* Cedric says I'm too old for hugs\n"
                "now, but that's silly, isn't it? You're never too old for hugs. *She\n"
                "fidgets with a ribbon in her hair.* Do you want to see what I've been\n"
                "drawing?\"",
                {{"\"Show me your drawings, Rosalind.\"", "rosalind_drawings", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Cedric is wrong. You're perfect as you are.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 8; }},
                 {"\"Actually, I wanted to ask about Elena.\"", "rosalind_elena", nullptr, nullptr}});

        addNode(state, "rosalind_drawings", "Lady Rosalind",
                "\"*She excitedly grabs a sketchbook from her desk.* Look! I drew the\n"
                "garden, and here's Father's study, and this one, *she pauses, blushing,*\n"
                "this one is you, sister. Wearing that blue dress from the spring ball.\n"
                "*She holds it up proudly.* Elena said I have real talent. She said I\n"
                "should apply to the Royal Academy's art program when I'm older!\"",
                {{"\"These are wonderful, Rosalind. You're very talented.\"", "rosalind_drawings_praise", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 8; }},
                 {"\"The Royal Academy? That was Elena's idea?\"", "rosalind_drawings_elena", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 2; }},
                 {"\"You drew me? *Touch the page gently.*\"", "rosalind_drawings_touched", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 10; }}});

        addNode(state, "rosalind_drawings_praise", "Lady Rosalind",
                "\"*She beams so brightly the room seems warmer.* You really think so?\n"
                "Father says art is a fine hobby but not a worthy pursuit for a lady.\n"
                "*Her face falls slightly.* But Elena says that beauty created by human\n"
                "hands is the closest thing to magic we have. *She clutches the sketchbook.*\n"
                "I want to make magic, sister.\"",
                {{"\"Then make magic. I'll support you no matter what Father says.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 10; }},
                 {"\"Father has a point. Art alone won't sustain you.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 5; }}},
                true);

        addNode(state, "rosalind_drawings_elena", "Lady Rosalind",
                "\"*She nods enthusiastically.* Elena knows so much about art! She told me\n"
                "about painters in the capital who make portraits for the royal court. She\n"
                "said I could be one of them someday. *She pauses, looking worried.* You\n"
                "don't like her, do you, sister? I can tell.\"",
                {{"\"It's complicated, Rosalind. But I'm glad she encourages you.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Be careful about believing everything Elena tells you.\"", "rosalind_elena_doubt", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 3; }}});

        addNode(state, "rosalind_elena_doubt", "Lady Rosalind",
                "\"*She hugs her sketchbook protectively.* But she's always so nice to me.\n"
                "She remembers my birthday, she knows my favorite color, she braids my\n"
                "hair when Clara is too busy. *Her lip trembles.* Why does everyone keep\n"
                "being nice only to turn out to be bad? Am I just that easy to fool?\"",
                {{"\"You're not easy to fool. You just see the best in people.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 8; }},
                 {"\"Sometimes, yes. But that's not always a bad thing.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }}},
                true);

        addNode(state, "rosalind_drawings_touched", "Lady Rosalind",
                "\"*Her eyes fill with happy tears.* I worked on it for three weeks! I\n"
                "wanted to get the lace on the collar just right. *She traces the drawing\n"
                "with her finger.* You looked so beautiful that night, sister. Everyone\n"
                "was staring. Even the Prince noticed you before, well, before Elena\n"
                "arrived. *She bites her lip.* Was I not supposed to mention that?\"",
                {{"\"The Prince noticed me? Before Elena?\"", "rosalind_prince", nullptr, nullptr},
                 {"\"It doesn't matter, little one. The drawing is beautiful.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 5; }}});

        addNode(state, "rosalind_prince", "Lady Rosalind",
                "\"*She nods vigorously.* Oh yes! He asked Cedric who you were! Cedric\n"
                "told me, even though he made me promise not to tell anyone. *She covers\n"
                "her mouth.* Oh. I just told you. Well, you're not 'anyone,' you're my\n"
                "sister! *She giggles.* But then Elena sang that song and the Prince\n"
                "forgot about everyone else.\"",
                {{"\"Interesting. What song did she sing?\"", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 2; }},
                 {"\"Cedric talks too much. Don't repeat that.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 3; }}},
                true);

        addNode(state, "rosalind_day", "Lady Rosalind",
                "\"*She bounces on her seat.* Oh, so much! I practiced my embroidery this\n"
                "morning, the roses are finally looking like roses instead of blobs! Then\n"
                "I read in the library for a while. *She pauses.* And then Elena taught\n"
                "me a card game from her village. It's called 'Wolf and Sheep.' The wolf\n"
                "has to catch all the sheep, but the sheep can team up to trap the wolf!\"",
                {{"\"Who wins more often, the wolf or the sheep?\"", "rosalind_wolf", nullptr, nullptr},
                 {"\"That sounds fun. What else did Elena teach you?\"", "rosalind_elena_teaches", nullptr, nullptr},
                 {"\"You spend a lot of time with Elena.\"", "rosalind_elena_time", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 2; }}});

        addNode(state, "rosalind_wolf", "Lady Rosalind",
                "\"*She thinks carefully.* The wolf wins if the sheep don't work together.\n"
                "But if even two sheep cooperate, the wolf almost always loses. *She grins.*\n"
                "Elena says it's a lesson about life, that bullies only win when people\n"
                "are too afraid to stand together. *She looks at you.* Isn't that wise?\"",
                {{"\"That is wise. And perhaps a warning.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Elena is very good at teaching lessons.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 3; }}},
                true);

        addNode(state, "rosalind_elena_teaches", "Lady Rosalind",
                "\"*She counts on her fingers.* She taught me flower braiding, three\n"
                "card games, how to whistle with a blade of grass, and a lullaby from\n"
                "her village. *She hums a few notes.* Oh! And she's been helping me\n"
                "with my reading. She says I'm smart but I just need someone patient\n"
                "enough to explain things.\"",
                {{"\"She sounds like a good teacher.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 3;
                          gs.heroine_popularity += 2;
                  }},
                 {"\"Has she asked you about our family? About Father's business?\"", "rosalind_family_questions", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 3; }}});

        addNode(state, "rosalind_family_questions", "Lady Rosalind",
                "\"*She scrunches her face, thinking.* She asked about Mother once. I told\n"
                "her about the roses and how Mother used to sing in the garden. *She pauses.*\n"
                "Oh, and she asked about Father's library, which books were his favorites.\n"
                "And, um, she asked if Father had any enemies. *She looks at you uncertainly.*\n"
                "That's a normal question, isn't it?\"",
                {{"\"No, Rosalind. That is not a normal question.\"", "rosalind_family_alarm", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].suspicion += 5;
                          gs.heroine_popularity += 2;
                  }},
                 {"\"It's fine, little one. She was probably just curious.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }}});

        addNode(state, "rosalind_family_alarm", "Lady Rosalind",
                "\"*Her face crumples.* It's not? But she seemed so interested! She said\n"
                "she wanted to understand our family better so she could be a proper guest.\n"
                "*She wrings her hands.* Did I say something I shouldn't have? Oh no, did\n"
                "I tell her something dangerous? Sister, I'm sorry! I didn't think!\"",
                {{"\"It's not your fault. You're trusting, that's all.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 5;
                          gs.quest.rosalind_warned = true;
                  }},
                 {"\"From now on, don't answer her questions about our family.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.rosalind_warned = true;
                          gs.npcs["rosalind"].affection -= 3;
                  }}},
                true);

        addNode(state, "rosalind_elena_time", "Lady Rosalind",
                "\"*She shifts uncomfortably.* Is that bad? She's nice to me, sister.\n"
                "Cedric is always busy, Father is always in his study, and you...\n"
                "*She trails off, looking at her hands.* You're always doing important\n"
                "things. Elena actually has time for me.\"",
                {{"\"I'm sorry I haven't been around more. I'll do better.\"", "rosalind_neglect", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 10; }},
                 {"\"Elena has time because she has nothing else to do.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection -= 8;
                          gs.heroine_popularity += 3;
                  }}});

        addNode(state, "rosalind_neglect", "Lady Rosalind",
                "\"*She looks up at you with glistening eyes.* You will? *She throws her\n"
                "arms around you.* I know you're busy with important grown-up things. But\n"
                "sometimes I just, I miss when we used to pick berries in the garden and\n"
                "you'd tell me stories about brave princesses. *She sniffles.* We don't\n"
                "do that anymore.\"",
                {{"\"We'll pick berries tomorrow. I promise.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 10; }},
                 {"\"We grew up, Rosalind. Things change.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 3; }}},
                true);

        addNode(state, "rosalind_elena", "Lady Rosalind",
                "\"Elena? Oh, she's so wonderful, sister! She taught me how to braid\n"
                "flower crowns and she tells the best stories! *She beams.* Yesterday\n"
                "she told me about a princess who defeated a dragon by singing it a\n"
                "lullaby instead of fighting it! *She pauses.* You should join us\n"
                "next time!\"",
                {{"\"*Force a smile.* That sounds lovely.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 3; }},
                 {"\"Stay away from her, Rosalind.\"", "rosalind_warning", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 10; }},
                 {"\"Has Elena ever said anything strange to you?\"", "rosalind_elena_strange", nullptr, nullptr}});

        addNode(state, "rosalind_elena_strange", "Lady Rosalind",
                "\"*She thinks hard, her tongue poking out in concentration.* Strange?\n"
                "Hmm. *She brightens.* She said once that she wished she'd had a sister\n"
                "like me. And then she got really quiet and looked sad. *She fidgets.*\n"
                "Oh, and she said something funny, that sometimes the people who smile\n"
                "the most are hiding the most pain. I didn't really understand that.\"",
                {{"\"She might be right about that.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Did she say anything about our family?\"", "rosalind_family_questions", nullptr, nullptr}},
                true);

        addNode(state, "rosalind_warning", "Lady Rosalind",
                "\"*Her face falls.* But... she's so nice to me. Why would you say that?\n"
                "*Her eyes fill with tears.* You're just jealous because she's nice\n"
                "to everyone and people like her! *She clutches her sketchbook.* Elena\n"
                "says jealousy makes monsters of us all!\"",
                {{"\"I'm saying this because I love you. Elena isn't what she seems.\"",
                  "rosalind_warning_deep", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.rosalind_warned = true;
                          gs.heroine_popularity += 2;
                          gs.npcs["rosalind"].affection -= 5;
                  }},
                 {"\"Did Elena teach you that phrase too?\"", "rosalind_warning_phrase", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].suspicion += 5;
                  }},
                 {"\"*Sigh* Forget I said anything.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.heroine_popularity += 5; }}});

        addNode(state, "rosalind_warning_deep", "Lady Rosalind",
                "\"*She wipes her eyes with her sleeve.* Not what she seems? But she's\n"
                "always so kind. She remembers my name day, she braids my hair, she\n"
                "listens when I talk about my drawings. *She looks at you, confused and\n"
                "hurt.* If that's not real, then how do I know when anything is real?\"",
                {{"\"You trust me, don't you? I would never lie to you.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 5;
                          gs.quest.rosalind_warned = true;
                  }},
                 {"\"Sometimes you can't know. But I'll always protect you.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 8;
                          gs.quest.rosalind_warned = true;
                  }}},
                true);

        addNode(state, "rosalind_warning_phrase", "Lady Rosalind",
                "\"*She hesitates.* Well... yes. She says lots of smart things. *She\n"
                "fidgets.* Why? Is that bad? *She looks genuinely confused.* She also\n"
                "said that the strongest armor is kindness and the sharpest sword is\n"
                "truth. That's, that's a good thing, isn't it?\"",
                {{"\"Rosalind, she's teaching you her philosophy. Be careful.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.quest.rosalind_warned = true;
                          gs.npcs["rosalind"].suspicion += 5;
                  }},
                 {"\"It is a good thing. Just make sure you think for yourself.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 5;
                          gs.quest.rosalind_warned = true;
                  }}},
                true);

        addNode(state, "rosalind_rejected", "Lady Rosalind",
                "\"*She stumbles back, her eyes going wide.* Oh. *Her voice shrinks to\n"
                "almost nothing.* I'm sorry. I didn't mean to bother you. *She turns\n"
                "away, hugging herself.* Elena says I'm too clingy. Maybe she's right.\"",
                {{"\"Rosalind, wait. I didn't mean that.\"", "rosalind_apologize", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 5; }},
                 {"*Leave without another word*", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 10; }}});

        addNode(state, "rosalind_apologize", "Lady Rosalind",
                "\"*She turns back slowly, her eyes red-rimmed.* You didn't? *She sniffles.*\n"
                "It's just, everyone's been so tense lately. Father is always frowning,\n"
                "Cedric barely talks to me, and you always look like you're carrying the\n"
                "weight of the world. *She reaches for your hand.* Is everything okay,\n"
                "sister? You can tell me. I'm not as little as everyone thinks.\"",
                {{"\"Everything is fine, Rosalind. I'm sorry for being short with you.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 8; }},
                 {"\"You're more perceptive than I give you credit for.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 10; }}},
                true);

        addNode(state, "rosalind_serious", "Lady Rosalind",
                "\"*She puts down her sketchbook, her expression unusually grave for her\n"
                "age.* Important? *She sits up straighter, trying to look grown-up.*\n"
                "Okay. I'm listening.\"",
                {{"\"Elena has been sent away from the estate.\"", "rosalind_expelled_news",
                  [](const GameState &gs)
                  { return gs.quest.elena_expelled; },
                  nullptr},
                 {"\"I found out Elena has been hiding things from us.\"", "rosalind_letters_news",
                  [](const GameState &gs)
                  { return gs.quest.elena_letters_found && !gs.quest.elena_expelled; },
                  nullptr},
                 {"\"Something terrible has happened.\"", "rosalind_death_news",
                  [](const GameState &gs)
                  { return gs.quest.elena_dead; },
                  nullptr}});

        addNode(state, "rosalind_expelled_news", "Lady Rosalind",
                "\"*The color drains from her face.* Sent away? But, but she's my friend!\n"
                "*She stands up, knocking her sketchbook to the floor.* Why?! What did she\n"
                "do?! *Tears stream down her cheeks.* Did you do this, sister? Did you\n"
                "make Father send her away?!\"",
                {{"\"She was corresponding with rival nobles. She was a threat.\"", "rosalind_expelled_explain", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 10; }},
                 {"\"Father made the decision. I only showed him the truth.\"", "rosalind_expelled_blame", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 5; }},
                 {"\"I'm sorry, Rosalind. I know she meant a lot to you.\"", "rosalind_expelled_comfort", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 3; }}});

        addNode(state, "rosalind_expelled_explain", "Lady Rosalind",
                "\"*She shakes her head violently.* No! No, I don't believe it! Elena\n"
                "wouldn't do that! She was kind, she was good! *She picks up her\n"
                "sketchbook and holds it against her chest.* She drew a little flower\n"
                "in the corner of this page, right here, see? *Her voice breaks.* Bad\n"
                "people don't draw flowers for children!\"",
                {{"\"Sometimes bad people are the best at seeming good.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 5; }},
                 {"\"I know this is hard. I'm here for you, little one.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }}},
                true);

        addNode(state, "rosalind_expelled_blame", "Lady Rosalind",
                "\"*She stares at you, her expression crumbling.* You showed him. *Her\n"
                "voice is barely a whisper.* You planned this. You wanted her gone all\n"
                "along. *She backs away.* Elena said you might do this. She said some\n"
                "people only feel safe by making others disappear. I didn't believe her.\n"
                "*She turns away.* I should have.\"",
                {{"\"Rosalind, please. I did this to protect our family.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 5; }},
                 {"\"You'll understand when you're older.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 10; }}},
                true);

        addNode(state, "rosalind_expelled_comfort", "Lady Rosalind",
                "\"*She sobs, burying her face in your shoulder.* She was the only one\n"
                "who had time for me. *She hiccups.* She was going to teach me watercolors\n"
                "next week. *She pulls back, eyes swollen.* Can I, can I at least write\n"
                "to her? Please?\"",
                {{"\"Of course you can write to her.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 10;
                          gs.heroine_popularity += 3;
                  }},
                 {"\"I don't think that's a good idea.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 8; }}},
                true);

        addNode(state, "rosalind_letters_news", "Lady Rosalind",
                "\"*She blinks.* Hiding things? Like what? *She pulls her knees to her\n"
                "chest.* Everyone hides things. I hide my candy stash from Cedric. Is it\n"
                "that kind of hiding?\"",
                {{"\"She's been writing secret letters to rival noble families.\"", "rosalind_letters_detail", nullptr, nullptr},
                 {"\"Not exactly candy, Rosalind. More like secret plans.\"", "rosalind_letters_simple", nullptr, nullptr}});

        addNode(state, "rosalind_letters_detail", "Lady Rosalind",
                "\"*She goes very quiet.* Secret letters. *She thinks for a long time.*\n"
                "Maybe, maybe she had a good reason? Like, what if she was writing to\n"
                "help someone? *She looks at you hopefully.* Or what if someone was\n"
                "making her write them? She told me once that sometimes people do things\n"
                "they don't want to because they have no choice.\"",
                {{"\"You might be right. I need to find out for certain.\"", "", nullptr,
                  [](GameState &gs)
                  {
                          gs.npcs["rosalind"].affection += 5;
                          gs.heroine_popularity += 2;
                  }},
                 {"\"Don't make excuses for her, Rosalind.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection -= 5; }}},
                true);

        addNode(state, "rosalind_letters_simple", "Lady Rosalind",
                "\"Secret plans? *Her eyes go wide.* Like in a spy story? *She looks\n"
                "genuinely thrilled for a moment before catching herself.* Wait, that's\n"
                "bad, isn't it? *She hugs her knees.* But Elena wouldn't do bad things.\n"
                "She's, she's too nice for bad things.\"",
                {{"\"Nice people can still make choices others don't understand.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }},
                 {"\"Sometimes the nicest people have the darkest secrets.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].suspicion += 5; }}},
                true);

        addNode(state, "rosalind_death_news", "Lady Rosalind",
                "\"*She freezes.* Terrible? *Her voice is very small.* Who? *She searches\n"
                "your face and something in your expression makes her go pale.* No. No,\n"
                "no, no. *She covers her ears.* Don't say it. Please don't say it.\"",
                {{"\"Elena is gone, Rosalind. I'm so sorry.\"", "rosalind_death_reaction", nullptr, nullptr},
                 {"\"There was an accident. Elena didn't survive.\"", "rosalind_death_reaction", nullptr, nullptr}});

        addNode(state, "rosalind_death_reaction", "Lady Rosalind",
                "\"*She doesn't cry. She doesn't scream. She goes absolutely still, like\n"
                "a candle flame frozen in time. When she finally speaks, her voice is\n"
                "hollow.* She promised me. She promised she'd teach me watercolors.\n"
                "*She looks down at her sketchbook, at the little flower Elena drew\n"
                "in the corner.* She promised.\"",
                {{"*Hold her tight without saying a word*", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 5; }},
                 {"\"I'm here, Rosalind. I'll always be here.\"", "", nullptr,
                  [](GameState &gs)
                  { gs.npcs["rosalind"].affection += 3; }}},
                true);
}
