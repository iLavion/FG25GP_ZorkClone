# Academy

```mermaid
graph TD
    subgraph Academy
        MG[Main Gate]
        ACY[Academy Courtyard]
        LH[Lecture Hall]
        DG[Dueling Ground]
        DH[Dormitory Hall]
        HC[Heroine's Classroom]
        AR[Archive Room]
        RG[Rooftop Garden]
    end

    MG -->|North| ACY
    ACY -->|South| MG

    ACY -->|North| LH
    LH -->|South| ACY

    ACY -->|East| DG
    DG -->|West| ACY

    ACY -->|West| DH
    DH -->|East| ACY

    LH -->|East| HC
    HC -->|West| LH

    LH -->|Up| AR
    AR -->|Down| LH

    AR -->|Up| RG
    RG -->|Down| AR

    MG -->|"South (far)"| CP["Central Plaza (to City Market)"]

    style ACY fill:#4169E1,color:#fff
    style HC fill:#FF69B4,color:#fff
    style RG fill:#90EE90,color:#000
    style DG fill:#CD5C5C,color:#fff
```

## Room Details

| Room | ID | Travel Time | Exits | Features |
|------|----|------------|-------|----------|
| Main Gate | academy_main_gate | 2 min | N -> Courtyard | Entrance, gate guard, bulletin board, exit to City |
| Academy Courtyard | academy_courtyard | 3 min | S -> Gate, N -> Lecture Hall, E -> Dueling, W -> Dormitory | Open area, students socializing, fountain |
| Lecture Hall | academy_lecture_hall | 2 min | S -> Courtyard, E -> Heroine's Classroom, Up -> Archive | Classes in session, professor NPC, intel on Elena |
| Dueling Ground | academy_dueling_ground | 3 min | W -> Courtyard | Practice swords, challenge rivals, reputation events |
| Dormitory Hall | academy_dormitory | 2 min | E -> Courtyard | Student rooms, gossip, sleep (if enrolled) |
| Heroine's Classroom | academy_heroine_classroom | 2 min | W -> Lecture Hall | Elena's study space, her notes, social sabotage |
| Archive Room | academy_archive | 3 min | Down -> Lecture Hall, Up -> Rooftop | Historical records, blackmail material, restricted texts |
| Rooftop Garden | academy_rooftop_garden | 2 min | Down -> Archive | Quiet spot, secret meetings, scenic overlook |
