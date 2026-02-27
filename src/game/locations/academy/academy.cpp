#include "game.hpp"

void registerAcademyMainGate(GameState &state);
void registerAcademyCourtyard(GameState &state);
void registerAcademyLectureHall(GameState &state);
void registerAcademyDuelingGround(GameState &state);
void registerAcademyDormitory(GameState &state);
void registerAcademyHeroineClassroom(GameState &state);
void registerAcademyArchive(GameState &state);
void registerAcademyRooftopGarden(GameState &state);

void buildAcademy(GameState &state)
{
    Area area;
    area.id = "academy";
    area.name = "The Academy";
    area.rooms = {
        "academy_main_gate", "academy_courtyard", "academy_lecture_hall",
        "academy_dueling_ground", "academy_dormitory", "academy_heroine_classroom",
        "academy_archive", "academy_rooftop_garden"};
    state.areas[area.id] = area;

    registerAcademyMainGate(state);
    registerAcademyCourtyard(state);
    registerAcademyLectureHall(state);
    registerAcademyDuelingGround(state);
    registerAcademyDormitory(state);
    registerAcademyHeroineClassroom(state);
    registerAcademyArchive(state);
    registerAcademyRooftopGarden(state);
}
