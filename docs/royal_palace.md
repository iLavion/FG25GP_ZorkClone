# Royal Palace

```mermaid
graph TD
    subgraph Royal Palace
        OC[Outer Courtyard]
        GS[Grand Staircase]
        TR[Throne Room]
        AC[Audience Chamber]
        BR[Ballroom]
        SC[Servants' Corridor]
        RW[Restricted Wing]
        PG[Palace Garden]
    end

    OC -->|North| GS
    GS -->|South| OC

    GS -->|North| AC
    AC -->|South| GS

    AC -->|North| TR
    TR -->|South| AC

    GS -->|East| BR
    BR -->|West| GS

    GS -->|West| SC
    SC -->|East| GS

    GS -->|Up| RW
    RW -->|Down| GS

    SC -->|South| PG
    PG -->|North| SC

    OC -->|"South (far)"| CL["Carriage Lane (to Noble Quarter)"]

    style TR fill:#DC143C,color:#fff
    style GS fill:#FFD700,color:#000
    style RW fill:#8B0000,color:#fff
    style BR fill:#FF69B4,color:#000
    style PG fill:#90EE90,color:#000
```

## Room Details

| Room | ID | Travel Time | Exits | Features |
|------|----|------------|-------|----------|
| Outer Courtyard | palace_outer_courtyard | 4 min | N -> Grand Staircase | Palace entrance, royal guards, impressive architecture |
| Grand Staircase | palace_grand_staircase | 3 min | S -> Outer Court, N -> Audience, E -> Ballroom, W -> Servants' Corridor, Up -> Restricted | Central hub, ornate marble stairs |
| Throne Room | palace_throne_room | 2 min | S -> Audience Chamber | The King's seat, formal audiences, endgame events |
| Audience Chamber | palace_audience_chamber | 3 min | N -> Throne Room, S -> Grand Staircase | Petitions, Prince NPC, political maneuvering |
| Ballroom | palace_ballroom | 3 min | W -> Grand Staircase | Grand dances, social competition, Elena encounters |
| Servants' Corridor | palace_servants_corridor | 2 min | E -> Grand Staircase, S -> Palace Garden | Servant gossip, hidden routes, intel |
| Restricted Wing | palace_restricted_wing | 4 min | Down -> Grand Staircase | Royal secrets, forbidden documents, high suspicion |
| Palace Garden | palace_garden | 3 min | N -> Servants' Corridor | Royal gardens, private conversations, romantic scenes |
