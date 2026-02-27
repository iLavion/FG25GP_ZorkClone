#include "game.hpp"

void registerDukeAldric(GameState &state);
void registerElena(GameState &state);
void registerButlerGraves(GameState &state);
void registerMaidClara(GameState &state);
void registerCaptainRoderick(GameState &state);
void registerCedric(GameState &state);
void registerRosalind(GameState &state);
void registerChefMarcel(GameState &state);
void registerGardenerThorne(GameState &state);
void registerMadameFortuna(GameState &state);
void registerScholarElias(GameState &state);
void registerMerchantVera(GameState &state);
void registerFatherMatthias(GameState &state);
void registerBaronessVivienne(GameState &state);
void registerDockMasterHolt(GameState &state);

void buildNPCs(GameState &state)
{
    registerDukeAldric(state);
    registerElena(state);
    registerButlerGraves(state);
    registerMaidClara(state);
    registerCaptainRoderick(state);
    registerCedric(state);
    registerRosalind(state);
    registerChefMarcel(state);
    registerGardenerThorne(state);
    registerMadameFortuna(state);
    registerScholarElias(state);
    registerMerchantVera(state);
    registerFatherMatthias(state);
    registerBaronessVivienne(state);
    registerDockMasterHolt(state);
}
