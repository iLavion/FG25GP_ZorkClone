#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include <algorithm>

void registerCaptainRoderick(GameState &state)
{
    NPC n;
    n.id = "captain_roderick";
    n.name = "Captain Roderick";
    n.title = "Guard Captain";
    n.description = "Head of estate security. Suspicious by nature. He watches everyone,\n"
                    "including you.";
    n.current_room = "courtyard";
    n.affection = 40;
    n.suspicion = 20;
    n.disposition = Disposition::Suspicious;
    n.dialogue_root = "captain_roderick_root";
    n.traits = {Trait::Perceptive, Trait::Strong, Trait::LightSleeper};
    n.hireable = true;
    n.hire_cost = 30;
    n.schedule = {
        {5, "courtyard"},
        {7, "grand_hall"},
        {8, "courtyard"},
        {10, "hallway"},
        {12, "kitchen"},
        {13, "courtyard"},
        {15, "garden"},
        {17, "courtyard"},
        {19, "dining_room"},
        {20, "grand_hall"},
        {22, "courtyard"},
        {0, "courtyard"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
        state.rooms[n.current_room].npc_ids.push_back(n.id);

    addNode(state, "captain_roderick_root", "Captain Roderick",
            "\"Lady Seraphina. *He stands at attention, hand resting on his sword hilt.*\n"
            "Is there a security matter you wish to report?\"",
            {{"\"Has anything unusual happened at the estate?\"", "roderick_report", nullptr, nullptr},
             {"\"I'd like to discuss our guest, Elena.\"", "roderick_elena", nullptr, nullptr},
             {"\"Tell me about yourself, Captain.\"", "roderick_backstory", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }},
             {"\"I need your help with something discreet.\" (Hire)", "roderick_hire",
              [](const GameState &gs)
              { return gs.player.suspicion < 50; },
              nullptr},
             {"\"What's the security situation?\"", "roderick_patrol", nullptr, nullptr},
             {"\"Just passing through, Captain.\"", "", nullptr, nullptr}});

    addNode(state, "roderick_report", "Captain Roderick",
            "\"*He pulls out a small ledger.* The usual comings and goings. Though I've\n"
            "noted an increase in visitors since our guest arrived. Merchants, couriers,\n"
            "even a few minor nobles I don't recognize. *He flips a page.* I've doubled\n"
            "the garden patrols and stationed a man near the guest room at night.\"",
            {{"\"Have any of these visitors been suspicious?\"", "roderick_report_visitors", nullptr, nullptr},
             {"\"Good. Stay vigilant.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }},
             {"\"A man near the guest room? Isn't that excessive?\"", "roderick_report_excessive", nullptr, nullptr}});

    addNode(state, "roderick_report_visitors", "Captain Roderick",
            "\"*He lowers his voice.* One caught my eye. A man in dark traveling clothes,\n"
            "no house crest, no merchant's badge. He delivered a letter to Elena's room\n"
            "and left before I could question him. *His jaw tightens.* The letter bore\n"
            "a wax seal, some kind of flower. I've never seen that sigil before.\"",
            {{"\"A flower seal? Describe it.\"", "roderick_flower_seal", nullptr, nullptr},
             {"\"Interesting. Keep monitoring her correspondence.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }},
             {"\"You should have intercepted that letter.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection -= 3; }}});

    addNode(state, "roderick_flower_seal", "Captain Roderick",
            "\"*He sketches in the air.* Six petals, narrow, curved. Purple wax.\n"
            "Not a rose, not a lily. *He pauses.* An iris, perhaps? I've seen\n"
            "something similar on documents from the capital, but I can't place\n"
            "it. *He meets your eyes.* If you learn anything about that sigil,\n"
            "my lady, I would appreciate knowing.\"",
            {{"\"The Iris Consortium. I've heard whispers.\"", "roderick_iris", nullptr, nullptr},
             {"\"I'll look into it. Thank you, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }}});

    addNode(state, "roderick_iris", "Captain Roderick",
            "\"*His eyes sharpen.* The Iris Consortium? *He steps closer, voice barely\n"
            "above a whisper.* I've heard that name once before, from an old commanding\n"
            "officer. He said they were a network of merchants and minor nobles who\n"
            "trade in favors and secrets. *He grips his sword hilt.* If they're\n"
            "involved with our guest, this is far more dangerous than I thought.\"",
            {{"\"Can you investigate further?\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }},
             {"\"Keep this between us, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }}},
            true);

    addNode(state, "roderick_report_excessive", "Captain Roderick",
            "\"*He stiffens.* With respect, my lady, it is my duty to protect this\n"
            "estate and everyone in it. That includes protecting you from yourself,\n"
            "if necessary. *He pauses.* I've noticed... activity. Late at night.\n"
            "Footsteps in the hallway when everyone should be asleep. The cellar\n"
            "door found unlocked twice this week.\"",
            {{"\"The cellar? That is concerning.\"", "roderick_cellar", nullptr, nullptr},
             {"\"And you think Elena is responsible?\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }}});

    addNode(state, "roderick_cellar", "Captain Roderick",
            "\"*He nods grimly.* I checked it myself. Nothing missing, but there were\n"
            "scuff marks on the floor, fresh ones, leading toward the back wall.\n"
            "*He looks at you meaningfully.* I've heard old stories about passages\n"
            "beneath this estate. Servants' tales, mostly. But those scuff marks\n"
            "were real.\"",
            {{"\"I know about the passage. Thorne showed me.\"", "roderick_passage_known", nullptr,
              [](const GameState &gs)
              { return gs.quest.secret_passage_known; }},
             {"\"Look into it, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }}},
            true);

    addNode(state, "roderick_passage_known", "Captain Roderick",
            "\"*His expression darkens.* Thorne. Of course. That man knows more about\n"
            "this estate than the blueprints do. *He crosses his arms.* A secret\n"
            "passage is a security vulnerability, my lady. I'll need to post a guard.\n"
            "Unless, you'd prefer the passage remain... accessible?\"",
            {{"\"Leave it open, but watch who uses it.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].suspicion += 5; }},
             {"\"Post a guard. Security comes first.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 8; }}},
            true);

    addNode(state, "roderick_elena", "Elena",
            "\"*He narrows his eyes.* That commoner? I don't trust her, my lady. Too\n"
            "charming for her own good. Every servant she speaks to walks away smiling.\n"
            "That kind of influence doesn't come naturally. *He pauses.* I've been\n"
            "watching her, but she hasn't done anything I can officially report to\n"
            "your father. Yet.\"",
            {{"\"Keep watching. Report anything suspicious.\"", "roderick_elena_watch", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }},
             {"\"I want you to... create a situation.\" (Risky)", "roderick_setup",
              [](const GameState &gs)
              { return gs.player.suspicion < 40; }, nullptr},
             {"\"What exactly have you observed?\"", "roderick_elena_details", nullptr, nullptr},
             {"\"Perhaps you're being too suspicious, Captain.\"", "roderick_elena_defend", nullptr, nullptr}});

    addNode(state, "roderick_elena_watch", "Captain Roderick",
            "\"*He nods curtly.* Understood, my lady. I'll have my men keep a closer\n"
            "eye on her movements. Discreetly, of course. *He pauses.* One more\n"
            "thing. She's been visiting the garden at odd hours. Before dawn,\n"
            "mostly. Thorne has noticed it too. Could be nothing, but it's unusual.\"",
            {{"\"Before dawn? What could she be doing?\"", "", nullptr,
              [](GameState &gs)
              { gs.heroine_popularity += 2; }},
             {"\"Thank you, Captain. You're invaluable.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }}},
            true);

    addNode(state, "roderick_elena_details", "Captain Roderick",
            "\"*He pulls out his ledger.* She rises early, visits the garden, then the\n"
            "library. Spends hours reading, makes notes in a journal she keeps on her\n"
            "person. She eats with the family when invited, with the servants when not.\n"
            "*He flips a page.* Receives letters twice weekly. Writes in her room late\n"
            "at night, I can see the candlelight from the courtyard. *He looks up.*\n"
            "She's methodical, my lady. Whatever she's doing, it's planned.\"",
            {{"\"Methodical and planned. That's not innocent behavior.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }},
             {"\"Or she's a studious girl with a routine. Keep watching.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "roderick_elena_defend", "Captain Roderick",
            "\"*He straightens, a flash of indignation crossing his face.* Suspicion\n"
            "is my profession, my lady. Twenty years of service taught me that charming\n"
            "strangers are the ones you watch most carefully. *He softens slightly.*\n"
            "But, perhaps you're right. Perhaps she's exactly what she claims. I\n"
            "simply prefer to be certain.\"",
            {{"\"Your dedication is appreciated, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }},
             {"\"Keep watching, but don't harass her.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "roderick_setup", "Captain Roderick",
            "\"*He stiffens.* My lady, I am a man of duty. I will not fabricate evidence.\n"
            "*He pauses, studying your face.* But if real evidence were to... surface,\n"
            "I would act swiftly. And if someone were to, say, discover that our guest\n"
            "had been somewhere she shouldn't be at an hour she couldn't explain...\n"
            "well, that would be a matter of security.\"",
            {{"\"I understand, Captain. Perfectly.\"", "", nullptr,
              [](GameState &gs)
              { gs.player.suspicion += 8; }},
             {"\"Forget I asked. This isn't your way.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }}},
            true);

    addNode(state, "roderick_backstory", "Captain Roderick",
            "\"*He seems surprised by the question.* Myself? *He relaxes slightly,\n"
            "the rigid military bearing softening.* Not much to tell. Served in\n"
            "the King's Guard for twelve years. Saw action at the Thornwall Border.\n"
            "Your father recruited me personally when Lady Aldric, your mother,\n"
            "fell ill. He wanted the best protection for his family.\"",
            {{"\"You knew my mother?\"", "roderick_mother", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }},
             {"\"The Thornwall Border? What happened there?\"", "roderick_thornwall", nullptr, nullptr},
             {"\"My father chose well.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 8; }}});

    addNode(state, "roderick_mother", "Captain Roderick",
            "\"*His expression softens in a way you've never seen.* Lady Aldric was...\n"
            "remarkable. Kind, but fierce. She insisted I teach you and your siblings\n"
            "basic self-defense when you were children. *A ghost of a smile.* You were\n"
            "the best student, my lady. You disarmed Lord Cedric on your first try.\n"
            "He was furious. *He clears his throat.* She was the heart of this estate.\"",
            {{"\"I remember those lessons. Thank you for that, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 10; }},
             {"\"She was the best of us. I miss her every day.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 8; }}},
            true);

    addNode(state, "roderick_thornwall", "Captain Roderick",
            "\"*His jaw tightens.* Border skirmishes with the southern provinces.\n"
            "Three years of mud, steel, and watching good men die for disputed\n"
            "farmland. *He touches a scar on his forearm.* I earned this the night\n"
            "our camp was raided. Killed four men with a broken sword. *He shakes\n"
            "his head.* War teaches you one thing, my lady: trust is the most\n"
            "dangerous weapon, and the most valuable.\"",
            {{"\"That explains why you trust no one.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }},
             {"\"You're a brave man, Captain.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 8; }}},
            true);

    addNode(state, "roderick_hire", "Captain Roderick",
            "\"*He checks that no one is nearby.* Discreet, my lady? *He lowers his\n"
            "voice.* For 30 gold, I can arrange certain... security measures. I have\n"
            "men who can watch without being seen, documents that can be examined\n"
            "without being disturbed, and rooms that can be searched while their\n"
            "occupants are elsewhere.\"",
            {{"\"Search Elena's room tonight.\"", "roderick_hire_search", nullptr,
              [](GameState &gs)
              {
                  if (gs.player.gold >= 30)
                  {
                      gs.player.gold -= 30;
                  }
              }},
             {"\"Have your men shadow Elena for a week.\"", "roderick_hire_shadow", nullptr,
              [](GameState &gs)
              {
                  if (gs.player.gold >= 30)
                  {
                      gs.player.gold -= 30;
                  }
              }},
             {"\"That's too costly. Maybe later.\"", "", nullptr, nullptr}});

    addNode(state, "roderick_hire_search", "Captain Roderick",
            "\"*He nods.* Consider it done. My men will enter while she's at dinner.\n"
            "We'll look for correspondence, journals, anything that reveals her true\n"
            "intentions. *He pauses.* If there's anything to find, my lady, we'll\n"
            "find it. And if there isn't... well, at least you'll know.\"",
            {{"\"Report to me first. No one else.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.quest.elena_letters_found = true;
                  gs.player.suspicion += 5;
                  gs.npcs["captain_roderick"].affection += 5;
              }}},
            true);

    addNode(state, "roderick_hire_shadow", "Captain Roderick",
            "\"*He strokes his chin.* A full surveillance operation. I'll rotate three\n"
            "men in shifts. She won't take a step without us knowing. *He tucks his\n"
            "ledger away.* By week's end, I'll have a complete record of her movements,\n"
            "contacts, and habits. You'll know her better than she knows herself.\"",
            {{"\"Good. Bring me your findings as soon as they're ready.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.player.suspicion += 3;
                  gs.npcs["captain_roderick"].affection += 5;
                  gs.heroine_popularity -= 3;
              }}},
            true);

    addNode(state, "roderick_patrol", "Captain Roderick",
            "\"*He straightens.* Current deployment: two men on the main gate, one\n"
            "patrolling the garden perimeter, one in the grand hall, and myself\n"
            "wherever I'm most needed. *He frowns.* Frankly, my lady, I'm\n"
            "understaffed. This estate has too many entrances and not enough\n"
            "guards to cover them all. Especially at night.\"",
            {{"\"What vulnerabilities concern you most?\"", "roderick_vulnerabilities", nullptr, nullptr},
             {"\"Can we hire more guards?\"", "roderick_more_guards", nullptr, nullptr},
             {"\"You're doing your best with what you have.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 5; }}});

    addNode(state, "roderick_vulnerabilities", "Captain Roderick",
            "\"*He begins listing them on his fingers.* The cellar has that back wall\n"
            "I mentioned. The garden wall is low enough to climb in three places.\n"
            "The kitchen entrance is unguarded after midnight. The balcony is\n"
            "accessible from the courtyard roof. *He meets your eyes.* And the\n"
            "guest room window faces the garden wall. If someone wanted to leave\n"
            "the estate unseen... it would be trivial.\"",
            {{"\"You suspect Elena uses the garden wall exit?\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }},
             {"\"Seal the vulnerabilities. I'll fund it if needed.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["captain_roderick"].affection += 10;
                  gs.player.reputation += 3;
              }}},
            true);

    addNode(state, "roderick_more_guards", "Captain Roderick",
            "\"*His eyes light up.* I could use four more men, at minimum. That would\n"
            "let me cover the garden at night and maintain proper shifts. *He pauses.*\n"
            "Your father hasn't approved the budget. He says the estate is peaceful.\n"
            "*A dry look.* Peace, in my experience, is what happens right before\n"
            "everything falls apart.\"",
            {{"\"I'll speak to my father about it.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 8; }},
             {"\"A pessimistic view, Captain, but not wrong.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["captain_roderick"].affection += 3; }}},
            true);
}
