# Ducal Estate - Ground Floor (1F)

```mermaid
graph TD
    subgraph Ground Floor
        FS[Father's Study]
        LIB[Library]
        GH[Grand Hall]
        DR[Dining Room]
        KIT[Kitchen]
        CY[Courtyard]
        SQ[Servants' Quarters]
        GAR[Garden]
        CEL[Cellar]
    end

    FS -->|East| LIB
    LIB -->|East| GH
    GH -->|East| DR
    DR -->|North| KIT
    KIT -->|Down| CEL

    GH -->|South| CY
    CY -->|East| SQ
    CY -->|South| GAR

    LIB -->|West| FS
    GH -->|West| LIB
    DR -->|West| GH
    KIT -->|South| DR
    CEL -->|Up| KIT

    CY -->|North| GH
    SQ -->|West| CY
    GAR -->|North| CY

    GH -->|Up| HALL["Hallway (2F) ⬆"]

    GAR -->|South| EG["Estate Gate (to Village)"]

    style GH fill:#FFD700,color:#000
    style GAR fill:#90EE90,color:#000
    style CEL fill:#808080,color:#fff
    style FS fill:#DEB887,color:#000
    style EG fill:#FF6347,color:#fff

    subgraph Second Floor
        SR[Sibling's Room]
        GR[Guest Room]
        HALL[Hallway]
        BED[Bedroom]
        BAL[Balcony]
    end

    SR -->|South| HALL
    HALL -->|North| SR

    GR -->|East| HALL
    HALL -->|West| GR

    HALL -->|East| BED
    BED -->|West| HALL

    BED -->|East| BAL
    BAL -->|West| BED

    HALL -->|Down| GH["Grand Hall (1F)"]

    style BED fill:#FF69B4,color:#000
    style HALL fill:#87CEEB,color:#000
    style BAL fill:#FFD700,color:#000
    style GR fill:#DDA0DD,color:#000
    style SR fill:#98FB98,color:#000
```

## Room Details

| Room | Travel Time | Key Features |
|------|------------|--------------|
| Grand Hall | 4 min | Central hub, chandelier, social area. Stairs up to 2F. |
| Library | 2 min | Books, reading nook, connects Study and Grand Hall. |
| Father's Study | 2 min | Duke's desk, maps, locked documents. Dead end west. |
| Dining Room | 2 min | Formal meals, place cards, leads to Kitchen. |
| Kitchen | 2 min | Chef Marcel's domain, locked cabinet. Stairs to Cellar. |
| Cellar | 3 min | Wine storage, poison, hidden passage hints. |
| Courtyard | 5 min | Guard patrols, fountain, main outdoor hub. |
| Servants' Quarters | 3 min | Staff quarters, gossip, duty roster. |
| Garden | 8 min | Gardener Thorne, hedge maze, nightshade. Exit to Village. |
