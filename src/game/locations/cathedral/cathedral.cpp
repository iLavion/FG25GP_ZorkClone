#include "game.hpp"

void registerCathedralNave(GameState &state);
void registerCathedralConfessional(GameState &state);
void registerCathedralSideChapel(GameState &state);
void registerCathedralClergyOffice(GameState &state);
void registerCathedralCrypt(GameState &state);
void registerCathedralCharityKitchen(GameState &state);

void buildCathedral(GameState &state)
{
    Area area;
    area.id = "cathedral";
    area.name = "The Cathedral";
    area.rooms = {
        "cathedral_nave", "cathedral_confessional", "cathedral_side_chapel",
        "cathedral_clergy_office", "cathedral_crypt", "cathedral_charity_kitchen"};
    state.areas[area.id] = area;

    registerCathedralNave(state);
    registerCathedralConfessional(state);
    registerCathedralSideChapel(state);
    registerCathedralClergyOffice(state);
    registerCathedralCrypt(state);
    registerCathedralCharityKitchen(state);
}
