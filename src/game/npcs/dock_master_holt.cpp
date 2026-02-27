#include "game.hpp"
#include "game/dialogue_helpers.hpp"
#include "utilities/text.hpp"
#include <iostream>

void registerDockMasterHolt(GameState &state)
{
    NPC n;
    n.id = "dock_master_holt";
    n.name = "Dock Master Holt";
    n.title = "Harbor Master";
    n.description = "A stocky, weather-beaten man with a salt-and-pepper beard and hands\n"
                    "like ship's rigging. He wears a heavy coat regardless of the weather\n"
                    "and speaks in the clipped, no-nonsense manner of someone who has spent\n"
                    "a lifetime commanding ships and men.";
    n.current_room = "docks_harbor_master";
    n.affection = 10;
    n.suspicion = 0;
    n.disposition = Disposition::Neutral;
    n.dialogue_root = "holt_root";
    n.traits = {Trait::Perceptive};
    n.schedule = {
        {5, "docks_main_pier"},
        {7, "docks_harbor_master"},
        {9, "docks_warehouses"},
        {11, "docks_main_pier"},
        {13, "docks_fish_market"},
        {14, "docks_harbor_master"},
        {17, "docks_ship_deck"},
        {19, "docks_harbor_master"},
        {22, "docks_main_pier"},
    };
    state.npcs[n.id] = n;
    if (state.rooms.count(n.current_room))
    {
        state.rooms[n.current_room].npc_ids.push_back(n.id);
    }

    addNode(state, "holt_root", "Dock Master Holt",
            "\"*He looks up from a stack of shipping manifests and squints.*\n"
            "Lady... Seraphina, is it? Don't get many nobles down at the docks.\n"
            "What brings you to my pier? If it's fresh fish you want, the market\n"
            "is that way. *He jerks a thumb over his shoulder.*\"",
            {{"\"I'm interested in the shipping routes.\"", "holt_routes",
              nullptr, nullptr},
             {"\"I need to arrange a discreet passage.\"", "holt_passage",
              nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].suspicion += 5; }},
             {"\"What can you tell me about unusual shipments lately?\"",
              "holt_unusual", nullptr, nullptr},
             {"\"I've heard rumors about smuggling operations.\"", "holt_smuggling",
              nullptr, [](GameState &gs)
              { gs.npcs["dock_master_holt"].suspicion += 10; }},
             {"\"I just wanted to see the ships.\"", "holt_ships", nullptr, nullptr}});

    addNode(state, "holt_routes", "Dock Master Holt",
            "\"Shipping routes? *He raises an eyebrow.* We run three main lines:\n"
            "east to the spice islands, south to the warm kingdoms, and north\n"
            "to the mining provinces. Most cargo is trade goods, textiles, grain,\n"
            "lumber. *He crosses his arms.* Why does a noble lady care about\n"
            "shipping routes?\"",
            {{"\"I'm considering investing in trade.\"", "holt_invest", nullptr, nullptr},
             {"\"I'm looking for someone who might have arrived by ship.\"",
              "holt_arrivals", nullptr, nullptr},
             {"\"Purely academic curiosity.\"", "", nullptr, nullptr}});

    addNode(state, "holt_invest", "Dock Master Holt",
            "\"*His expression brightens.*\n"
            "Now you're speaking my language. Trade investment, that's the\n"
            "smartest thing a noble can do with their gold. The eastern spice\n"
            "route pays triple returns, but it's risky. *He scratches his beard.*\n"
            "You want safe? Southern textiles. Want rich? Eastern spices.\n"
            "Want to lose everything? Gamble on northern ice diamonds.\"",
            {{"\"What about importing something specific?\"", "holt_specific",
              nullptr, nullptr},
             {"\"I'll keep the investment idea in mind. Thank you.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}});

    addNode(state, "holt_specific", "Dock Master Holt",
            "\"Specific? *He leans in.* I can arrange almost anything, legal or\n"
            "slightly-less-than-legal. Rare herbs, exotic fabrics, foreign wines.\n"
            "*He holds up a finger.* But anything that gets my dock shut down,\n"
            "that I won't touch. I've got a reputation to maintain, even if it's\n"
            "not a pretty one.\"",
            {{"\"What's the most unusual thing you've imported?\"",
              "holt_unusual_import", nullptr, nullptr},
             {"\"Good to know. I may need your services.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["dock_master_holt"].affection += 5;
                  std::cout << colored("  [i] Dock Master Holt can import rare goods.", ansi::BRIGHT_CYAN) << "\n";
              }}});

    addNode(state, "holt_unusual_import", "Dock Master Holt",
            "\"*He chuckles.*\n"
            "Last year a countess wanted a live peacock from the southern\n"
            "kingdoms. The thing screamed the entire voyage. Nearly gave old\n"
            "Captain Briggs a heart attack. *He shakes his head.* Nobles.\n"
            "No offense, my lady. You're alright, for a noble.\"",
            {{"\"*Laugh.* None taken, Holt.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 10; }}},
            true);

    addNode(state, "holt_arrivals", "Dock Master Holt",
            "\"*He pulls out a thick, leather-bound ledger.*\n"
            "Every soul that comes through this port gets logged. Name, origin,\n"
            "purpose of travel. *He flips through pages.* Who are you looking\n"
            "for?\"",
            {{"\"A young woman named Elena, arrived sometime recently.\"",
              "holt_elena_arrival",
              [](const GameState &gs)
              { return gs.quest.met_elena; }, nullptr},
             {"\"Anyone from the eastern provinces, arriving in the last month.\"",
              "holt_eastern", nullptr, nullptr},
             {"\"Never mind. Just general curiosity.\"", "", nullptr, nullptr}});

    addNode(state, "holt_elena_arrival", "Dock Master Holt",
            "\"*He flips back several pages and runs a thick finger down the entries.*\n"
            "Elena... Elena... Ah, here. Elena. No surname listed. Arrived on\n"
            "the Southern Star, passenger class, three months ago. *He squints\n"
            "at the entry.* Huh. Her passage was paid for by a third party.\n"
            "Name is smudged, can't read it. That's unusual.\"",
            {{"\"A third party paid for her passage? Who would do that?\"",
              "holt_elena_payment", nullptr, nullptr},
             {"\"What else does the record say?\"", "holt_elena_details", nullptr, nullptr}});

    addNode(state, "holt_elena_payment", "Dock Master Holt",
            "\"*He shrugs.*\n"
            "Could be anyone. A sponsor, a patron, a relative with money.\n"
            "But here's the thing, the payment was made in advance. Someone\n"
            "knew she was coming before she did, or at least before she\n"
            "arrived. *He taps the ledger.* That takes planning. And gold.\n"
            "Whoever brought that girl to this city wanted her here.\"",
            {{"\"Someone planned Elena's arrival. Interesting.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena's passage was pre-paid by an unknown sponsor.", ansi::BRIGHT_CYAN) << "\n";
                  std::cout << colored("      Someone orchestrated her arrival in the capital.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "holt_elena_details", "Dock Master Holt",
            "\"*He reads aloud.*\n"
            "Single passenger, one trunk of belongings, no weapons declared.\n"
            "Point of origin: Millhaven, a farming village in the south.\n"
            "*He looks up.* She also had a letter of introduction to the Duke,\n"
            "sealed with a wax seal I didn't recognize. Not a noble house seal.\n"
            "Something else. Could be a merchant guild, could be a church.\"",
            {{"\"An unrecognized seal? Can you describe it?\"",
              "holt_elena_seal", nullptr, nullptr},
             {"\"That's very helpful. Thank you, Holt.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}});

    addNode(state, "holt_elena_seal", "Dock Master Holt",
            "\"*He scratches his head.*\n"
            "Round, with some kind of flower in the center. Laurel wreath\n"
            "around it, if I'm remembering right. Deep red wax, good quality.\n"
            "*He shrugs.* Could be a hundred organizations. But it wasn't any\n"
            "noble house I know, and I know most of them by their seals.\"",
            {{"\"A flower seal in red wax. I'll look into it.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Elena carried a letter with an unidentified flower seal.", ansi::BRIGHT_CYAN) << "\n";
                  std::cout << colored("      This may identify her mysterious patron.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "holt_eastern", "Dock Master Holt",
            "\"Eastern provinces? *He flips pages.* Let me see... Three ships\n"
            "from the east this month. The Jade Serpent carried spices. The\n"
            "Morning Glory had textiles and one passenger, a scholar heading\n"
            "to the Academy. And the Red Fox was unlisted cargo, private\n"
            "charter. *He frowns.* Private charters don't have to declare,\n"
            "so I can't tell you what was on it.\"",
            {{"\"Who chartered the Red Fox?\"", "holt_red_fox", nullptr, nullptr},
             {"\"A scholar from the east. What was their name?\"",
              "holt_eastern_scholar", nullptr, nullptr}});

    addNode(state, "holt_red_fox", "Dock Master Holt",
            "\"*He flips to a different page.*\n"
            "Chartered by... a trading company called the Iris Consortium.\n"
            "Never heard of them before this month. Paid in gold, cash. The\n"
            "crew unloaded six crates at night, took them to a warehouse\n"
            "on the west side. *He gives you a look.* I don't pry into\n"
            "private charters, my lady. It's bad for business.\"",
            {{"\"The Iris Consortium. I'll remember that name.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] The 'Iris Consortium' shipped mystery cargo at night.", ansi::BRIGHT_YELLOW) << "\n";
              }}},
            true);

    addNode(state, "holt_eastern_scholar", "Dock Master Holt",
            "\"*He checks the manifest.*\n"
            "One 'Elias Faerwind,' scholar of antiquities. Heading to the\n"
            "Royal Academy. Quiet fellow, polite. Carried about thirty books\n"
            "and nothing else. Scholars, they're all the same. *He smirks.*\"",
            {{"\"That must be the Academy's new historian.\"", "", nullptr, nullptr}},
            true);

    addNode(state, "holt_passage", "Dock Master Holt",
            "\"*He lowers his voice.*\n"
            "Discreet, eh? Where to, and how fast? I can get you on a merchant\n"
            "vessel to the south in three days, no questions asked. Costs more\n"
            "than a regular passage, mind. Discretion has a premium.\"",
            {{"\"How much?\"", "holt_passage_cost", nullptr, nullptr},
             {"\"Not for me. For someone else.\"", "holt_passage_someone", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].suspicion += 5; }},
             {"\"I'm just considering my options. Thank you.\"", "", nullptr, nullptr}});

    addNode(state, "holt_passage_cost", "Dock Master Holt",
            "\"For a noble lady? Fifty gold for a quiet cabin on a southbound\n"
            "ship. That includes new identity papers and a, shall we say,\n"
            "creative entry in the passenger log. *He crosses his arms.*\n"
            "I've helped three lords and a duchess disappear over the years.\n"
            "My record is spotless.\"",
            {{"\"I'll keep that in mind if things go badly.\"", "", nullptr,
              [](GameState &gs)
              {
                  std::cout << colored("  [i] Holt can arrange an escape by ship for 50 gold.", ansi::BRIGHT_CYAN) << "\n";
              }},
             {"\"That won't be necessary. I intend to win.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}},
            true);

    addNode(state, "holt_passage_someone", "Dock Master Holt",
            "\"*He gives you a long, hard look.*\n"
            "Sending someone away? That's a different kind of business. *He\n"
            "scratches his chin.* If they're willing, same price. If they're\n"
            "not willing... *He shakes his head.* I don't do kidnapping, my\n"
            "lady. Not even for nobles. But I know people who know people.\n"
            "*He meets your eyes.* Though I'd advise against it. Strongly.\"",
            {{"\"Nothing like that. Just exploring possibilities.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].suspicion -= 5; }},
             {"\"What if someone needed to disappear permanently?\"",
              "holt_disappear", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].suspicion += 15; }}});

    addNode(state, "holt_disappear", "Dock Master Holt",
            "\"*His expression hardens.*\n"
            "Then I'd say that someone should think very carefully about what\n"
            "they're asking. *He leans in close.* People who arrange\n"
            "disappearances tend to need one themselves, sooner or later.\n"
            "*He straightens.* I think we're done here, my lady. Good day.\"",
            {{"\"*You've overstepped. Leave quietly.*\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["dock_master_holt"].affection -= 15;
                  gs.player.suspicion += 5;
                  std::cout << colored("  [i] You've alarmed Holt. He may be watching you now.", ansi::BRIGHT_RED) << "\n";
                  std::cout << colored("  Suspicion +5", ansi::BRIGHT_YELLOW) << "\n";
              }}},
            true);

    addNode(state, "holt_unusual", "Dock Master Holt",
            "\"Unusual? *He rubs his chin thoughtfully.* The docks always have\n"
            "something unusual. Last week someone shipped a crate of live eels\n"
            "that broke open on the pier. Chaos. *He grins, then grows serious.*\n"
            "But if you mean suspicious, there have been more private charters\n"
            "than usual. Cloaked figures unloading at odd hours. I've logged\n"
            "what I can, but private charters have protections.\"",
            {{"\"Who's been chartering these ships?\"", "holt_red_fox", nullptr, nullptr},
             {"\"Have you reported this to the authorities?\"", "holt_authorities",
              nullptr, nullptr},
             {"\"Just dock gossip. Thank you, Holt.\"", "", nullptr, nullptr}});

    addNode(state, "holt_authorities", "Dock Master Holt",
            "\"*He snorts.*\n"
            "The authorities? My lady, with respect, the authorities are the\n"
            "ones chartering half these ships. When a lord wants something\n"
            "moved quietly, he doesn't ask permission, he pays gold. *He\n"
            "shakes his head.* I keep my head down and my books clean.\n"
            "That's how you survive in this business.\"",
            {{"\"A pragmatic approach. I respect that.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}},
            true);

    addNode(state, "holt_smuggling", "Dock Master Holt",
            "\"*His face closes off immediately.*\n"
            "Smuggling? I wouldn't know anything about that, my lady. This\n"
            "is a legitimate port with legitimate trade. *He stares at you.*\n"
            "Whatever you've heard is hearsay and gossip. Nothing happens on\n"
            "my docks that isn't accounted for. *He pauses.* Officially.\"",
            {{"\"Of course. I meant no offense.\"", "holt_no_offense", nullptr, nullptr},
             {"\"I'm not here to cause trouble. But I could use a contact.\"",
              "holt_contact", nullptr, nullptr}});

    addNode(state, "holt_no_offense", "Dock Master Holt",
            "\"*He relaxes slightly.*\n"
            "None taken, my lady. It's just, smuggling is a word that gets\n"
            "ports shut down and dock masters hanged. *He forces a laugh.*\n"
            "Unofficially, if you ever need something moved around the city\n"
            "without too many questions, maybe talk to some of the warehouse\n"
            "workers. They're more flexible than I am. Officially.\"",
            {{"\"Unofficially understood. Thank you, Holt.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}},
            true);

    addNode(state, "holt_contact", "Dock Master Holt",
            "\"*He sizes you up for a long moment.*\n"
            "A contact. *He sighs.* The smuggler's hideout is in the back\n"
            "of the warehouses. Ask for a woman named 'Shadow.' She handles\n"
            "the off-books work. *He holds up a finger.* But you didn't hear\n"
            "that from me, and if anyone asks, I'll deny everything. We clear?\"",
            {{"\"Crystal clear. Thank you, Holt.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["dock_master_holt"].affection += 5;
                  std::cout << colored("  [i] Holt directed you to 'Shadow' in the smuggler's hideout.", ansi::BRIGHT_CYAN) << "\n";
              }}},
            true);

    addNode(state, "holt_ships", "Dock Master Holt",
            "\"*His expression softens.*\n"
            "The ships? Now that I can understand. There's nothing like\n"
            "watching a three-masted galleon come into port with full sails.\n"
            "*He gestures toward the harbor.* We've got the Southern Star,\n"
            "she's a beauty, runs the southern trade route. The Jade Serpent\n"
            "handles the east. And old Captain Briggs keeps his fishing fleet\n"
            "by the main pier, been here since before I was born.\"",
            {{"\"It must be wonderful, working by the sea.\"", "holt_sea_love",
              nullptr, nullptr},
             {"\"Have you always been a dock master?\"", "holt_past", nullptr, nullptr}});

    addNode(state, "holt_sea_love", "Dock Master Holt",
            "\"*A rare smile crosses his weathered face.*\n"
            "Wonderful? It's freezing, wet, and smells like fish. *He looks\n"
            "out at the harbor, and his voice softens.* But yes. There's\n"
            "nowhere else I'd rather be. The sea doesn't care about noble\n"
            "houses or court politics. She just is. *He clears his throat.*\n"
            "Getting sentimental. Don't tell anyone.\"",
            {{"\"Your secret is safe with me, Holt.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 10; }}},
            true);

    addNode(state, "holt_past", "Dock Master Holt",
            "\"*He leans against his desk.*\n"
            "Twenty years a sailor before I got too old for the rigging. The\n"
            "Duke, your father actually, gave me this position. Said he wanted\n"
            "someone honest running the docks. *He chuckles.* 'Honest' might\n"
            "be a stretch, but I've kept the port running and the cargo flowing.\n"
            "Your father's a good man, my lady. Better than most nobles.\"",
            {{"\"He is. And he chose well with you.\"", "", nullptr,
              [](GameState &gs)
              {
                  gs.npcs["dock_master_holt"].affection += 15;
                  std::cout << colored("  [i] Holt is loyal to your father. He could be a valuable ally.", ansi::BRIGHT_GREEN) << "\n";
              }},
             {"\"I'll let him know you said that.\"", "", nullptr,
              [](GameState &gs)
              { gs.npcs["dock_master_holt"].affection += 5; }}},
            true);
}
