#include "game.hpp"

void registerBedroom(GameState &state);
void registerHallway(GameState &state);
void registerGrandHall(GameState &state);
void registerKitchen(GameState &state);
void registerDiningRoom(GameState &state);
void registerLibrary(GameState &state);
void registerGarden(GameState &state);
void registerCourtyard(GameState &state);
void registerServantsQuarters(GameState &state);
void registerFathersStudy(GameState &state);
void registerSiblingsRoom(GameState &state);
void registerGuestRoom(GameState &state);
void registerBalcony(GameState &state);
void registerCellar(GameState &state);

void buildVillage(GameState &state);
void buildCity(GameState &state);
void buildAcademy(GameState &state);
void buildCathedral(GameState &state);
void buildNobleQuarter(GameState &state);
void buildPalace(GameState &state);
void buildBarracks(GameState &state);
void buildDocks(GameState &state);
void buildForest(GameState &state);

void buildRooms(GameState &state)
{
    Area estate;
    estate.id = "ducal_estate";
    estate.name = "The Ducal Estate";
    estate.rooms = {
        "bedroom", "hallway", "grand_hall", "kitchen", "dining_room",
        "library", "garden", "courtyard", "servants_quarters",
        "fathers_study", "siblings_room", "guest_room", "balcony", "cellar"};
    state.areas[estate.id] = estate;

    registerBedroom(state);
    registerHallway(state);
    registerGrandHall(state);
    registerKitchen(state);
    registerDiningRoom(state);
    registerLibrary(state);
    registerGarden(state);
    registerCourtyard(state);
    registerServantsQuarters(state);
    registerFathersStudy(state);
    registerSiblingsRoom(state);
    registerGuestRoom(state);
    registerBalcony(state);
    registerCellar(state);

    buildVillage(state);
    buildCity(state);
    buildAcademy(state);
    buildCathedral(state);
    buildNobleQuarter(state);
    buildPalace(state);
    buildBarracks(state);
    buildDocks(state);
    buildForest(state);
}
