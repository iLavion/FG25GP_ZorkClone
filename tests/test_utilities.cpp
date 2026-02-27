#include "test_framework.hpp"
#include "utilities/string.hpp"
#include "core/room.hpp"
#include <stdexcept>

bool test_to_lower_basic()
{
    TEST_ASSERT_EQ(to_lower("HELLO"), "hello", "to_lower uppercase");
    TEST_ASSERT_EQ(to_lower("hello"), "hello", "to_lower already lowercase");
    TEST_ASSERT_EQ(to_lower("HeLLo WoRLd"), "hello world", "to_lower mixed case");
    return true;
}

bool test_to_lower_empty()
{
    TEST_ASSERT_EQ(to_lower(""), "", "to_lower empty string");
    return true;
}

bool test_to_lower_special_chars()
{
    TEST_ASSERT_EQ(to_lower("Hello123!@#"), "hello123!@#", "to_lower preserves non-alpha");
    return true;
}

bool test_to_upper_basic()
{
    TEST_ASSERT_EQ(to_upper("hello"), "HELLO", "to_upper lowercase");
    TEST_ASSERT_EQ(to_upper("HELLO"), "HELLO", "to_upper already uppercase");
    TEST_ASSERT_EQ(to_upper("HeLLo"), "HELLO", "to_upper mixed case");
    return true;
}

bool test_to_upper_empty()
{
    TEST_ASSERT_EQ(to_upper(""), "", "to_upper empty string");
    return true;
}

bool test_to_trim_whitespace()
{
    TEST_ASSERT_EQ(to_trim("  hello  "), "hello", "to_trim both sides");
    TEST_ASSERT_EQ(to_trim("hello  "), "hello", "to_trim trailing");
    TEST_ASSERT_EQ(to_trim("  hello"), "hello", "to_trim leading");
    return true;
}

bool test_to_trim_tabs_and_newlines()
{
    TEST_ASSERT_EQ(to_trim("\t hello \n"), "hello", "to_trim tabs and newlines");
    return true;
}

bool test_to_trim_empty()
{
    TEST_ASSERT_EQ(to_trim(""), "", "to_trim empty string");
    TEST_ASSERT_EQ(to_trim("   "), "", "to_trim only whitespace");
    return true;
}

bool test_to_trim_no_whitespace()
{
    TEST_ASSERT_EQ(to_trim("hello"), "hello", "to_trim no whitespace to remove");
    return true;
}

bool test_direction_from_string_full()
{
    TEST_ASSERT(direction_from_string("north") == Direction::North, "north");
    TEST_ASSERT(direction_from_string("south") == Direction::South, "south");
    TEST_ASSERT(direction_from_string("east") == Direction::East, "east");
    TEST_ASSERT(direction_from_string("west") == Direction::West, "west");
    TEST_ASSERT(direction_from_string("up") == Direction::Up, "up");
    TEST_ASSERT(direction_from_string("down") == Direction::Down, "down");
    return true;
}

bool test_direction_from_string_abbreviations()
{
    TEST_ASSERT(direction_from_string("n") == Direction::North, "n");
    TEST_ASSERT(direction_from_string("s") == Direction::South, "s");
    TEST_ASSERT(direction_from_string("e") == Direction::East, "e");
    TEST_ASSERT(direction_from_string("w") == Direction::West, "w");
    TEST_ASSERT(direction_from_string("u") == Direction::Up, "u");
    TEST_ASSERT(direction_from_string("d") == Direction::Down, "d");
    return true;
}

bool test_direction_from_string_case_insensitive()
{
    TEST_ASSERT(direction_from_string("NORTH") == Direction::North, "NORTH uppercase");
    TEST_ASSERT(direction_from_string("North") == Direction::North, "North mixed");
    TEST_ASSERT(direction_from_string("N") == Direction::North, "N uppercase");
    return true;
}

bool test_direction_from_string_invalid()
{
    bool threw = false;
    try
    {
        direction_from_string("nowhere");
    }
    catch (const std::invalid_argument &)
    {
        threw = true;
    }
    TEST_ASSERT(threw, "direction_from_string should throw for invalid input");
    return true;
}

bool test_direction_to_string()
{
    TEST_ASSERT_EQ(direction_to_string(Direction::North), "north", "North to string");
    TEST_ASSERT_EQ(direction_to_string(Direction::South), "south", "South to string");
    TEST_ASSERT_EQ(direction_to_string(Direction::East), "east", "East to string");
    TEST_ASSERT_EQ(direction_to_string(Direction::West), "west", "West to string");
    TEST_ASSERT_EQ(direction_to_string(Direction::Up), "up", "Up to string");
    TEST_ASSERT_EQ(direction_to_string(Direction::Down), "down", "Down to string");
    return true;
}

bool test_direction_roundtrip()
{
    std::string dirs[] = {"north", "south", "east", "west", "up", "down"};
    for (const auto &d : dirs)
    {
        Direction dir = direction_from_string(d);
        std::string back = direction_to_string(dir);
        TEST_ASSERT_EQ(back, d, "roundtrip for " + d);
    }
    return true;
}

TestSuite createUtilityTests()
{
    TestSuite suite;
    suite.name = "Utility Functions";
    suite.tests = {
        {"to_lower - basic", test_to_lower_basic},
        {"to_lower - empty", test_to_lower_empty},
        {"to_lower - special chars", test_to_lower_special_chars},
        {"to_upper - basic", test_to_upper_basic},
        {"to_upper - empty", test_to_upper_empty},
        {"to_trim - whitespace", test_to_trim_whitespace},
        {"to_trim - tabs and newlines", test_to_trim_tabs_and_newlines},
        {"to_trim - empty", test_to_trim_empty},
        {"to_trim - no whitespace", test_to_trim_no_whitespace},
        {"direction_from_string - full names", test_direction_from_string_full},
        {"direction_from_string - abbreviations", test_direction_from_string_abbreviations},
        {"direction_from_string - case insensitive", test_direction_from_string_case_insensitive},
        {"direction_from_string - invalid throws", test_direction_from_string_invalid},
        {"direction_to_string", test_direction_to_string},
        {"direction roundtrip", test_direction_roundtrip},
    };
    return suite;
}
