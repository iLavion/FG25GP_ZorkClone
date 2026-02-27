#include "game.hpp"
#include "game/dialogue_helpers.hpp"

namespace game::npcs
{

    void buildMarcelDialogue(GameState &state)
    {
        addNode(state, "marcel_root", "Chef Marcel",
                "Chef Marcel stands at his domain's center, a copper pot bubbling behind him and a cleaver "
                "resting within arm's reach. His apron is spattered with today's efforts, and his thick arms "
                "are crossed. \"Lady Seraphina. The kitchen is a busy place, but I always have a moment for "
                "the Duke's daughter. What brings you to my realm?\"",
                {
                    {"What is on the menu tonight?", "marcel_menu", nullptr, nullptr},
                    {"Tell me about yourself, Marcel.", "marcel_backstory", nullptr, nullptr},
                    {"I need to discuss the tea service.", "marcel_tea", nullptr, nullptr},
                    {"What do you know about Elena?", "marcel_elena", nullptr, nullptr},
                    {"I need your help with something.", "marcel_hire", [](const GameState &)
                     { return true; },
                     {}},
                    {"I want to discuss the cellar stores.", "marcel_cellar", nullptr, nullptr},
                    {"[After bribe] About our arrangement...", "marcel_post_bribe", [](const GameState &gs)
                     { return gs.quest.chef_bribed; },
                     {}},
                    {"[After Elena's expulsion] How is the kitchen?", "marcel_post_expulsion", [](const GameState &gs)
                     { return gs.quest.elena_expelled; },
                     {}},
                    {"[After body discovered] Marcel, we need to talk.", "marcel_post_death", [](const GameState &gs)
                     { return gs.quest.body_discovered; },
                     {}},
                    {"Goodbye.", "marcel_farewell", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_menu", "Chef Marcel",
                "Marcel's eyes light up, the topic closest to his heart. \"Tonight I am preparing a roast "
                "pheasant with herb crust, accompanied by braised root vegetables and a cream of mushroom soup "
                "to start. For dessert, a honey-almond tart with candied citrus peel.\" He kisses his fingers. "
                "\"The pheasant was brought in fresh this morning by the Duke's hunting party. I have been "
                "marinating it since dawn.\"",
                {
                    {"That sounds wonderful.", "marcel_menu_praise", nullptr, nullptr},
                    {"Could you prepare something special for a guest?", "marcel_menu_guest", nullptr, nullptr},
                    {"I need food for myself. I am hungry.", "marcel_food_request", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_menu_praise", "Chef Marcel",
                "He beams, a rare full smile crossing his stern face. \"You have good taste, my lady. "
                "Your mother, rest her soul, was the same. She always appreciated the craft.\" He lowers "
                "his voice conspiratorially. \"Between you and me, the Duke eats whatever is put in front "
                "of him without a word. But your mother, she could tell the difference between thyme and "
                "oregano with her eyes closed. I miss cooking for someone who truly understood.\"",
                {
                    {"I would like to learn about cooking sometime.", "marcel_teach", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "chef_marcel")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_teach", "Chef Marcel",
                "Marcel actually steps back in surprise. \"A noblewoman, wanting to learn the kitchen arts? "
                "That is... unusual.\" But he is clearly pleased. \"Come any morning before the breakfast rush "
                "and I will show you the basics. How to make a proper stock, how to judge heat by sound, "
                "how to balance flavors.\" He wags a thick finger. \"But you wear an apron in my kitchen, "
                "same as everyone else. No silk sleeves near my stoves.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_menu_guest", "Chef Marcel",
                "\"A special dish for a guest?\" His eyes narrow shrewdly. \"That depends entirely on "
                "what impression you wish to make, my lady. I can prepare something to impress, "
                "something to comfort, or something to... unsettle.\" He picks up his cleaver and "
                "examines the edge thoughtfully. \"Food is a weapon as surely as any blade. It can "
                "make a guest feel welcome, or make them feel very small indeed.\"",
                {
                    {"Something to impress Elena.", "marcel_impress_elena", nullptr, nullptr},
                    {"Something that would make someone uncomfortable.", "marcel_unsettle", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_impress_elena", "Chef Marcel",
                "\"The heroine?\" He considers. \"She comes from common stock, if the rumors are true. "
                "I could prepare dishes so refined, so impossibly elegant, that she would not even know "
                "how to eat them properly. Ortolan in aspic, quail eggs in saffron sauce, a dessert "
                "that requires three different spoons.\" He smirks. \"Nothing humiliates like a table "
                "setting one cannot navigate.\"",
                {
                    {"Perfect. Do it.", "marcel_impress_accept", nullptr, [](GameState &gs)
                     {
                         gs.heroine_popularity -= 3;
                     }},
                    {"No, I want to genuinely make her welcome.", "marcel_welcome_elena", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_impress_accept", "Chef Marcel",
                "\"Consider it done, my lady.\" His smirk widens. \"I will prepare a formal twelve-course "
                "menu with enough silverware to confuse a duchess, let alone a commoner. She will not know "
                "whether to eat the garnish or wear it.\" He chuckles darkly. \"The kitchen serves the "
                "house, and the house serves you.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_welcome_elena", "Chef Marcel",
                "Marcel raises an eyebrow, surprised. \"Genuine hospitality? For the heroine?\" "
                "He shrugs. \"As you wish. I will prepare hearty country fare elevated just enough "
                "to show respect without condescension. A good roast, honest bread, a fruit compote. "
                "The kind of meal that says 'you are welcome here, and we see you as you are.'\" "
                "He pauses. \"You are more generous than I expected, my lady.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_unsettle", "Chef Marcel",
                "Marcel sets down the cleaver with a deliberate thud. \"Now that is more my expertise. "
                "A dish that looks beautiful but tastes of ash and bitter herbs. Or a soup that is "
                "just slightly too spicy, enough to make the eyes water without being obviously wrong.\" "
                "He leans in. \"Or, if you want subtlety, I simply serve something the guest is known "
                "to dislike. It sends a message without leaving proof.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_food_request", "Chef Marcel",
                "\"My lady, you need not ask. There is always something ready in the kitchen.\" "
                "He moves to a side counter and returns with a plate: cold sliced ham, fresh bread, "
                "and a small pot of mustard. \"Eat. A hungry mind makes poor decisions, and you look "
                "like you have important decisions ahead of you.\"",
                {
                    {"Thank you, Marcel.", "marcel_root", nullptr, [](GameState &gs)
                     {
                         gs.player.hunger = std::min(gs.player.hunger + 25, 100);
                     }},
                },
                false);

        addNode(state, "marcel_backstory", "Chef Marcel",
                "Marcel sets down his utensils and leans against the counter. \"I trained in the capital, "
                "at the Grand Imperial Kitchen under Master Bouchard. Fifteen years, from scullery boy to "
                "sous-chef.\" His expression darkens. \"Then Bouchard sold the kitchen's reputation for "
                "political favors. Started serving inferior ingredients to fund his gambling debts. "
                "When I confronted him, he had me dismissed and blacklisted from every restaurant "
                "in the capital.\"",
                {
                    {"How did you end up here?", "marcel_backstory_estate", nullptr, nullptr},
                    {"That must have been difficult.", "marcel_backstory_sympathy", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_backstory_estate", "Chef Marcel",
                "\"Your father found me. Or rather, Butler Graves found me on your father's behalf. "
                "The Duke was looking for a private chef who could handle formal dinners and daily meals "
                "alike. Graves heard about my dismissal and investigated the truth of it.\" Marcel's "
                "expression softens slightly. \"The Duke offered me this position without hesitation. "
                "Said he valued honest cooking over political connections.\" He pauses. \"That was "
                "twelve years ago. I have never given him reason to regret the choice.\"",
                {
                    {"And Bouchard?", "marcel_bouchard", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_backstory_sympathy", "Chef Marcel",
                "\"Difficult?\" He laughs bitterly. \"I spent three months sleeping in alleyways, "
                "cooking scraps for tavern owners who paid in copper and insults. A man who has "
                "prepared feasts for nobility, reduced to tavern slop.\" He straightens. \"But it taught "
                "me something valuable: pride is a luxury, but skill is permanent. I carried my craft "
                "with me even when I had nothing else.\"",
                {
                    {"That is admirable.", "marcel_backstory_admire", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "chef_marcel")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_backstory_admire", "Chef Marcel",
                "He waves a hand dismissively, but there is warmth in his eyes. \"Admirable? "
                "Desperate, more like. But I appreciate the sentiment, my lady. You are one of the "
                "few in this house who has ever asked.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_bouchard", "Chef Marcel",
                "Marcel's jaw tightens. \"Last I heard, he drank himself into ruin and his kitchen "
                "was shuttered. Poetic justice, perhaps.\" He picks up a knife and begins chopping "
                "vegetables with controlled fury. \"But I will not pretend I do not still feel the "
                "bitterness. A man who trades integrity for gold deserves everything he gets.\" "
                "He pauses mid-chop. \"Which is why I take any offer of coin very seriously, my lady. "
                "I know the cost of compromising one's principles.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea", "Chef Marcel",
                "\"The afternoon tea service?\" Marcel wipes his hands. \"I prepare it daily at "
                "three o'clock. Earl grey for the Duke, chamomile for Lady Rosalind, and your preference "
                "of course.\" He eyes you carefully. \"Is there something specific about the tea service "
                "you wish to discuss?\"",
                {
                    {"Who handles the tea between kitchen and table?", "marcel_tea_chain", nullptr, nullptr},
                    {"Could anything be added to the tea without detection?", "marcel_tea_poison", nullptr, nullptr},
                    {"I want Elena invited to tea.", "marcel_tea_elena", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea_chain", "Chef Marcel",
                "\"I brew the tea personally. It goes on a tray with the appropriate cups and saucers. "
                "Then Graves or one of the junior servants carries it to the drawing room.\" He frowns. "
                "\"There is a window of perhaps five minutes between when the tray leaves my kitchen "
                "and when it reaches the table. During that time, it passes through the hallway and, "
                "on some occasions, the servant uses the back corridor.\" He looks at you pointedly. "
                "\"That corridor has several alcoves where one might be unobserved.\"",
                {
                    {"Interesting.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea_poison", "Chef Marcel",
                "Marcel's expression goes carefully blank. \"My lady, I am a chef. I work with "
                "ingredients that can heal or harm in equal measure. A strong enough flavor, say "
                "bergamot or mint, can mask almost anything.\" He does not look at you as he speaks. "
                "\"Hypothetically, of course. A responsible chef would never allow tampering with food "
                "or drink that leaves his kitchen.\" He pauses. \"But the tea does leave my kitchen, "
                "does it not? What happens after that is outside my control.\"",
                {
                    {"I understand your meaning.", "marcel_root", nullptr, [](GameState &gs)
                     {
                         gs.player.suspicion += 2;
                     }},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea_elena", "Chef Marcel",
                "\"An extra cup for the heroine? Simple enough.\" He pulls out another saucer. "
                "\"I will prepare a proper setting. What blend do you suggest for her? Something "
                "refined to remind her of her station? Or something common and honest, as a subtle "
                "commentary?\"",
                {
                    {"Something refined. Let her feel out of place.", "marcel_tea_refined", nullptr, [](GameState &gs)
                     {
                         gs.quest.invited_elena = true;
                     }},
                    {"Something welcoming. I want her comfortable.", "marcel_tea_welcoming", nullptr, [](GameState &gs)
                     {
                         gs.quest.invited_elena = true;
                     }},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea_refined", "Chef Marcel",
                "\"A rare white tea from the eastern provinces, then. Delicate, expensive, and served "
                "in porcelain so thin you can see the light through it.\" He smirks. \"She will not "
                "know whether to drink it or admire it. And every sip will remind her that she is "
                "drinking something worth more than a month of her family's income.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_tea_welcoming", "Chef Marcel",
                "Marcel blinks, then nods with something approaching respect. \"A good herbal blend "
                "then. Honey and lemon. The kind of tea that puts a person at ease.\" He studies you. "
                "\"You are playing a longer game than I gave you credit for, my lady. A comfortable "
                "guest reveals more than a nervous one.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena", "Chef Marcel",
                "Marcel scoffs openly. \"The heroine? She came into my kitchen on her second day here and "
                "offered to help with the cooking.\" He sounds personally offended. \"Help. In my kitchen. "
                "As if she could simply walk in and start chopping onions beside a trained Imperial chef.\" "
                "He calms himself. \"I will say this: she has a way with people. The scullery maids adore "
                "her. She brings them wildflowers and asks about their families. Within a week, half my "
                "kitchen staff would walk through fire for her.\"",
                {
                    {"She is winning over the servants?", "marcel_elena_servants", nullptr, nullptr},
                    {"Does she ever ask for anything unusual?", "marcel_elena_unusual", nullptr, nullptr},
                    {"Has she been in the kitchen stores?", "marcel_elena_stores", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_servants", "Chef Marcel",
                "\"Not just winning, conquering. She knows every servant's name, their children's names, "
                "their birthdays.\" Marcel waves the cleaver for emphasis. \"In twelve years I have "
                "never learned the scullery boy's surname, and she had it memorized in two days. "
                "Either she genuinely cares about common folk, which I doubt given her ambition, "
                "or she is building a network of loyal informants under this very roof.\"",
                {
                    {"That is concerning.", "marcel_elena_concern", nullptr, nullptr},
                    {"Maybe she is just kind.", "marcel_elena_kind", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_concern", "Chef Marcel",
                "\"It should be, my lady. The kitchen hears everything. Servants gossip while they "
                "peel potatoes. If Elena has their loyalty, she has their ears and their tongues.\" "
                "He lowers his voice. \"Nothing said in this house is truly private if the servants "
                "are not on your side. Remember that.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_kind", "Chef Marcel",
                "\"Kind.\" He rolls the word around his mouth like a questionable ingredient. "
                "\"Perhaps. But kindness that is this strategic, this perfectly targeted, this consistent? "
                "That is not kindness, my lady. That is a campaign.\" He shrugs. \"But what do I know? "
                "I am just a cook.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_unusual", "Chef Marcel",
                "\"Now that you mention it...\" Marcel strokes his chin. \"She asked about the herb "
                "stores three days ago. Wanted to know if we kept medicinal herbs separate from cooking "
                "herbs. Said she was interested in traditional remedies.\" He narrows his eyes. "
                "\"I told her the medicinal herbs are Thorne's domain, not mine. But I saw her lingering "
                "near the spice cabinet afterward, reading labels.\"",
                {
                    {"What labels was she reading?", "marcel_elena_labels", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_labels", "Chef Marcel",
                "\"The exotic spices. Star anise, white pepper, and...\" He pauses. \"Nutmeg. "
                "In large quantities, nutmeg is not just a spice, my lady. It can cause hallucinations, "
                "confusion, even illness. A pinch in a cake is delightful. A tablespoon in a drink "
                "is dangerous.\" He meets your eyes. \"I cannot say what she intended. But I moved "
                "the nutmeg to the locked cabinet after that.\"",
                {
                    {"Good thinking.", "marcel_root", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_elena_stores", "Chef Marcel",
                "\"She has not entered the cold stores, no. Those are locked and I keep the key on "
                "my person at all times.\" He pats his apron pocket. \"But she has been in the dry "
                "pantry twice. She claimed she was looking for biscuits for Lady Rosalind.\" He snorts. "
                "\"She was in there long enough to inventory the entire room. Biscuits do not require "
                "that much browsing.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire", "Chef Marcel",
                "Marcel crosses his arms, his expression shifting to one of careful calculation. "
                "\"Help, you say. I am a chef, not a hired blade. But everyone has skills beyond their "
                "title, and everyone has a price.\" He studies you. \"What exactly do you need?\"",
                {
                    {"I need something to put in Elena's food. (20 gold)", "marcel_hire_poison", [](const GameState &gs)
                     {
                         return gs.player.gold >= 20 && !gs.quest.chef_bribed;
                     },
                     {}},
                    {"Sabotage a dinner to embarrass Elena. (15 gold)", "marcel_hire_sabotage", [](const GameState &gs)
                     { return gs.player.gold >= 15; }, [](GameState &gs)
                     {
                    gs.player.gold -= 15;
                    gs.quest.elena_embarrassed = true;
                    gs.heroine_popularity -= 5;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "chef_marcel") {
                            n.second.affection += 5;
                            break;
                        }
                    } }},
                    {"Report anything Elena does in the kitchen. (10 gold)", "marcel_hire_watch", [](const GameState &gs)
                     { return gs.player.gold >= 10; }, [](GameState &gs)
                     {
                    gs.player.gold -= 10;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "chef_marcel") {
                            n.second.affection += 5;
                            break;
                        }
                    } }},
                    {"Lock the kitchen stores so Elena cannot access them. (5 gold)", "marcel_hire_lock", [](const GameState &gs)
                     { return gs.player.gold >= 5; }, [](GameState &gs)
                     { gs.player.gold -= 5; }},
                    {"Never mind.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_poison", "Chef Marcel",
                "Marcel goes very still. His hands rest flat on the counter, and for a moment "
                "the kitchen seems to hold its breath. \"You are asking me to cross a line, my lady. "
                "One that cannot be uncrossed.\" He glances at the door, then back to you. "
                "\"Twenty gold, and I will prepare something that causes severe illness but not death. "
                "It will look like bad shellfish, a common enough occurrence. No one will suspect the chef "
                "who has fed this household without incident for twelve years.\"",
                {
                    {"Do it.", "marcel_hire_poison_accept", nullptr, [](GameState &gs)
                     {
                         gs.player.gold -= 20;
                         gs.quest.chef_bribed = true;
                         gs.quest.acquired_poison = true;
                         gs.player.suspicion += 5;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "chef_marcel")
                             {
                                 n.second.suspicion += 20;
                                 break;
                             }
                         }
                     }},
                    {"No. That is too far.", "marcel_hire_poison_refuse", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_poison_accept", "Chef Marcel",
                "Marcel takes the gold without counting it. His face is a mask. \"It will be in the "
                "next meal I serve to the guest room. A private supper, nothing that could affect the "
                "family.\" He pauses at the door to the pantry. \"We do not speak of this again, "
                "my lady. Not here, not anywhere. If anyone asks, I will deny everything, and I am "
                "a very convincing liar when my livelihood depends on it.\"",
                {
                    {"Understood.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_poison_refuse", "Chef Marcel",
                "Something relaxes in Marcel's shoulders, though his expression does not change. "
                "\"A wise decision, my lady. Poison is a coward's tool, and you are no coward.\" "
                "He returns to his chopping. \"There are other ways to deal with unwanted guests. "
                "Less permanent ones.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_sabotage", "Chef Marcel",
                "Marcel's eyes gleam with professional mischief. \"Now this I can do with artistry. "
                "A dish that spills at the worst moment. A sauce that stains silk beyond repair. "
                "A dessert that collapses dramatically just as the guest takes a bite.\" He rubs his "
                "hands together. \"I once saw a souffl\\u00e9 catastrophe end a betrothal in the capital. "
                "Food can destroy reputations without anyone lifting a finger, and the chef is never blamed "
                "because 'accidents happen in the kitchen.'\"",
                {
                    {"Make it memorable.", "marcel_sabotage_confirm", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_sabotage_confirm", "Chef Marcel",
                "\"Oh, it will be. I am thinking a red wine reduction that 'accidentally' transfers "
                "from serving platter to her dress. Or a pepper grinder that 'malfunctions' directly "
                "over her plate.\" He grins. \"Leave the details to me, my lady. By tomorrow evening, "
                "the only thing anyone will remember about dinner is the heroine's humiliation.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_watch", "Chef Marcel",
                "\"Ten gold to keep my eyes open? You drive a generous bargain, my lady.\" He tucks "
                "the coins away. \"I will note every time she enters the kitchen, what she touches, "
                "who she speaks with, and for how long. The kitchen is my territory, and nothing moves "
                "through it without my knowledge.\"",
                {
                    {"I will check in with you regularly.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_hire_lock", "Chef Marcel",
                "\"Easily done. I will claim we had a rat problem and that all stores must be secured. "
                "No one will question it, rats are a kitchen's eternal enemy.\" He produces a heavy key. "
                "\"The pantry, the spice cabinet, and the cold stores will all require my personal key. "
                "If the heroine wants so much as a pinch of salt, she will have to come through me.\"",
                {
                    {"Good.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_cellar", "Chef Marcel",
                "\"The cellar stores are my concern as well as the kitchen. Wine, preserved foods, "
                "root vegetables for the winter.\" He frowns. \"I have noticed inventory discrepancies "
                "lately. Small amounts, nothing that would raise an alarm on its own. A bottle of wine "
                "here, a jar of preserves there.\"",
                {
                    {"Someone is stealing from the cellars?", "marcel_cellar_theft", nullptr, nullptr},
                    {"Could it be the servants?", "marcel_cellar_servants", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_cellar_theft", "Chef Marcel",
                "\"Stealing is a strong word. But yes, supplies are leaving the cellar that I did "
                "not authorize.\" He pulls out a worn ledger. \"I keep meticulous records. Three bottles "
                "of the '42 Burgundy, gone. A wheel of aged cheese, gone. Two jars of honey, gone.\" "
                "He snaps the ledger shut. \"This is not a servant sneaking snacks. This is someone "
                "provisioning for something. Possibly stocking supplies for a journey, or feeding "
                "someone who should not be in the estate.\"",
                {
                    {"Could Elena be hiding someone?", "marcel_cellar_hiding", nullptr, nullptr},
                    {"I will look into it.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_cellar_hiding", "Chef Marcel",
                "\"It crossed my mind.\" He lowers his voice. \"The cellar connects to older parts "
                "of the estate. If someone knew the layout, they could move supplies without being seen.\" "
                "He shrugs. \"But who would she be feeding? A contact from outside? A co-conspirator?\" "
                "He taps the ledger. \"All I know is the numbers do not add up, and they started not "
                "adding up shortly after our guest arrived.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_cellar_servants", "Chef Marcel",
                "\"My staff knows better. I count everything, and they know I count everything. "
                "A servant caught stealing from my kitchen would be dismissed before the stolen bread "
                "hit their stomach.\" His expression is fierce on this point. \"No. This is someone "
                "who does not fear the kitchen hierarchy. Someone who believes they are above suspicion.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_post_bribe", "Chef Marcel",
                "Marcel glances around nervously before speaking, keeping his voice barely above "
                "the clatter of pots. \"It is done, my lady. I do not want to discuss details. "
                "The preparation was administered as agreed.\" He wipes his hands obsessively on his "
                "apron. \"I will say this once: do not ask me to do anything like it again. My hands "
                "are for creating, not for... what they did. The guilt sits in my stomach like a stone.\"",
                {
                    {"You did the right thing.", "marcel_bribe_reassure", nullptr, nullptr},
                    {"Your silence is more important than your comfort.", "marcel_bribe_threaten", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_bribe_reassure", "Chef Marcel",
                "\"Did I?\" He does not look convinced. \"I have spent my entire career building "
                "something honest from ingredients and heat. One act, and it all feels tainted.\" "
                "He takes a steadying breath. \"But what is done is done. I will not undo it, "
                "and I will not speak of it. You have my word on that, at least.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_bribe_threaten", "Chef Marcel",
                "Marcel's face drains of color, then flushes with anger. \"Threaten me in my own "
                "kitchen, my lady?\" But the anger fades quickly, replaced by something colder. "
                "\"Very well. I understand the arrangement. But remember, a chef who knows your secrets "
                "is either an ally or a liability. It would be wiser to keep me as the former.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "chef_marcel")
                             {
                                 n.second.affection -= 15;
                                 n.second.suspicion += 10;
                                 break;
                             }
                         }
                     }},
                },
                false);

        addNode(state, "marcel_post_expulsion", "Chef Marcel",
                "Marcel is rolling pastry dough with barely contained satisfaction. \"The kitchen runs "
                "smoothly once more, my lady. No more unexpected visitors, no more servants distracted "
                "by wildflowers and sweet talk.\" He dusts flour from his hands. \"I prepared a "
                "celebratory pastry, if you would like one. Almond and rosewater, your grandmother's "
                "recipe.\" He pauses. \"The scullery maids were upset at first, but they will recover. "
                "Servants always do.\"",
                {
                    {"I will take that pastry.", "marcel_pastry", nullptr, [](GameState &gs)
                     {
                         gs.player.hunger = std::min(gs.player.hunger + 10, 100);
                     }},
                    {"How are the staff taking it?", "marcel_staff_morale", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_pastry", "Chef Marcel",
                "He presents it with a flourish: a golden crescent dusted with powdered sugar, "
                "still warm from the oven. \"Eat it while it is warm, my lady. Perfection waits "
                "for no one.\"",
                {
                    {"Delicious.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_staff_morale", "Chef Marcel",
                "\"Mixed, if I am honest. The younger servants miss her charm and attention. "
                "The older ones are relieved, they always knew something was off about a commoner "
                "who fit in too perfectly.\" He lowers his voice. \"Clara has been particularly vocal "
                "in your defense, which is useful. And Graves, as always, says nothing, which is "
                "even more useful.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_post_death", "Chef Marcel",
                "Marcel stands motionless, his hands flat on the counter. The kitchen is uncharacteristically "
                "silent. No bubbling pots, no sizzling pans. \"My lady.\" His voice is hoarse. \"The kitchen "
                "has been quiet today. No one wants to eat. The staff are frightened.\" He meets your eyes, "
                "and there is something searching in his gaze. \"If I knew anything, if I had any part in "
                "what happened, that knowledge would destroy me. So I choose to know nothing.\" He picks up "
                "a knife and begins mechanically dicing onions. \"The onions are making my eyes water, "
                "in case anyone asks.\"",
                {
                    {"No one is asking, Marcel.", "marcel_death_comfort", nullptr, nullptr},
                    {"Keep the kitchen running. Normalcy helps.", "marcel_death_normalcy", nullptr, nullptr},
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_death_comfort", "Chef Marcel",
                "\"Good.\" His voice breaks slightly on the word. \"Then I will keep doing what I do. "
                "Cooking. Feeding this household. Pretending that the world has not shifted beneath our feet.\" "
                "He chops faster. \"Food is honest, my lady. It nourishes or it does not. It has no "
                "hidden motives, no ambitions. I find comfort in that, these days more than ever.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_death_normalcy", "Chef Marcel",
                "\"Normalcy.\" He almost laughs. \"Very well, my lady. Tonight's dinner will be served "
                "at the usual hour. Soup, roast, dessert. The household will sit at the same table and "
                "eat the same food and pretend that nothing has changed.\" He sets the knife down. "
                "\"That is what you need, is it not? The appearance that everything continues as before.\" "
                "He nods slowly. \"The kitchen can provide that, at least.\"",
                {
                    {"Back to other matters.", "marcel_root", nullptr, nullptr},
                },
                false);

        addNode(state, "marcel_farewell", "Chef Marcel",
                "Marcel gives a curt nod, already turning back to his pots. \"The kitchen never sleeps, "
                "my lady. Neither do I, most days. You know where to find me.\"",
                {}, true);
    }

}


void registerChefMarcel(GameState &state)
{
    NPC n;
    n.id = "chef_marcel";
    n.name = "Chef Marcel";
    n.title = "Head Chef";
    n.description = "The temperamental but brilliant head chef. He controls the kitchen with\n"
                    "an iron ladle and keeps meticulous records.";
    n.current_room = "kitchen";
    n.affection = 30;
    n.suspicion = 0;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "marcel_root";
    n.traits = {Trait::Greedy, Trait::EarlyBird, Trait::Strong};
    n.hireable = true;
    n.hire_cost = 20;
    n.schedule = {
        {5, "kitchen"},
        {8, "dining_room"},
        {9, "kitchen"},
        {12, "dining_room"},
        {13, "kitchen"},
        {15, "cellar"},
        {16, "kitchen"},
        {19, "dining_room"},
        {20, "kitchen"},
        {22, "servants_quarters"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildMarcelDialogue(state);
}
