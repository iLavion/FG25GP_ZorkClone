#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct TestResult
{
    std::string name;
    bool passed;
    std::string message;
};

struct TestSuite
{
    std::string name;
    std::vector<std::pair<std::string, std::function<bool()>>> tests;
    std::vector<TestResult> results;
};

static int g_totalPassed = 0;
static int g_totalFailed = 0;

#define TEST_ASSERT(condition, msg)                                          \
    if (!(condition))                                                        \
    {                                                                        \
        std::cout << "    FAIL: " << msg << "\n";                            \
        std::cout << "      at " << __FILE__ << ":" << __LINE__ << "\n";     \
        return false;                                                        \
    }

#define TEST_ASSERT_EQ(actual, expected, msg)                                \
    if ((actual) != (expected))                                              \
    {                                                                        \
        std::cout << "    FAIL: " << msg << "\n";                            \
        std::cout << "      Expected: " << (expected) << "\n";               \
        std::cout << "      Actual:   " << (actual) << "\n";                 \
        std::cout << "      at " << __FILE__ << ":" << __LINE__ << "\n";     \
        return false;                                                        \
    }

static void runSuite(TestSuite &suite)
{
    std::cout << "\n=== " << suite.name << " ===\n";
    int passed = 0;
    int failed = 0;

    for (const auto &test : suite.tests)
    {
        std::cout << "  [RUN] " << test.first << "\n";
        bool result = false;
        try
        {
            result = test.second();
        }
        catch (const std::exception &e)
        {
            std::cout << "    EXCEPTION: " << e.what() << "\n";
            result = false;
        }
        catch (...)
        {
            std::cout << "    UNKNOWN EXCEPTION\n";
            result = false;
        }

        if (result)
        {
            std::cout << "  [PASS] " << test.first << "\n";
            passed++;
        }
        else
        {
            std::cout << "  [FAIL] " << test.first << "\n";
            failed++;
        }

        suite.results.push_back({test.first, result, ""});
    }

    g_totalPassed += passed;
    g_totalFailed += failed;
    std::cout << "  Results: " << passed << " passed, " << failed << " failed\n";
}
