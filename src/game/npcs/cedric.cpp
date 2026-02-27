#include "game.hpp"
#include "game/dialogue_helpers.hpp"

namespace game::npcs
{

void buildCedricDialogue(GameState& state)
{
    addNode(state, "cedric_root", "Lord Cedric",
        "Cedric stands by the window, his riding boots still dusty from the morning patrol. "
        "He turns as you enter, his expression shifting from distant thought to brotherly warmth. "
        "\"Seraphina. I was hoping you would come by. There is much on my mind.\"",
        {
            {"What is troubling you?", "cedric_troubled", nullptr, nullptr},
            {"I want to talk about Elena.", "cedric_elena", nullptr, nullptr},
            {"I need your help, brother.", "cedric_help", nullptr, nullptr},
            {"Tell me what you have been doing.", "cedric_daily", nullptr, nullptr},
            {"I want to talk about Father.", "cedric_father", nullptr, nullptr},
            {"How is Rosalind?", "cedric_rosalind", nullptr, nullptr},
            {"[Alliance formed] About our plans...", "cedric_alliance_plans",
                [](const GameState& gs) { return gs.quest.cedric_alliance; }, nullptr},
            {"[After Elena's expulsion] We did it.", "cedric_post_expulsion",
                [](const GameState& gs) { return gs.quest.elena_expelled; }, nullptr},
            {"[After body discovered] Cedric, something terrible happened.", "cedric_post_death",
                [](const GameState& gs) { return gs.quest.body_discovered; }, nullptr},
            {"I should go.", "cedric_farewell", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_troubled", "Lord Cedric",
        "Cedric runs a hand through his hair, a gesture he makes only when genuinely worried. "
        "\"Several things. Father has been distant, more than usual. He locks himself in the study "
        "for hours and will not say what occupies him.\" He moves to the desk, picking up a letter. "
        "\"And I intercepted this at the gate, addressed to our guest from someone in the capital. "
        "The seal is unfamiliar, a flower of some kind.\" He sets it down. \"I did not open it. "
        "That feels like a line I should not cross alone.\"",
        {
            {"Open it. We need to know.", "cedric_open_letter", nullptr, nullptr},
            {"You are right not to open it. But keep it safe.", "cedric_keep_letter", nullptr, nullptr},
            {"A flower seal... I have heard of this.", "cedric_iris_mention",
                [](const GameState& gs) { return gs.quest.elena_letters_found; }, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_open_letter", "Lord Cedric",
        "Cedric breaks the seal carefully, his brow furrowed as he reads. \"It is... coded. "
        "Most of it is pleasantries, innocuous on the surface. But there are phrases that do not "
        "fit natural conversation. 'The garden blooms in the third season.' 'The eastern wall "
        "catches the best light.'\" He looks up. \"This is intelligence communication, Seraphina. "
        "Someone is sending Elena information about our estate using coded language.\"",
        {
            {"We need to decode the rest.", "cedric_decode", nullptr, nullptr},
            {"This proves she is a spy.", "cedric_spy_confirm", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_decode", "Lord Cedric",
        "\"I studied cipher work at the academy, though I am no expert.\" He spreads the letter "
        "on the desk. \"'Third season' could mean autumn, or the third month of her stay. "
        "'Eastern wall' matches the rose garden, which Thorne mentioned she visits at dawn.\" "
        "He frowns. \"There is a signature: 'Your faithful Iris.' Not a name, I think. A code "
        "name or an organization.\" He looks at you. \"We should show this to Father. Or... "
        "we keep it as leverage.\"",
        {
            {"Show Father.", "cedric_decode_father", nullptr,
                [](GameState& gs) {
                    gs.quest.duke_suspicious_elena = true;
                }},
            {"Keep it. We may need it later.", "cedric_decode_keep", nullptr,
                [](GameState& gs) {
                    gs.quest.elena_letters_found = true;
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_decode_father", "Lord Cedric",
        "\"I agree. Father needs to see this. He may understand more of the cipher than we do, "
        "he spent years in court politics before retreating to the estate.\" Cedric folds the letter "
        "carefully. \"I will present it to him tonight. If this is what I think it is, Elena's "
        "time as a guest under this roof is ending.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_decode_keep", "Lord Cedric",
        "Cedric hesitates, then nods slowly. \"You are thinking strategically. I trust your "
        "judgment, sister.\" He locks the letter in his desk drawer. \"But we cannot hold this "
        "indefinitely. If Elena discovers we have her correspondence, she will become desperate. "
        "And desperate people are dangerous.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_keep_letter", "Lord Cedric",
        "\"I will lock it in my desk. No one has the key but me.\" He tucks the letter away. "
        "\"But Seraphina, if there are more like this, we need a strategy. One intercepted letter "
        "is a curiosity. A pattern of them is evidence.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_iris_mention", "Lord Cedric",
        "Cedric's expression sharpens. \"You know about this? The Iris Consortium?\" He sits "
        "heavily in his chair. \"Then it is worse than I thought. I heard rumors at the academy "
        "about a network operating across provinces, placing agents in noble households. "
        "If Elena is one of theirs...\" He trails off. \"Seraphina, this is not just about our "
        "family's reputation. This is about political manipulation at a level that could affect "
        "the entire region.\"",
        {
            {"We need to act carefully.", "cedric_root", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_spy_confirm", "Lord Cedric",
        "\"A spy. Yes.\" Cedric's voice is tight with controlled anger. \"I wanted to give her "
        "the benefit of doubt. A charming commoner who caught the Prince's eye, perhaps genuinely. "
        "But this...\" He gestures at the letter. \"This is professional. Organized. She is not "
        "here by accident, and she is not here for love or social advancement alone.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena", "Lord Cedric",
        "Cedric's expression becomes guarded, complex. \"Elena. Yes.\" He pauses longer than "
        "usual. \"I will be honest with you, Seraphina, even though it may not be what you want "
        "to hear.\" He turns from the window. \"She is not what she appears. I am certain of that. "
        "But neither is she entirely the villain you may want her to be.\" He crosses his arms. "
        "\"I have watched her carefully. She is intelligent, driven, and calculating. But I have "
        "also seen her with Rosalind, teaching her to make flower crowns with genuine patience. "
        "And I saw her help a servant who tripped on the stairs, without anyone watching.\"",
        {
            {"You are defending her?", "cedric_elena_defend", nullptr, nullptr},
            {"Charm is a weapon, Cedric.", "cedric_elena_weapon", nullptr, nullptr},
            {"Have you spoken with her directly?", "cedric_elena_direct", nullptr, nullptr},
            {"She is dangerous to this family.", "cedric_elena_dangerous", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_defend", "Lord Cedric",
        "\"Not defending. Understanding.\" He meets your eyes steadily. \"If we treat her as "
        "purely evil, we underestimate her. She is a person with goals, some of which may conflict "
        "with ours and some of which may be legitimate.\" He steps closer, lowering his voice. "
        "\"That said, I am your brother first and foremost. Whatever you decide to do about Elena, "
        "I stand with you. But I want you to decide with clear eyes, not clouded by anger or fear.\"",
        {
            {"You are right. I need to think clearly.", "cedric_elena_clear", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"My eyes are clear. She needs to go.", "cedric_elena_go", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_clear", "Lord Cedric",
        "Cedric places a hand briefly on your shoulder. \"That is the sister I know. The one "
        "who thinks before she strikes.\" His expression is warm. \"Whatever comes next, we face "
        "it together. As Aldrics.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_go", "Lord Cedric",
        "\"Then we make it happen. Properly, with evidence and justification, so that Father "
        "supports the decision and no one can claim we acted out of petty jealousy.\" His jaw "
        "sets. \"We need something concrete, Seraphina. Rumors and suspicion are not enough for "
        "Father. He will want proof.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_weapon", "Lord Cedric",
        "\"I know it is. I trained in combat, remember? I know that the deadliest strikes are "
        "the ones that look like a friendly gesture.\" His eyes narrow. \"But a weapon is only "
        "dangerous if you do not see it coming. And I see her, Seraphina. I see exactly what she "
        "is doing.\" He lowers his voice. \"The question is what she does not want us to see. "
        "The charm is a performance. What is happening behind it?\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_direct", "Lord Cedric",
        "\"Once, in the library. She was reading a history of the province's noble families.\" "
        "He frowns. \"We spoke about the books. She was knowledgeable, surprisingly so for someone "
        "of her claimed background. She asked about the Aldric lineage, specifically about "
        "alliances formed during the border wars.\" His expression darkens. \"At the time, I "
        "thought it was intellectual curiosity. Now I wonder if she was mapping our political "
        "connections.\"",
        {
            {"She is gathering intelligence.", "cedric_root", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_elena_dangerous", "Lord Cedric",
        "\"Yes. She is.\" There is no disagreement in his voice. \"Not in an obvious way. "
        "She will not attack us with swords or poison, at least, I hope not. Her danger is "
        "more insidious. She changes people's perceptions. She makes them question loyalties "
        "they have held for years.\" He looks at the family portrait on the wall. \"She makes "
        "them wonder if the Aldric family truly deserves the power it holds. And once that doubt "
        "takes root, it spreads like ivy across stone.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_help", "Lord Cedric",
        "Cedric straightens, the protective instinct in him responding immediately. \"Name it. "
        "Whatever you need, I am here.\"",
        {
            {"Cover for me if things get complicated.", "cedric_help_cover", nullptr,
                [](GameState& gs) {
                    gs.player.suspicion = std::max(gs.player.suspicion - 10, 0);
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Form an alliance with me against Elena.", "cedric_help_alliance",
                [](const GameState& gs) {
                    for (const auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            return n.second.affection >= 60 && !gs.quest.cedric_alliance;
                        }
                    }
                    return false;
                },
                [](GameState& gs) {
                    gs.quest.cedric_alliance = true;
                    gs.player.reputation += 10;
                    gs.heroine_popularity -= 5;
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 15;
                            break;
                        }
                    }
                }},
            {"Talk to Father on my behalf.", "cedric_help_father", nullptr, nullptr},
            {"Watch Elena's movements for me.", "cedric_help_watch", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_help_cover", "Lord Cedric",
        "\"Of course. If anyone asks where you were, when you were, or what you were doing, "
        "I will provide whatever story is needed.\" His expression is serious. \"I will say you "
        "were with me, reviewing estate accounts or riding the perimeter. No one questions a "
        "brother and sister spending time together.\" He pauses. \"But Seraphina, please, "
        "tell me if things are escalating. I can cover for minor things, but if it becomes "
        "serious, I need to know before it spirals.\"",
        {
            {"I will keep you informed.", "cedric_root", nullptr, nullptr},
            {"The less you know, the safer you are.", "cedric_cover_ignorance", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_cover_ignorance", "Lord Cedric",
        "\"Do not do that.\" His voice sharpens. \"Do not shut me out for my own protection. "
        "I am not Rosalind. I can handle difficult truths.\" He softens. \"We are stronger "
        "together than apart, sister. Whatever you are planning, two minds are better than one.\"",
        {
            {"You are right. I will tell you everything.", "cedric_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_help_alliance", "Lord Cedric",
        "Cedric takes a long breath, then extends his hand. \"An alliance. Between us, formally.\" "
        "His grip is firm when you shake. \"This means I commit fully. My reputation, my influence "
        "with Father, my connections from the academy, all in service of protecting this family "
        "from Elena's machinations.\" His eyes are intense. \"But I have one condition: we do not "
        "cross certain lines. No murder, no framing for crimes she did not commit. We expose the "
        "truth and let it do the work. Agreed?\"",
        {
            {"Agreed. Truth is enough.", "cedric_alliance_agreed", nullptr, nullptr},
            {"I cannot promise that.", "cedric_alliance_reluctant", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_alliance_agreed", "Lord Cedric",
        "\"Good.\" Relief and determination mingle in his expression. \"Then here is what I "
        "propose: I will use my access to Father's study to review Elena's original introduction "
        "letter. If her references are fabricated, we have grounds for a formal inquiry. "
        "Meanwhile, you work the household, gather what the servants know, what Thorne has seen "
        "in the garden, what Clara has heard in the corridors.\" He nods firmly. \"We build an "
        "irrefutable case. And we present it to Father together.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_alliance_reluctant", "Lord Cedric",
        "Cedric's expression cools slightly. \"Then we have a problem, sister. I will not be "
        "party to something that dishonors this family, even if it removes Elena.\" He does not "
        "withdraw his hand but his grip loosens. \"I stand with you. But there are things I will "
        "not stand for. Keep me informed, and I will trust your judgment. Cross the line, and I "
        "will stand aside.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_help_father", "Lord Cedric",
        "\"I can speak to Father, yes. But you should know, he has been... receptive to Elena "
        "recently. She complimented his library and asked about the family archives. Father does "
        "not often find people interested in history, and Elena pressed exactly the right buttons.\" "
        "He sighs. \"I will frame my concerns carefully. Focus on security, on the unusual "
        "correspondence, on Roderick's increased patrols. Father responds to facts, not feelings.\"",
        {
            {"Do you think he will listen?", "cedric_father_listen", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father_listen", "Lord Cedric",
        "\"He will listen to me. He always has.\" Cedric's confidence is quiet but real. "
        "\"Father may be charmed by Elena's attention, but he is not a fool. If I present "
        "concrete concerns, he will investigate. He did not maintain this family's position "
        "for decades by ignoring threats.\" He pauses. \"But timing matters. If I approach him "
        "while he is already suspicious, the impact doubles. If I come too early, he may dismiss "
        "it as jealousy or overprotectiveness.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_help_watch", "Lord Cedric",
        "\"I already watch her more than is probably healthy.\" He catches himself and clears "
        "his throat. \"From a security standpoint. She takes walks in the garden at unusual hours, "
        "she reads in the library well past midnight, and she has been seen near the servants' "
        "quarters speaking with the younger staff.\" He frowns. \"I will be more systematic about "
        "it. Morning and evening, I will note her location and who she interacts with. If there "
        "is a pattern, I will find it.\"",
        {
            {"Thank you, brother.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_daily", "Lord Cedric",
        "\"The usual, mostly. Morning ride along the estate perimeter. I checked the boundary "
        "walls, the gate, the south road.\" He leans against the desk. \"I also visited the "
        "village briefly. The mood there is... interesting. Elena's reputation has spread beyond "
        "the estate. The villagers speak of a 'kind lady' who has arrived at the Duke's residence. "
        "Some are saying she is a sign of change, that the old noble ways are softening.\"",
        {
            {"Her influence is spreading that far?", "cedric_village_influence", nullptr, nullptr},
            {"What do the villagers think of our family?", "cedric_village_aldric", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_village_influence", "Lord Cedric",
        "\"Faster than you would think. The servants talk, the merchants carry stories, and "
        "before you know it, a commoner guest at the Duke's table becomes folk legend.\" "
        "He sounds frustrated. \"It is a narrative that works against us, Seraphina. A kind "
        "commoner versus a noble family. People love that story. It does not matter if it is "
        "true, it matters that it is compelling.\"",
        {
            {"We need to control the narrative.", "cedric_narrative", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_narrative", "Lord Cedric",
        "\"Exactly. We need the villagers to see our family as generous and just, not as "
        "oppressors threatened by a kind girl.\" He thinks. \"Charitable acts, visible ones. "
        "A donation to the village school. Free grain from our stores. It is politics, not "
        "generosity, but it works.\" He meets your eyes. \"Father would approve, if framed "
        "properly. It strengthens our position while undermining Elena's 'common touch' narrative.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_village_aldric", "Lord Cedric",
        "\"Respect, mostly. Father is fair in his taxation and quick to respond to complaints. "
        "That earns loyalty.\" He crosses his arms. \"But there is always an undercurrent. "
        "Nobility is inherently resented by those who do not possess it. Elena taps into that "
        "resentment simply by existing, a commoner welcomed into noble circles. To the villagers, "
        "she represents possibility. To us, she represents disruption.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father", "Lord Cedric",
        "Cedric's expression becomes complicated. \"Father is... Father. He carries the weight "
        "of this family and the province on his shoulders, and he does so largely alone since "
        "Mother died.\" He looks at the family portrait. \"He is stern because he must be. "
        "But I remember when he would read us stories by the fire, before the responsibilities "
        "consumed him.\"",
        {
            {"Does he ever talk about Mother?", "cedric_father_mother", nullptr, nullptr},
            {"Is he handling the Elena situation well?", "cedric_father_elena", nullptr, nullptr},
            {"He has been distant with me.", "cedric_father_distant", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father_mother", "Lord Cedric",
        "\"Rarely. And only when he has had too much wine, which is to say, almost never.\" "
        "Cedric's voice drops. \"But I hear him sometimes, late at night, in the study. Speaking "
        "to her portrait as if she might answer.\" He swallows. \"He loved her completely, "
        "Seraphina. And when she died, something in him closed off that has never reopened. "
        "He pours everything into the estate and into duty because if he stopped, even for a "
        "moment, I think the grief would swallow him.\"",
        {
            {"I wish I could help him.", "cedric_father_help", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father_help", "Lord Cedric",
        "\"You help him by being here. By being strong. By protecting this family.\" Cedric's "
        "eyes are bright. \"He may not say it, he may never say it, but he needs you, Seraphina. "
        "Both of us. Rosalind's innocence reminds him of better days, your determination reminds "
        "him of Mother, and my duty reminds him of himself.\" He manages a half-smile. "
        "\"We are all he has left, and he would burn the province to keep us safe.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father_elena", "Lord Cedric",
        "\"Honestly? No.\" Cedric is blunt. \"He is treating her as a guest rather than a threat, "
        "which is either diplomacy or denial. She has found exactly the approach that works on him: "
        "intellectual respect and genuine interest in his work.\" He shakes his head. \"Father has "
        "always been susceptible to anyone who engages with his mind. Mother was the one who read "
        "people's hearts. Without her, he sees what is presented and trusts it.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_father_distant", "Lord Cedric",
        "\"He has been distant with everyone, not just you.\" Cedric's tone is gentle. \"Do not "
        "take it personally, Seraphina. He is processing. Elena's presence has stirred something "
        "in the household dynamic, and Father responds to change by retreating into analysis.\" "
        "He pauses. \"Give him facts, not feelings. That is the key to Father. Show him evidence "
        "of a problem and he will act. Express concern without proof and he will dismiss it "
        "as emotion.\"",
        {
            {"That is good advice.", "cedric_root", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_rosalind", "Lord Cedric",
        "Cedric's expression softens completely. \"Our little sister. She is too good for this "
        "world, Seraphina.\" He sighs. \"She has been spending time with Elena, which worries me. "
        "Elena fills her head with stories about the outside world, about adventure and freedom. "
        "Rosalind is impressionable, and Elena knows exactly which strings to pull.\"",
        {
            {"Should we keep them apart?", "cedric_rosalind_apart", nullptr, nullptr},
            {"Rosalind is stronger than you think.", "cedric_rosalind_strong", nullptr, nullptr},
            {"Elena is using Rosalind to get to us.", "cedric_rosalind_used", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_rosalind_apart", "Lord Cedric",
        "\"I have considered it. But forbidding contact would only make Rosalind more curious. "
        "Forbidden fruit and all that.\" He runs a hand through his hair. \"Better to guide her "
        "understanding. Talk to her about Elena, not to poison her opinion, but to sharpen her "
        "perception. Teach her to see the strategy behind the kindness.\" He pauses. \"Or we "
        "simply ensure that Rosalind has better company and more interesting activities so that "
        "Elena's attention becomes less appealing by comparison.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_rosalind_strong", "Lord Cedric",
        "\"Is she?\" Genuine hope mixes with doubt. \"I want to believe that. She is perceptive "
        "in her own way, I grant you. She notices things that adults miss because she does not "
        "filter her observations through expectation.\" He almost smiles. \"She told me last "
        "week that Elena 'tries too hard to be liked, like a puppy that has been kicked before.' "
        "That is more insightful than anything Roderick has said about our guest.\"",
        {
            {"See? She is wiser than we give her credit for.", "cedric_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 5;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_rosalind_used", "Lord Cedric",
        "\"That is exactly what worries me.\" Cedric's protective instinct flares. \"Rosalind "
        "is the family's emotional center. If Elena influences her deeply enough, she becomes "
        "leverage, a voice inside the family advocating for Elena's interests without even "
        "realizing it.\" His fists clench briefly. \"I will not allow our sister to be used "
        "as a pawn. Not by Elena, not by anyone.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_alliance_plans", "Lord Cedric",
        "Cedric moves to the desk and spreads a rough map he has made of the estate and "
        "surrounding area. \"I have been thinking about our next moves.\" His voice is low "
        "and focused. \"We need to approach this from multiple angles: evidence, reputation, "
        "and timing.\"",
        {
            {"What evidence do we have so far?", "cedric_plan_evidence", nullptr, nullptr},
            {"When should we make our move?", "cedric_plan_timing", nullptr, nullptr},
            {"Who else can we trust?", "cedric_plan_allies", nullptr, nullptr},
            {"What is our endgame?", "cedric_plan_endgame", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_plan_evidence", "Lord Cedric",
        "\"The intercepted correspondence with the Iris seal. The unusual night movements "
        "documented by Graves and Thorne. The intelligence-gathering questions she has asked "
        "the staff and family members.\" He ticks them off on his fingers. \"Individually, "
        "each could be explained innocently. Together, they form a pattern of systematic "
        "infiltration.\" He taps the desk. \"But Father will want something definitive. "
        "A confession, a caught-in-the-act moment, or documentary proof of her receiving "
        "instructions from an outside organization.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_plan_timing", "Lord Cedric",
        "\"The Royal Ball is approaching. Elena will expect an invitation. If we move before "
        "the ball, we prevent her from making connections with other noble families.\" He traces "
        "a line on his rough map. \"If we wait until after, we risk her expanding her influence "
        "beyond our walls.\" He looks up. \"My recommendation: present our evidence to Father "
        "within the week. Give him time to verify and act before the ball. A Duke who expels a "
        "guest months before a social event is being cautious. One who does it the night before "
        "looks desperate.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_plan_allies", "Lord Cedric",
        "\"Graves is reliable, his loyalty is absolute. Clara is useful but needs management. "
        "Roderick is a soldier, give him a clear order and he will execute it.\" He considers. "
        "\"Thorne is an unknown, loyal to the estate but independent in his thinking. Marcel "
        "follows gold and self-interest, useful but not trustworthy.\" He meets your eyes. "
        "\"Rosalind is too young to involve directly. Father will be our most important ally "
        "when the time comes, but we cannot approach him prematurely.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_plan_endgame", "Lord Cedric",
        "\"Elena leaves the estate, discredited and without the connections she came here to "
        "build. The family's reputation is maintained or strengthened. Rosalind is safe. "
        "Father's political position is secure.\" He pauses. \"That is the clean outcome. "
        "The messy outcome is that Elena fights back, leverages whatever intelligence she has "
        "gathered, and drags the Aldric name through public scandal.\" His jaw tightens. "
        "\"We need to ensure she leaves with nothing worth using against us.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_post_expulsion", "Lord Cedric",
        "Cedric exhales slowly, as if releasing a breath he has held for weeks. \"We did it. "
        "She is gone.\" He sits heavily in his chair. \"I should feel relieved. I do feel "
        "relieved. But there is something else too.\" He stares at the desk where the intercepted "
        "letter once lay. \"Did we do the right thing, Seraphina? I keep asking myself that. "
        "We had evidence, yes. We had reasons. But part of me wonders if there was another way.\"",
        {
            {"We protected our family. That is what matters.", "cedric_exp_protected", nullptr, nullptr},
            {"I wonder the same thing.", "cedric_exp_wonder", nullptr, nullptr},
            {"Focus on what comes next.", "cedric_exp_next", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_exp_protected", "Lord Cedric",
        "\"Yes. You are right.\" He nods, though the doubt has not entirely left his eyes. "
        "\"The Aldric family stands. Rosalind is safe. Father's position is secure. That is "
        "worth any discomfort I feel.\" He straightens. \"Besides, if the Iris Consortium truly "
        "sent her, she was never going to stop on her own. We ended something that would only "
        "have grown more dangerous.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_exp_wonder", "Lord Cedric",
        "Cedric looks at you with something like gratitude. \"Thank you for saying that. "
        "Everyone else is so certain, so relieved. But certainty feels wrong after what we "
        "did to someone's life.\" He rubs his face. \"She was clever and dangerous, yes. "
        "But she was also a person. And we dismantled her world.\" He pauses. \"I just need "
        "to sit with that for a while.\"",
        {
            {"Take the time you need.", "cedric_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection += 10;
                            break;
                        }
                    }
                }},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_exp_next", "Lord Cedric",
        "\"Practical as ever.\" A hint of his old smile. \"You are right. The Iris Consortium "
        "will not stop because we expelled one agent. If they want access to the Aldric power "
        "base, they will try again.\" He stands, pacing. \"We need to strengthen our defenses. "
        "Review the staff for other contacts. Increase Roderick's patrols. And perhaps... "
        "reach out to other noble families who may have faced similar infiltration.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_post_death", "Lord Cedric",
        "Cedric's face is pale. His hands are shaking, which he tries to hide by gripping the "
        "edge of the desk. \"Seraphina.\" His voice is barely controlled. \"Tell me you did not "
        "do this.\" He searches your face with desperate intensity. \"Tell me that whatever "
        "happened to Elena was not our doing. Because if it was, if our alliance, our plans "
        "led to someone's death, then I...\" He cannot finish.",
        {
            {"It was not us, Cedric. I promise.", "cedric_death_innocent", nullptr, nullptr},
            {"Things got out of control.", "cedric_death_out_of_control", nullptr, nullptr},
            {"She was a threat. It is over now.", "cedric_death_cold", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_death_innocent", "Lord Cedric",
        "He searches your eyes for a long moment, then nods slowly. \"I believe you.\" Whether "
        "he truly does or simply needs to is unclear. \"Then it was an accident, or someone else "
        "acted on their own. The estate has enough troubled souls.\" He takes a shuddering breath. "
        "\"We need to manage this, Seraphina. For the family. For Father. He will be devastated, "
        "a guest dying under his roof violates everything he stands for.\"",
        {
            {"We will get through this together.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_death_out_of_control", "Lord Cedric",
        "The blood drains from his face. \"Out of control.\" He sits down heavily. \"What does "
        "that mean, exactly? Seraphina, I need to know the truth. All of it. Because if I am "
        "covering for something without understanding what happened, I am complicit in ways I "
        "cannot live with.\" His voice is rough. \"I said I would stand with you. But I also "
        "said there were lines I would not cross. Tell me we did not cross them.\"",
        {
            {"It was an accident. A terrible accident.", "cedric_death_accident", nullptr, nullptr},
            {"You are right. I owe you the truth.", "cedric_death_truth", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_death_accident", "Lord Cedric",
        "\"An accident.\" He repeats it as if trying to make it true. \"Then we grieve "
        "appropriately and we ensure the household remains stable. Father will launch an "
        "investigation. Roderick will secure the grounds. And we...\" He looks at his hands. "
        "\"We stand together. As always.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_death_truth", "Lord Cedric",
        "Cedric listens. His expression moves from shock to horror to something unreadable. "
        "When you finish, the silence stretches like a wound. \"I see.\" Two words that carry "
        "the weight of a world rearranging itself. \"I need time, Seraphina. I need to think "
        "about who we are and who we have become.\" He turns to the window. \"I am still your "
        "brother. Nothing changes that. But everything else... everything else needs to be "
        "reconsidered.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection -= 20;
                            break;
                        }
                    }
                }},
        }, false);

    addNode(state, "cedric_death_cold", "Lord Cedric",
        "Cedric recoils as if struck. \"A threat? She was a person, Seraphina. Whatever she "
        "was doing, whatever the Consortium wanted, she was a living, breathing person.\" "
        "His voice breaks. \"And you speak of her death as if it were weeding a garden.\" "
        "He presses his fists to his eyes. \"I thought we agreed. I thought we had a line. "
        "What happened to 'truth is enough'?\"",
        {
            {"I am sorry, Cedric.", "cedric_death_sorry", nullptr, nullptr},
            {"Back to other matters.", "cedric_root", nullptr,
                [](GameState& gs) {
                    for (auto& n : gs.npcs) {
                        if (n.second.id == "cedric") {
                            n.second.affection -= 30;
                            n.second.suspicion += 20;
                            break;
                        }
                    }
                }},
        }, false);

    addNode(state, "cedric_death_sorry", "Lord Cedric",
        "\"Sorry does not bring her back.\" But some of the hardness leaves his voice. "
        "\"I am sorry too. For whatever part I played. For not seeing where this was heading.\" "
        "He wipes his eyes roughly. \"We cannot undo what is done. But we can choose what comes "
        "next. And I choose to believe that you, my sister, are not the person this moment "
        "makes you look like.\" He meets your eyes. \"Prove me right.\"",
        {
            {"Back to other matters.", "cedric_root", nullptr, nullptr},
        }, false);

    addNode(state, "cedric_farewell", "Lord Cedric",
        "Cedric manages a warm, if tired, smile. \"Take care of yourself, Seraphina. "
        "And come find me whenever you need. Day or night. That is what brothers are for.\"",
        {}, true);
}

}


void registerCedric(GameState &state)
{
    NPC n;
    n.id = "cedric";
    n.name = "Lord Cedric";
    n.title = "Elder Brother";
    n.description = "Your protective, observant elder brother. He notices more than he lets on.";
    n.current_room = "library";
    n.affection = 55;
    n.suspicion = 0;
    n.disposition = Disposition::Loyal;
    n.dialogue_root = "cedric_root";
    n.traits = {Trait::Perceptive, Trait::Strong};
    n.schedule = {
        {7, "dining_room"},
        {8, "courtyard"},
        {10, "library"},
        {12, "dining_room"},
        {13, "garden"},
        {15, "fathers_study"},
        {17, "library"},
        {19, "dining_room"},
        {21, "hallway"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    game::npcs::buildCedricDialogue(state);
}
