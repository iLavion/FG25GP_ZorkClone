# City Market District

```mermaid
graph TD
    subgraph City Market District
        CP[Central Plaza]
        APO[Apothecary]
        GS[General Store]
        BS[Bookshop]
        BAK[Bakery]
        AL[Alleyways]
        BMD[Black Market Den]
        CO[Courier Office]
    end

    CP -->|West| APO
    APO -->|East| CP

    CP -->|East| GS
    GS -->|West| CP

    CP -->|North| BS
    BS -->|South| CP

    CP -->|South| BAK
    BAK -->|North| CP

    CP -->|"South-East"| AL
    AL -->|"North-West"| CP

    AL -->|South| BMD
    BMD -->|North| AL

    BS -->|East| CO
    CO -->|West| BS

    CP -->|"North (far)"| TSQ["Town Square ⬆ (to Village)"]
    CP -->|"West (far)"| CL["Carriage Lane ⬅ (to Noble Quarter)"]
    CP -->|"East (far)"| MG["Main Gate ➡ (to Academy)"]
    AL -->|"East (far)"| MP["Main Pier ➡ (to Docks)"]

    style CP fill:#FF8C00,color:#fff
    style BMD fill:#2F4F4F,color:#fff
    style AL fill:#696969,color:#fff
```

## Room Details

| Room | ID | Travel Time | Exits | Features |
|------|----|------------|-------|----------|
| Central Plaza | city_central_plaza | 3 min | N -> Bookshop, S -> Bakery, E -> General Store, W -> Apothecary, SE -> Alleyways | Main hub, fountain, criers, area transitions |
| Apothecary | city_apothecary | 2 min | E -> Central Plaza | Potions, herbs, poison ingredients, alchemist NPC |
| General Store | city_general_store | 2 min | W -> Central Plaza | Tools, rope, lanterns, general supplies |
| Bookshop | city_bookshop | 2 min | S -> Central Plaza, E -> Courier Office | Rare texts, lore books, scholar NPC |
| Bakery | city_bakery | 2 min | N -> Central Plaza | Fresh bread, pastries, food supplies, friendly baker |
| Alleyways | city_alleyways | 3 min | NW -> Central Plaza, S -> Black Market | Dark, thieves, rats, exit to Docks |
| Black Market Den | city_black_market | 4 min | N -> Alleyways | Illegal goods, forged documents, hired thugs, fence NPC |
| Courier Office | city_courier | 2 min | W -> Bookshop | Send/receive letters, intercept messages, clerk NPC |
