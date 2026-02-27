# Village Suburb

```mermaid
graph TD
    subgraph Village Suburb
        TS[Town Square]
        CH[Chapel]
        GY[Graveyard]
        IC[Inn Common Room]
        IR[Inn Rooms]
        TAI[Tailor Shop]
        SM[Small Market]
        VW[Village Well]
    end

    TS -->|North| CH
    CH -->|South| TS

    CH -->|East| GY
    GY -->|West| CH

    TS -->|East| IC
    IC -->|West| TS

    IC -->|Up| IR
    IR -->|Down| IC

    TS -->|West| TAI
    TAI -->|East| TS

    TS -->|South| SM
    SM -->|North| TS

    SM -->|East| VW
    VW -->|West| SM

    TS -->|"North (far)"| EG["Estate Gate ⬆ (to Ducal Estate)"]
    TS -->|"South (far)"| CP["Central Plaza (to City Market)"]
    CH -->|"East (far)"| NAV["Nave ➡ (to Cathedral)"]
    TS -->|"West (far)"| WP["Woodland Path ⬅ (to Forest Edge)"]

    style TS fill:#228B22,color:#fff
    style CH fill:#9370DB,color:#fff
    style IC fill:#DAA520,color:#000
    style IR fill:#BDB76B,color:#000
```

## Room Details

| Room | ID | Travel Time | Exits | Features |
|------|----|------------|-------|----------|
| Town Square | village_town_square | 3 min | N -> Chapel, S -> Market, E -> Inn, W -> Tailor | Central hub, notice board, gossip, carriage to Estate |
| Chapel | village_chapel | 2 min | S -> Town Sq, E -> Graveyard | Prayer, priest NPC, exit to Cathedral |
| Graveyard | village_graveyard | 3 min | W -> Chapel | Quiet, hidden items, lore |
| Inn Common Room | village_inn | 2 min | W -> Town Sq, Up -> Inn Rooms | Drinks, rumors, travelers, bard |
| Inn Rooms | village_inn_rooms | 1 min | Down -> Inn Common | Sleep allowed, eavesdrop |
| Tailor Shop | village_tailor | 2 min | E -> Town Sq | Disguises, clothing, NPC tailor |
| Small Market | village_market | 2 min | N -> Town Sq, E -> Well | Food stalls, merchants, supplies |
| Village Well | village_well | 2 min | W -> Market | Meeting point, overheard secrets |
