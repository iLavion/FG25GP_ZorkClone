#include "game.hpp"
#include "game/dialogue_helpers.hpp"

namespace game::npcs
{

    void buildThorneDialogue(GameState &state)
    {
        addNode(state, "thorne_root", "Gardener Thorne",
                "Thorne kneels among the rosebushes, his weathered hands moving with practiced care. "
                "He glances up, soil-streaked and squinting. \"Lady Seraphina. The garden keeps its own counsel, "
                "but I am always willing to share what I notice.\"",
                {
                    {"Tell me about the garden.", "thorne_garden", nullptr, nullptr},
                    {"Have you noticed anything unusual lately?", "thorne_observations", nullptr, nullptr},
                    {"I want to know about the secret passages.", "thorne_passage_intro", nullptr, nullptr},
                    {"Tell me about yourself, Thorne.", "thorne_backstory", nullptr, nullptr},
                    {"I need your help with something.", "thorne_hire", [](const GameState &)
                     { return true; },
                     {}},
                    {"What do you know about plants and herbs?", "thorne_herbs", nullptr, nullptr},
                    {"[After Elena's expulsion] How are the grounds?", "thorne_post_expulsion", [](const GameState &gs)
                     { return gs.quest.elena_expelled; },
                     {}},
                    {"[After body discovered] About what happened...", "thorne_post_death", [](const GameState &gs)
                     { return gs.quest.body_discovered; },
                     {}},
                    {"Goodbye.", "thorne_farewell", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_garden", "Gardener Thorne",
                "Thorne gestures broadly at the grounds. \"The Aldric gardens are among the finest in the province. "
                "Three generations of careful tending. Every hedge, every flower bed tells a story.\" He points to a "
                "row of white roses near the east wall. \"Those were planted by your grandmother. And the wisteria "
                "along the balcony, that was your mother's favorite.\" His voice softens. \"I promised her I would "
                "keep them blooming. And so I have.\"",
                {
                    {"My mother loved the wisteria?", "thorne_mother_garden", nullptr, nullptr},
                    {"The roses near the east wall, are they special?", "thorne_roses", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_mother_garden", "Gardener Thorne",
                "Thorne pauses, his hands going still on the pruning shears. \"Your mother, may she rest, "
                "spent many afternoons here. She said the wisteria reminded her of her childhood home in the "
                "southern valley.\" He clears his throat. \"She had a gift for growing things. Not just plants, "
                "mind you. People, too. The staff adored her. When she... when we lost her, the gardens nearly "
                "died that winter. I could not bring myself to tend them.\" He straightens. \"But then I remembered "
                "my promise. And the wisteria bloomed again in spring, as if she willed it so.\"",
                {
                    {"Thank you for telling me that.", "thorne_mother_thanks", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_mother_thanks", "Gardener Thorne",
                "Something shifts behind his weathered expression. \"You have her eyes, my lady. And her "
                "kindness, when you choose to show it.\" He returns to his work, but there is a warmth "
                "in his movements that was not there before.",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_roses", "Gardener Thorne",
                "\"The white roses are a rare breed, brought from the northern highlands decades ago. "
                "They bloom only in autumn, when everything else is dying.\" He examines one closely. "
                "\"Your grandmother said they were a reminder that beauty persists even in dark seasons.\" "
                "He lowers his voice. \"Interesting thing about those roses, a certain young woman has "
                "taken to visiting them at dawn. Picks a petal or two when she thinks no one is watching.\"",
                {
                    {"You mean Elena?", "thorne_elena_roses", nullptr, nullptr},
                    {"Why would someone pick rose petals?", "thorne_petals_use", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_elena_roses", "Gardener Thorne",
                "Thorne gives a slow, careful nod. \"I do not speak names without cause, but yes. "
                "The heroine. She comes at first light, always to the east wall. She handles the blooms "
                "gently enough, but she is looking for something specific.\" He frowns. \"White rose petals "
                "have uses beyond decoration, my lady. In the old herbalist texts, they are an ingredient "
                "in several preparations. Some medicinal. Some... less so.\"",
                {
                    {"Less so? What do you mean?", "thorne_elena_poison_hint", nullptr, nullptr},
                    {"Keep watching her for me.", "thorne_elena_watch", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_elena_poison_hint", "Gardener Thorne",
                "Thorne glances around before answering. \"A tincture of white rose petal, combined with "
                "foxglove root and nightshade berry, creates a draught that mimics a natural fever. "
                "Undetectable by most physicians.\" He holds up a hand. \"I am not saying she means harm. "
                "But a gardener notices what grows in his soil, and what is taken from it. That is all.\"",
                {
                    {"That is very useful to know.", "thorne_poison_knowledge", nullptr, nullptr},
                    {"Could she be making perfume instead?", "thorne_innocent_use", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_poison_knowledge", "Gardener Thorne",
                "\"Knowledge is neither good nor evil, my lady. It is what we do with it that matters.\" "
                "He meets your eyes steadily. \"I have served this house for nearly thirty years. "
                "Whatever you need from this garden, whether to grow or to cut down, you need only ask.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_innocent_use", "Gardener Thorne",
                "\"Perhaps.\" His tone suggests he does not believe it. \"White rose makes a fine perfume, "
                "true enough. But one does not need to pick petals at dawn for fragrance. The best time for "
                "perfume-making is midday, when the oils are warmest.\" He shrugs. \"An early riser myself, "
                "I know which hours belong to which purposes.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_elena_watch", "Gardener Thorne",
                "\"I already watch everything that moves in these grounds, my lady. It is in my nature.\" "
                "He taps the side of his nose. \"But I will pay special attention. If she takes anything "
                "more than petals, or meets anyone by the east wall, you will be the first to know.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_observations", "Gardener Thorne",
                "Thorne sets down his trowel and brushes his hands on his apron. \"Unusual? Where to begin.\" "
                "He ticks off fingers. \"Footprints near the cellar entrance three nights running. Someone "
                "trimmed the ivy near the south wall, and it was not me. And there is a new pattern of "
                "lantern light from the guest room, late at night, as if someone is reading by candlelight "
                "until the small hours.\"",
                {
                    {"Footprints near the cellar?", "thorne_cellar_prints", nullptr, nullptr},
                    {"The ivy was trimmed? Why would someone do that?", "thorne_ivy", nullptr, nullptr},
                    {"Late nights in the guest room...", "thorne_guest_light", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_cellar_prints", "Gardener Thorne",
                "\"Boot prints, not house shoes. Someone coming from outside, or at least wearing "
                "outdoor footwear.\" He scratches his chin. \"The cellar has its own secrets, as you may "
                "know. But these prints are fresh, repeated, deliberate. Whoever is visiting the cellar "
                "entrance is doing so with purpose, and at hours when the household is asleep.\"",
                {
                    {"Could it be related to the passages?", "thorne_cellar_passage", nullptr, nullptr},
                    {"I will investigate.", "thorne_cellar_noted", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_cellar_passage", "Gardener Thorne",
                "Thorne's expression becomes guarded. \"The passages are old. Built during the border wars "
                "for escape routes. Most of the household has forgotten they exist. If someone is using them "
                "now...\" He lets the implication hang. \"It means they have knowledge that should not be "
                "common. Either they found the entrance by accident, or someone told them.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_cellar_noted", "Gardener Thorne",
                "\"Be careful down there, my lady. The cellar is damp and the stones are old. "
                "And whatever you find, remember that a cornered animal is the most dangerous.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_ivy", "Gardener Thorne",
                "\"The south wall ivy grows thick and provides cover over the lower windows. "
                "Someone cut it back at a very specific spot, right above the servants' quarters window.\" "
                "He raises an eyebrow. \"Anyone standing on the path at night could see directly into that "
                "room through the gap. Convenient if you wanted to observe the servants without being noticed.\"",
                {
                    {"Elena might be spying on the staff.", "thorne_spy_theory", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_spy_theory", "Gardener Thorne",
                "\"I did not say that, my lady.\" But his expression says he was thinking it. "
                "\"I merely report what the garden tells me. The ivy was cut with a small, sharp blade. "
                "Kitchen scissors, perhaps. Not garden shears. The angle is too precise for my tools.\" "
                "He pauses. \"Kitchen scissors would be easy enough to borrow from Chef Marcel's domain.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_guest_light", "Gardener Thorne",
                "\"The guest room faces the garden. I see the light when I make my late rounds, "
                "checking for frost damage.\" He shakes his head. \"Three, four in the morning sometimes. "
                "Whatever our guest is reading or writing, it consumes her attention completely. Once I saw "
                "her silhouette at the window, just standing there, looking out at the estate. Not moving. "
                "For a quarter hour at least.\"",
                {
                    {"Watching the estate... planning something?", "thorne_elena_planning", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_elena_planning", "Gardener Thorne",
                "\"Planning, remembering, longing, who can say.\" Thorne is careful with his words. "
                "\"But I will tell you this: in my experience, people who lose sleep are either haunted "
                "by the past or worried about the future. Either way, she is not as carefree as she "
                "appears in daylight.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_intro", "Gardener Thorne",
                "Thorne's eyes narrow. \"The passages beneath the estate are not common knowledge, "
                "my lady. How much do you know already?\"",
                {
                    {"I have heard rumors. Show me.", "thorne_hire_passage", [](const GameState &gs)
                     { return !gs.quest.secret_passage_known; },
                     {}},
                    {"You already showed me the entrance.", "thorne_passage_followup", [](const GameState &gs)
                     { return gs.quest.secret_passage_known; },
                     {}},
                    {"Never mind.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_hire_passage", "Gardener Thorne",
                "Thorne glances around carefully, ensuring no one is within earshot. \"I have maintained "
                "these grounds for decades, and in that time I have found things not on any blueprint. "
                "Beneath the cellar, there is a passage that leads outside the estate walls.\" He holds up "
                "a hand. \"This knowledge is dangerous, my lady. If the wrong person learned of it, "
                "the estate's security would be compromised. I would need compensation for the risk. "
                "Twenty-five gold, and I will show you the entrance myself.\"",
                {
                    {"Here is your gold. Show me.", "thorne_passage_reveal",
                     [](const GameState &gs)
                     { return gs.player.gold >= 25; },
                     [](GameState &gs)
                     {
                         gs.player.gold -= 25;
                         gs.quest.secret_passage_known = true;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"I do not have enough gold right now.", "thorne_passage_no_gold", nullptr, nullptr},
                    {"That seems steep for directions.", "thorne_passage_haggle", nullptr, nullptr},
                    {"Never mind.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_reveal", "Gardener Thorne",
                "Thorne pockets the gold with a practiced motion. \"Follow me at dusk. I will be "
                "near the cellar entrance, pretending to check the drainage stones.\" He lowers his voice "
                "further. \"The passage entrance is behind the third wine rack, the one that sits slightly "
                "crooked. Push the left side and it swings inward. The tunnel runs beneath the courtyard "
                "and exits through a storm drain near the outer wall.\" He pauses. \"One more thing. "
                "There are markings on the walls, old symbols from the border wars. Follow the ones shaped "
                "like arrows. The others lead to dead ends, or worse.\"",
                {
                    {"Worse?", "thorne_passage_danger", nullptr, nullptr},
                    {"Thank you, Thorne.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_danger", "Gardener Thorne",
                "\"Cave-ins, mostly. Some sections have not been maintained in a century. "
                "And there are rats the size of small cats down there.\" He almost smiles. "
                "\"Nothing a determined lady cannot handle, I am sure.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_no_gold", "Gardener Thorne",
                "\"I understand, my lady. The offer stands whenever you are ready. "
                "You know where to find me, same as always.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_haggle", "Gardener Thorne",
                "\"Steep?\" His expression hardens slightly. \"My lady, I am risking my position here. "
                "If the Duke learned I was revealing the estate's secrets, even to his daughter, "
                "I would be dismissed without reference. Twenty-five gold is the price of my silence "
                "and my service. No less.\"",
                {
                    {"Fine. Here is the gold.", "thorne_passage_reveal",
                     [](const GameState &gs)
                     { return gs.player.gold >= 25; },
                     [](GameState &gs)
                     {
                         gs.player.gold -= 25;
                         gs.quest.secret_passage_known = true;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"I will return when I have the funds.", "thorne_passage_no_gold", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_passage_followup", "Gardener Thorne",
                "\"Have you made use of it yet?\" He keeps his voice low. \"I check the entrance "
                "weekly. No one else has been through, as far as I can tell. The dust was only disturbed "
                "where I showed you.\" He pauses. \"Though I found something odd last time. A scrap of "
                "fabric caught on a stone near the tunnel exit. Fine cloth, not servant-wear. "
                "Someone else may know about the passage after all.\"",
                {
                    {"What color was the fabric?", "thorne_fabric_clue", nullptr, nullptr},
                    {"Can you seal the exit?", "thorne_seal_exit", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_fabric_clue", "Gardener Thorne",
                "\"Pale blue. The kind of fabric you would find in a lady's dress, not a servant's "
                "uniform.\" He lets that sink in. \"I kept the scrap, if you want to examine it. "
                "But I think we both know whose wardrobe favors that shade of blue.\"",
                {
                    {"Elena.", "thorne_fabric_elena", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_fabric_elena", "Gardener Thorne",
                "\"I said no names.\" But his silence confirms it. \"If she knows about the passage, "
                "it means someone told her, or she found the entrance on her own. Either way, "
                "the estate is less secure than we thought. You may want to speak with Captain Roderick "
                "about increasing patrols near the cellar.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_seal_exit", "Gardener Thorne",
                "\"I could collapse the exit with a few well-placed stones. But that would trap anyone "
                "currently inside and remove your own escape route.\" He considers. \"A better option "
                "might be a simple alarm. A few clay pots balanced on a wire. Anyone passing through "
                "would knock them over, and I would hear it from the garden shed.\"",
                {
                    {"Set up the alarm.", "thorne_alarm_set", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Leave it for now.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_alarm_set", "Gardener Thorne",
                "\"Consider it done. I will set it up tonight.\" He nods firmly. \"If anything "
                "triggers it, I will leave a marker for you in the garden, a red ribbon on the "
                "gate post. Check for it each morning.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_backstory", "Gardener Thorne",
                "Thorne is quiet for a long moment, as if deciding how much to share. "
                "\"I came to the Aldric estate thirty years ago, when your grandfather was still Duke. "
                "Before that, I was a forester in the Thornwall region, near the northern border.\" "
                "He pulls a weed with more force than necessary. \"The border wars changed everything. "
                "My village was burned. My family... did not survive the winter that followed.\"",
                {
                    {"I am sorry, Thorne.", "thorne_past_sympathy", nullptr, nullptr},
                    {"How did you end up here?", "thorne_how_arrived", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_past_sympathy", "Gardener Thorne",
                "\"It was long ago, my lady. The grief has become... manageable. Like an old wound "
                "that aches in cold weather but no longer bleeds.\" He looks across the garden. "
                "\"This place gave me purpose again. Your grandfather hired me on the spot when I "
                "arrived half-starved at the gate. Said he could tell a man who understood growing things "
                "just by looking at his hands.\" He flexes his scarred, soil-dark fingers. \"He was right.\"",
                {
                    {"My grandfather sounds like he was a good man.", "thorne_grandfather", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 10;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_grandfather", "Gardener Thorne",
                "\"The best I have ever known.\" There is no hesitation. \"He understood that strength "
                "is not just in swords and edicts. It is in patience, in tending what matters, in "
                "knowing when to prune and when to let things grow.\" He meets your eyes. \"You remind "
                "me of him sometimes, my lady. More than your father does, truth be told. Though perhaps "
                "that is not my place to say.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_how_arrived", "Gardener Thorne",
                "\"I walked south for three weeks after the fires. No money, no destination. "
                "Just putting distance between myself and the ashes.\" He speaks matter-of-factly, "
                "without self-pity. \"I passed through the capital, but it was too crowded, too loud. "
                "Then I saw the Aldric estate from the road, and the gardens caught my eye even from "
                "a distance. Something growing. Something alive.\" He shrugs. \"I asked for work. "
                "Your grandfather gave me a home instead.\"",
                {
                    {"You have been loyal ever since.", "thorne_loyalty", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_loyalty", "Gardener Thorne",
                "\"Loyalty is easy when it is earned, my lady. The Aldric family gave me everything "
                "when I had nothing. This garden is my life's work, and this estate is the only home "
                "I have known for three decades.\" His jaw tightens. \"Which is why I do not take kindly "
                "to outsiders who threaten it. No matter how charming they may appear.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_herbs", "Gardener Thorne",
                "Thorne's eyes brighten, the closest to enthusiasm you have seen from him. "
                "\"Now that is a subject worth discussing. The herb garden behind the kitchen is "
                "my pride.\" He gestures toward the back of the estate. \"Lavender for calming draughts. "
                "Chamomile for sleep. Rosemary for memory and focus. Mint for digestion.\"",
                {
                    {"What about dangerous plants?", "thorne_dangerous_plants", nullptr, nullptr},
                    {"Could you make me a calming draught?", "thorne_calming", nullptr, nullptr},
                    {"What grows in the cellar?", "thorne_cellar_plants", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_dangerous_plants", "Gardener Thorne",
                "His expression becomes guarded again. \"Every gardener knows what kills as well as "
                "what heals, my lady. Foxglove grows along the south wall, beautiful but deadly if "
                "mishandled. Nightshade in the shaded corner near the cellar, I keep it for pest control. "
                "And there is monkshood in the wild section, the purple flowers that look so inviting.\" "
                "He fixes you with a steady look. \"I trust you are asking out of academic interest.\"",
                {
                    {"Of course. Purely academic.", "thorne_academic", nullptr, nullptr},
                    {"What if I needed something... specific?", "thorne_specific_request", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_academic", "Gardener Thorne",
                "\"Good.\" He does not entirely believe you, but he respects the answer. "
                "\"Knowledge of what is dangerous keeps us safe. The same foxglove that stops a heart "
                "can, in tiny doses, regulate one. It is all about intent and measure.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_specific_request", "Gardener Thorne",
                "Thorne goes very still. Then he looks around carefully. \"I do not ask why, my lady. "
                "But if you ever need a preparation, you come to me directly. Not to Chef Marcel, "
                "whose hands are steady with a knife but clumsy with plants. Not from books, which leave "
                "trails of their own.\" He lowers his voice to barely a whisper. \"A gardener's knowledge "
                "leaves no paper trail. Remember that.\"",
                {
                    {"I understand.", "thorne_root", nullptr, [](GameState &gs)
                     {
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_calming", "Gardener Thorne",
                "\"Easily done. Lavender and chamomile steeped in hot water with a drop of honey. "
                "I will leave a pouch of dried herbs at the kitchen door for you.\" He chuckles, "
                "a rare sound. \"Better than anything the apothecary sells, and half the price, "
                "which is to say, free.\"",
                {
                    {"Thank you, Thorne.", "thorne_root", nullptr, [](GameState &gs)
                     {
                         gs.player.energy = std::min(gs.player.energy + 5, 100);
                     }},
                },
                false);

        addNode(state, "thorne_cellar_plants", "Gardener Thorne",
                "\"Mushrooms, mostly. Some useful, some distinctly not. There is a colony of white "
                "cave mushrooms near the back wall that are edible and nutritious. But the dark ones "
                "with red spots along the passage entrance will make you violently ill.\" He frowns. "
                "\"I noticed someone has been harvesting the white ones recently. Small amounts, "
                "carefully picked. Not a rat's work, too precise.\"",
                {
                    {"Someone is going into the cellar for mushrooms?", "thorne_cellar_mushroom_thief", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_cellar_mushroom_thief", "Gardener Thorne",
                "\"Or using the mushroom-picking as cover for visiting the cellar regularly without "
                "raising suspicion.\" He taps his temple. \"Think about it, my lady. If someone caught "
                "you in the cellar, you hold up a basket of mushrooms and say you were gathering "
                "ingredients for Chef Marcel. Simple, believable. No one questions it.\"",
                {
                    {"Clever.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_hire", "Gardener Thorne",
                "Thorne straightens up, wiping his hands on his apron. \"I am a gardener, not a spy "
                "or a soldier. But I see things others miss, and I can move through the grounds "
                "without drawing attention.\" He tilts his head. \"What did you have in mind?\"",
                {
                    {"Watch Elena's movements in the gardens.", "thorne_hire_watch",
                     [](const GameState &gs)
                     { return gs.player.gold >= 15; },
                     [](GameState &gs)
                     {
                         gs.player.gold -= 15;
                         for (auto &n : gs.npcs)
                         {
                             if (n.second.id == "gardener_thorne")
                             {
                                 n.second.affection += 5;
                                 break;
                             }
                         }
                     }},
                    {"Show me the secret passage. (25 gold)", "thorne_hire_passage", [](const GameState &gs)
                     {
                         return gs.player.gold >= 25 && !gs.quest.secret_passage_known;
                     },
                     {}},
                    {"Prepare something from the dangerous plants.", "thorne_hire_poison", [](const GameState &gs)
                     { return gs.player.gold >= 30; }, [](GameState &gs)
                     {
                    gs.player.gold -= 30;
                    gs.quest.acquired_poison = true;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "gardener_thorne") {
                            n.second.suspicion += 15;
                            break;
                        }
                    } }},
                    {"Plant evidence in the garden shed.", "thorne_hire_evidence", [](const GameState &gs)
                     { return gs.player.gold >= 20; }, [](GameState &gs)
                     {
                    gs.player.gold -= 20;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "gardener_thorne") {
                            n.second.affection += 5;
                            break;
                        }
                    } }},
                    {"Never mind.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_hire_watch", "Gardener Thorne",
                "Thorne nods, pocketing the fifteen gold discreetly. \"I will keep to my usual rounds "
                "but pay particular attention to her movements near the garden. Dawn visits, evening "
                "walks, anyone she meets among the hedgerows.\" He pauses. \"Give me a few days. "
                "I will report what I find next time we speak.\"",
                {
                    {"Good. Be discreet.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_hire_poison", "Gardener Thorne",
                "Thorne goes very still. For a long moment, he says nothing, his eyes searching yours. "
                "Then he speaks, barely above a whisper. \"You understand what you are asking, my lady. "
                "This is not a calming draught.\" He takes the gold slowly. \"I will prepare something. "
                "You will find a small vial wrapped in burlap beneath the third stepping stone "
                "by the herb garden. Tomorrow morning, before dawn.\" His expression is troubled. "
                "\"I do this out of loyalty to this house. Do not make me regret it.\"",
                {
                    {"You have my word.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_hire_evidence", "Gardener Thorne",
                "\"The garden shed is my domain. No one else goes in there.\" He considers. "
                "\"I can place whatever you need among the tools and supplies. If someone were to "
                "search it, perhaps acting on a tip, they would find items that should not be there.\" "
                "He takes the gold. \"What exactly do you want found, and who do you want it blamed on?\"",
                {
                    {"Letters implicating Elena in conspiracy.", "thorne_evidence_letters", nullptr, nullptr},
                    {"Stolen items from the estate.", "thorne_evidence_stolen", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_evidence_letters", "Gardener Thorne",
                "\"Forged correspondence? That is Clara's specialty more than mine.\" He scratches "
                "his chin. \"But I can place them convincingly. A bundle of letters hidden beneath "
                "a loose floorboard, as if someone stashed them in haste.\" He nods. \"It will be done. "
                "Just make sure the right person comes looking at the right time.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_evidence_stolen", "Gardener Thorne",
                "\"Easier done. A silver candlestick, a jeweled hairpin, small things that would be "
                "missed but not immediately. I can arrange it so the items appear to have been hidden "
                "among the gardening supplies.\" He pauses. \"If Captain Roderick conducts a search "
                "and finds estate valuables hidden in the shed, it would be damning for anyone who "
                "has been seen frequenting the gardens.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_post_expulsion", "Gardener Thorne",
                "Thorne leans on his spade, looking out over the gardens with something close to relief. "
                "\"Quieter now. The dawn visits have stopped, obviously. The east wall roses are "
                "untouched for the first time in weeks.\" He turns to you. \"The grounds feel like they "
                "belong to the estate again, if you take my meaning. Whatever you did, my lady, "
                "the garden thanks you for it.\" He hesitates. \"Though I notice the staff are uneasy. "
                "An expulsion is dramatic. People talk. They wonder who might be next.\"",
                {
                    {"Let them wonder. It keeps people honest.", "thorne_post_exp_fear", nullptr, nullptr},
                    {"I did what was necessary.", "thorne_post_exp_necessary", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_post_exp_fear", "Gardener Thorne",
                "\"Fear is a gardener's tool as well, my lady. A scarecrow keeps the crows away, "
                "but only until they realize it cannot actually move.\" He gives you a meaningful look. "
                "\"Make sure your next actions match the impression. Otherwise, the crows come back "
                "bolder than before.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_post_exp_necessary", "Gardener Thorne",
                "\"I believe you, my lady. And the garden agrees, in its silent way.\" He returns to "
                "his work. \"If you need anything else tended, cut, or uprooted, you know where to find me.\"",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_post_death", "Gardener Thorne",
                "Thorne's face is ashen. He grips his spade tightly, knuckles white. \"I have seen "
                "death before, my lady. In the border wars, in the hard winters. But here, in this "
                "garden...\" He swallows. \"The ground remembers what is planted in it. Blood does not "
                "wash away as easily as people think.\" He looks at you with an expression you cannot "
                "quite read. \"I will tend the grounds as I always have. Whatever happened, the garden "
                "is innocent.\"",
                {
                    {"You saw nothing, Thorne.", "thorne_death_silence", nullptr, nullptr},
                    {"It was an accident.", "thorne_death_accident", nullptr, nullptr},
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_death_silence", "Gardener Thorne",
                "He holds your gaze for a long, uncomfortable moment. \"I am a gardener, my lady. "
                "I see roots and leaves and the turning of seasons. I do not see what happens between "
                "people in the dark.\" It is not agreement. It is not refusal. It is the careful neutrality "
                "of a man who has survived by knowing when to speak and when to let the earth cover "
                "what lies beneath.",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_death_accident", "Gardener Thorne",
                "\"Accidents happen in old estates, my lady. Uneven stones, steep stairs, "
                "damp cellars.\" His tone is flat. \"I have said this before and I will say it again: "
                "a gardener tends what is alive and buries what is dead. That is the natural order.\" "
                "He drives his spade into the earth with finality.",
                {
                    {"Back to other matters.", "thorne_root", nullptr, nullptr},
                },
                false);

        addNode(state, "thorne_farewell", "Gardener Thorne",
                "Thorne touches the brim of his hat. \"The garden keeps its own hours, my lady. "
                "You will find me here whenever you need.\"",
                {}, true);
    }

}

void registerGardenerThorne(GameState &state)
{
    NPC n;
    n.id = "gardener_thorne";
    n.name = "Gardener Thorne";
    n.title = "Head Gardener";
    n.description = "A weathered, secretive old gardener who has tended the estate for thirty\n"
                    "years. He knows every path, every passage, every secret the grounds hold.";
    n.current_room = "garden";
    n.affection = 35;
    n.suspicion = 10;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "thorne_root";
    n.traits = {Trait::Secretive, Trait::EarlyBird, Trait::Perceptive};
    n.hireable = true;
    n.hire_cost = 25;
    n.schedule = {
        {5, "garden"},
        {8, "kitchen"},
        {9, "garden"},
        {12, "servants_quarters"},
        {13, "garden"},
        {15, "cellar"},
        {16, "garden"},
        {19, "servants_quarters"},
        {20, "garden"},
    };
    n.associates = {"butler_graves", "maid_clara", "chef_marcel", "captain_roderick"};
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildThorneDialogue(state);
}