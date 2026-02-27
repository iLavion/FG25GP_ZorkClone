#include "game.hpp"
#include <iostream>

void registerLibrary(GameState &state)
{
    Room r;
    r.id = "library";
    r.name = "Library";
    r.description = "Floor-to-ceiling bookshelves filled with histories, poetry, and forbidden\n"
                    "texts. A cozy reading nook overlooks the garden through tall windows.\n"
                    "The Grand Hall is east, Father's Study is west.";
    r.area_id = "ducal_estate";
    r.exits = {
        {Direction::East, "grand_hall"},
        {Direction::West, "fathers_study"}};
    r.travel_time = 2;
    state.rooms[r.id] = r;

    state.rooms["library"].item_ids.push_back("letter");
    state.rooms["library"].item_ids.push_back("book_alchemy");
    state.rooms["library"].item_ids.push_back("book_persuasion");
    state.rooms["library"].item_ids.push_back("book_stealth");
    state.rooms["library"].item_ids.push_back("book_nobility");

    registerRoomActions(
        "library",
        {{"Browse the bookshelves",
          nullptr,
          [](GameState &gs)
          {
              (void)gs;
              std::cout << "You run your fingers along the spines of countless volumes.\n";
              std::cout << "Histories, poetry, forbidden texts... and a few titles on\n";
              std::cout << "poisons and court intrigue catch your eye.\n";
              std::cout << "\n  [i] Use READ <book> to study a book from your inventory.\n";
          }},
         {"Read by the window",
          nullptr,
          [](GameState &gs)
          {
              std::cout << "You settle into the reading nook by the tall windows.\n";
              std::cout << "The garden stretches out below, bathed in soft light.\n";
              std::cout << "A moment of peace in an otherwise treacherous world.\n";
              advanceTime(gs, 10);
          }}});
}
