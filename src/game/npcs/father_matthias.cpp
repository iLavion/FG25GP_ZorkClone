#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerFatherMatthias(GameState& state) {
    NPC n;
    n.id           = "father_matthias";
    n.name         = "Father Matthias";
    n.title        = "Cathedral Priest";
    n.description  = "A tall, gaunt man in simple brown robes. His face is lined with age\n"
                     "and wisdom, and his grey eyes hold a penetrating calm. He speaks\n"
                     "softly but with an authority that makes even nobles lower their voices.";
    n.current_room = "cathedral_nave";
    n.affection    = 25;
    n.suspicion    = 0;
    n.disposition  = Disposition::Neutral;
    n.dialogue_root = "matthias_root";
    n.traits       = { Trait::Perceptive };
    n.schedule = {
        {6,  "cathedral_nave"},
        {8,  "cathedral_charity_kitchen"},
        {10, "cathedral_nave"},
        {12, "cathedral_clergy_office"},
        {14, "cathedral_side_chapel"},
        {16, "cathedral_nave"},
        {18, "cathedral_confessional"},
        {20, "cathedral_clergy_office"},
        {22, "cathedral_nave"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room)) {
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    }

    addNode(state, "matthias_root", "Father Matthias",
        "\"*He looks up from his prayer book with kind, weathered eyes.*\n"
        "Lady Seraphina. It has been some time since you visited the Cathedral.\n"
        "The Lord's house is always open. What brings you here, child?\"",
        {
            {"\"I came to pray.\"", "matthias_pray", nullptr, nullptr},
            {"\"I need guidance, Father.\"", "matthias_guidance", nullptr, nullptr},
            {"\"I want to confess something.\"", "matthias_confess", nullptr,
                [](GameState& gs) { gs.npcs["father_matthias"].affection += 5; }},
            {"\"I've heard Elena has been coming here.\"", "matthias_elena",
                [](const GameState& gs) { return gs.quest.met_elena; }, nullptr},
            {"\"What can you tell me about the Cathedral's charity work?\"",
             "matthias_charity", nullptr, nullptr}
        });

    addNode(state, "matthias_pray", "Father Matthias",
        "\"*He smiles gently.*\n"
        "Then you are welcome here, child. The Chapel of the Saints is\n"
        "quiet this time of day, and the stained glass catches the light\n"
        "beautifully. *He pauses.* Prayer has a way of clarifying the heart.\n"
        "Whatever weighs on you, bring it before the light and it will\n"
        "seem lighter.\"",
        {
            {"\"*Kneel and pray quietly*\"", "", nullptr,
                [](GameState& gs) {
                    gs.player.suspicion = std::max(0, gs.player.suspicion - 3);
                    gs.player.energy = std::min(100, gs.player.energy + 5);
                    std::cout << colored("  [i] The quiet prayer soothes your troubled mind.", ansi::BRIGHT_CYAN) << "\n";
                    std::cout << colored("  Suspicion -3, Energy +5", ansi::GREEN) << "\n";
                }},
            {"\"Thank you, Father. Perhaps later.\"", "", nullptr, nullptr}
        },
        true);

    addNode(state, "matthias_guidance", "Father Matthias",
        "\"*He sets aside his book and gives you his full attention.*\n"
        "Guidance? Then speak freely, child. These walls have heard the\n"
        "troubles of emperors and beggars alike. What burden do you carry?\"",
        {
            {"\"I feel threatened by someone, and I don't know what to do.\"",
             "matthias_threatened", nullptr, nullptr},
            {"\"I've done things I'm not proud of.\"", "matthias_regret",
                [](const GameState& gs) { return gs.player.suspicion >= 20; },
                nullptr},
            {"\"How do you tell right from wrong when the stakes are high?\"",
             "matthias_morality", nullptr, nullptr},
            {"\"I'm afraid of losing everything.\"", "matthias_fear", nullptr, nullptr}
        });

    addNode(state, "matthias_threatened", "Father Matthias",
        "\"*He nods slowly.*\n"
        "The feeling of being threatened often reveals what we value most.\n"
        "Is it your position? Your family? Your sense of self? *He looks\n"
        "at you steadily.* The greatest danger is not the threat itself,\n"
        "but what we become in response to it. A cornered animal bites,\n"
        "but a wise soul finds another way out of the cage.\"",
        {
            {"\"What if there is no other way?\"", "matthias_no_way", nullptr, nullptr},
            {"\"You're right. I need to be better than my instincts.\"",
             "matthias_better", nullptr, nullptr}
        });

    addNode(state, "matthias_no_way", "Father Matthias",
        "\"*He places a hand on your shoulder.*\n"
        "There is always another way, child. It may not be easy, it may\n"
        "not be satisfying, but it exists. The question is whether you\n"
        "have the courage to look for it. *He pauses.* Darkness cannot\n"
        "drive out darkness. Only light can do that.\"",
        {{"\"I will try, Father.\"", "", nullptr,
            [](GameState& gs) {
                gs.player.suspicion = std::max(0, gs.player.suspicion - 5);
                gs.player.reputation = std::min(100, gs.player.reputation + 3);
                std::cout << colored("  [i] Father Matthias's words inspire you.", ansi::BRIGHT_CYAN) << "\n";
                std::cout << colored("  Suspicion -5, Reputation +3", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_better", "Father Matthias",
        "\"*A warm smile crosses his face.*\n"
        "That, child, is the beginning of wisdom. Not perfection, but the\n"
        "desire to be better. Hold onto that desire when the temptation\n"
        "to take the easy path becomes strong. *He squeezes your shoulder.*\n"
        "You have more strength in you than you know.\"",
        {{"\"Thank you, Father. Truly.\"", "", nullptr,
            [](GameState& gs) {
                gs.player.suspicion = std::max(0, gs.player.suspicion - 5);
                gs.player.reputation = std::min(100, gs.player.reputation + 5);
                gs.npcs["father_matthias"].affection += 10;
                std::cout << colored("  Suspicion -5, Reputation +5", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_regret", "Father Matthias",
        "\"*His expression is compassionate, not judging.*\n"
        "None of us are proud of everything we've done, child. The fact\n"
        "that you feel regret means your conscience still speaks. Would\n"
        "you like to make a proper confession?\"",
        {
            {"\"Yes, Father. I've been scheming against someone.\"",
             "matthias_confess_scheme", nullptr, nullptr},
            {"\"Not yet. I'm not sure I'm ready to stop.\"",
             "matthias_not_ready", nullptr, nullptr}
        });

    addNode(state, "matthias_confess_scheme", "Father Matthias",
        "\"*He listens quietly, his face revealing nothing.*\n"
        "Scheming against another, even one who threatens you, puts your\n"
        "soul in danger, child. But I understand why you feel driven to it.\n"
        "The world has taught you to fight with shadows. *He takes a slow\n"
        "breath.* I will not tell you to abandon your family or your honor.\n"
        "But I ask that you seek justice, not revenge. They wear similar\n"
        "faces but lead to very different ends.\"",
        {{"\"Justice, not revenge. I'll remember.\"", "", nullptr,
            [](GameState& gs) {
                gs.player.suspicion = std::max(0, gs.player.suspicion - 8);
                gs.npcs["father_matthias"].affection += 10;
                std::cout << colored("  [i] Confessing eases the weight on your conscience.", ansi::BRIGHT_CYAN) << "\n";
                std::cout << colored("  Suspicion -8", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_not_ready", "Father Matthias",
        "\"*He sighs, but does not judge.*\n"
        "Then I will pray for you, child. When you are ready, the door\n"
        "is always open. But know this: the longer you walk a dark path,\n"
        "the harder it becomes to find the light again. Do not wait too long.\"",
        {{"\"I understand, Father.\"", "", nullptr, nullptr}},
        true);

    addNode(state, "matthias_morality", "Father Matthias",
        "\"*He seems to consider this deeply.*\n"
        "A question philosophers have wrestled with for centuries. My answer\n"
        "is imperfect, but it is this: right is what you would do if the\n"
        "whole world could see. Wrong is what you do in shadow and hope\n"
        "no one discovers. *He meets your eyes.* Would you be proud of\n"
        "your actions if your father witnessed them? If a child watched?\"",
        {
            {"\"Not always. And that troubles me.\"", "matthias_troubled", nullptr, nullptr},
            {"\"Sometimes survival requires shadows.\"", "matthias_survival",
             nullptr, nullptr}
        });

    addNode(state, "matthias_troubled", "Father Matthias",
        "\"Good. Let it trouble you. That trouble is your compass, child.\n"
        "The moment you stop feeling it, that is when you are truly lost.\n"
        "*He pats your hand.* Come to me when the trouble grows too heavy.\n"
        "That is what I am here for.\"",
        {{"\"I will, Father. Thank you.\"", "", nullptr,
            [](GameState& gs) {
                gs.npcs["father_matthias"].affection += 10;
                gs.player.reputation = std::min(100, gs.player.reputation + 2);
                std::cout << colored("  Reputation +2", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_survival", "Father Matthias",
        "\"*His expression grows serious.*\n"
        "Survival, yes. I have seen good people do terrible things to\n"
        "survive. And I have seen wicked people justify everything in its\n"
        "name. The difference is not in the action, child, it is in the\n"
        "weight you carry afterward. If it does not weigh on you, be afraid.\n"
        "That means you have lost something precious.\"",
        {{"\"*You feel the weight of his words.* Thank you, Father.\"", "", nullptr, nullptr}},
        true);

    addNode(state, "matthias_fear", "Father Matthias",
        "\"*He nods with understanding.*\n"
        "Fear of loss is the most human of all fears, child. Your family,\n"
        "your name, your future. These things feel like they define us.\n"
        "But I will tell you a secret: you will survive losing all of them.\n"
        "What you cannot survive is losing yourself. *He gazes at the\n"
        "stained glass.* Protect your soul above all else.\"",
        {
            {"\"How do I protect my soul when the world demands I fight dirty?\"",
             "matthias_dirty_fight", nullptr, nullptr},
            {"\"You make it sound simple.\"", "matthias_not_simple", nullptr, nullptr}
        });

    addNode(state, "matthias_dirty_fight", "Father Matthias",
        "\"By choosing your battles carefully. Not every threat requires\n"
        "a response. Not every rival requires destruction. Sometimes the\n"
        "bravest thing is to let someone succeed and prove your worth\n"
        "another way. *He pauses.* But I am a priest, not a politician.\n"
        "My answers may not satisfy the world you live in.\"",
        {{"\"They satisfy something deeper. Thank you.\"", "", nullptr,
            [](GameState& gs) {
                gs.npcs["father_matthias"].affection += 5;
                gs.player.suspicion = std::max(0, gs.player.suspicion - 3);
                std::cout << colored("  Suspicion -3", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_not_simple", "Father Matthias",
        "\"*He chuckles softly.*\n"
        "Simple? No, child. Nothing about it is simple. But the path of\n"
        "the soul has never been about simplicity. It is about persistence.\n"
        "Keep walking, even when the road is dark. That is all any of us\n"
        "can do.\"",
        {{"\"Persistence. I can do that.\"", "", nullptr, nullptr}},
        true);

    addNode(state, "matthias_confess", "Father Matthias",
        "\"*He adopts a formal, solemn air.*\n"
        "Then let us go to the confessional, where your words are between\n"
        "you and the Almighty alone. *He stands and gestures toward the\n"
        "wooden booths.* Speak what weighs upon your heart, child.\"",
        {
            {"\"I've been plotting against an innocent woman.\"",
             "matthias_confess_plot", nullptr, nullptr},
            {"\"I've been consumed by jealousy and pride.\"",
             "matthias_confess_pride", nullptr, nullptr},
            {"\"I've considered doing something terrible.\"",
             "matthias_confess_terrible",
                [](const GameState& gs) { return gs.quest.acquired_poison; },
                nullptr}
        });

    addNode(state, "matthias_confess_plot", "Father Matthias",
        "\"*He is silent for a long moment.*\n"
        "The road to destruction is paved with justified wrongdoing, child.\n"
        "This woman, does she truly threaten you, or does she merely\n"
        "represent a future you fear? *He shakes his head.* I cannot\n"
        "grant absolution for a sin you intend to continue. But I can\n"
        "offer you this: the courage to choose a different path. Will you\n"
        "take it?\"",
        {
            {"\"I'll try. But I make no promises.\"", "", nullptr,
                [](GameState& gs) {
                    gs.player.suspicion = std::max(0, gs.player.suspicion - 5);
                    std::cout << colored("  [i] Your honesty is refreshing. Suspicion -5", ansi::GREEN) << "\n";
                }},
            {"\"I'm not sure I can.\"", "", nullptr,
                [](GameState& gs) { gs.npcs["father_matthias"].affection += 3; }}
        },
        true);

    addNode(state, "matthias_confess_pride", "Father Matthias",
        "\"*A warm understanding fills his eyes.*\n"
        "Jealousy and pride, the twin thorns of the noble soul. You are\n"
        "not the first to sit in this confessional with such burdens, child,\n"
        "and you will not be the last. *He bows his head.* The cure is not\n"
        "to deny these feelings but to refuse to let them rule your actions.\n"
        "Feel the jealousy, acknowledge the pride, then set them down.\"",
        {{"\"I'll try to set them down. Thank you, Father.\"", "", nullptr,
            [](GameState& gs) {
                gs.player.suspicion = std::max(0, gs.player.suspicion - 5);
                gs.player.reputation = std::min(100, gs.player.reputation + 3);
                gs.npcs["father_matthias"].affection += 10;
                std::cout << colored("  Suspicion -5, Reputation +3", ansi::GREEN) << "\n";
            }}},
        true);

    addNode(state, "matthias_confess_terrible", "Father Matthias",
        "\"*His face grows very serious.*\n"
        "Something terrible. *He takes a deep breath.* Child, whatever\n"
        "this is, step back from the edge. Now. Before it is too late.\n"
        "No position, no title, no victory is worth the stain that some\n"
        "actions leave on the soul. *He grips your hands.* Promise me.\n"
        "Promise me you will find another way.\"",
        {
            {"\"I promise, Father. I'll find another way.\"", "", nullptr,
                [](GameState& gs) {
                    gs.player.suspicion = std::max(0, gs.player.suspicion - 10);
                    gs.npcs["father_matthias"].affection += 15;
                    std::cout << colored("  [i] Father Matthias's plea shakes you to your core.", ansi::BRIGHT_CYAN) << "\n";
                    std::cout << colored("  Suspicion -10", ansi::GREEN) << "\n";
                }},
            {"\"*You pull your hands away.* I can't promise that.\"", "", nullptr,
                [](GameState& gs) {
                    gs.npcs["father_matthias"].affection -= 10;
                    std::cout << colored("  [i] Father Matthias looks at you with deep sorrow.", ansi::BRIGHT_YELLOW) << "\n";
                }}
        },
        true);

    addNode(state, "matthias_elena", "Father Matthias",
        "\"*He nods thoughtfully.*\n"
        "Elena? Yes, she has been a regular visitor. A devout girl, or so\n"
        "it appears. She prays, she helps in the charity kitchen, she\n"
        "speaks kindly to everyone. *He pauses.* She reminds me of a\n"
        "flower that turns always toward the sun, seeking approval.\"",
        {
            {"\"You sound like you see through her act.\"", "matthias_elena_act",
             nullptr, nullptr},
            {"\"Is she genuine, Father?\"", "matthias_elena_genuine", nullptr, nullptr},
            {"\"She's been helping in the charity kitchen?\"",
             "matthias_elena_charity", nullptr, nullptr}
        });

    addNode(state, "matthias_elena_act", "Father Matthias",
        "\"*He chooses his words carefully.*\n"
        "I would not call it an act. But neither would I call it entirely\n"
        "spontaneous. She performs goodness with great skill. Whether the\n"
        "goodness is genuine underneath the performance, only she and the\n"
        "Almighty know. *He looks at you.* But I will say this: I have\n"
        "the same question about many nobles who sit in my pews, including,\n"
        "if you will forgive me, yourself.\"",
        {
            {"\"*You feel slightly stung.* Fair point, Father.\"", "", nullptr,
                [](GameState& gs) { gs.npcs["father_matthias"].affection += 10; }},
            {"\"I don't pretend to be something I'm not.\"", "", nullptr,
                [](GameState& gs) { gs.npcs["father_matthias"].suspicion += 5; }}
        },
        true);

    addNode(state, "matthias_elena_genuine", "Father Matthias",
        "\"Genuine? *He strokes his chin.* I believe she genuinely wants to\n"
        "be good. But I also believe she genuinely wants to be powerful.\n"
        "These two desires are not always compatible, child. When they\n"
        "collide, which one wins will reveal who she truly is. *He sighs.*\n"
        "The same is true for you.\"",
        {{"\"I understand. Thank you for your honesty.\"", "", nullptr,
            [](GameState& gs) { gs.npcs["father_matthias"].affection += 5; }}},
        true);

    addNode(state, "matthias_elena_charity", "Father Matthias",
        "\"Yes, twice a week. She serves soup, mends clothes, reads to\n"
        "the children. The poor adore her. *He pauses.* It is, of course,\n"
        "very public charity. Word spreads quickly when a beautiful young\n"
        "woman feeds the hungry. *He gives you a meaningful look.* If you\n"
        "wished to serve here as well, the charity kitchen could always\n"
        "use another pair of hands.\"",
        {
            {"\"I'd like to help. When can I start?\"", "", nullptr,
                [](GameState& gs) {
                    gs.player.reputation = std::min(100, gs.player.reputation + 5);
                    gs.npcs["father_matthias"].affection += 10;
                    std::cout << colored("  [i] Father Matthias beams. You are welcome anytime.", ansi::BRIGHT_GREEN) << "\n";
                    std::cout << colored("  Reputation +5", ansi::GREEN) << "\n";
                }},
            {"\"Charity is not my battlefield.\"", "", nullptr,
                [](GameState& gs) { gs.npcs["father_matthias"].affection -= 3; }}
        },
        true);

    addNode(state, "matthias_charity", "Father Matthias",
        "\"The Cathedral feeds over a hundred people every day, my lady.\n"
        "The war left many displaced, and the recent droughts have not\n"
        "helped. *He looks at you hopefully.* A donation from the Aldric\n"
        "family would go a long way. And it would not hurt your family's\n"
        "standing among the common people, if that matters to you.\"",
        {
            {"\"I'd like to donate. (20 gold)\"", "", 
                [](const GameState& gs) { return gs.player.gold >= 20; },
                [](GameState& gs) {
                    gs.player.gold -= 20;
                    gs.player.reputation = std::min(100, gs.player.reputation + 5);
                    gs.npcs["father_matthias"].affection += 15;
                    std::cout << colored("  You donate 20 gold to the Cathedral's charity.", ansi::BRIGHT_GREEN) << "\n";
                    std::cout << colored("  Reputation +5", ansi::GREEN) << "\n";
                }},
            {"\"I will speak to my father about a donation.\"", "", nullptr,
                [](GameState& gs) {
                    gs.npcs["father_matthias"].affection += 5;
                    gs.player.reputation = std::min(100, gs.player.reputation + 2);
                    std::cout << colored("  Reputation +2", ansi::GREEN) << "\n";
                }},
            {"\"I'm afraid I cannot help at this time.\"", "", nullptr, nullptr}
        },
        true);
}
