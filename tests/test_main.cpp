#include "test_framework.hpp"

TestSuite createUtilityTests();
TestSuite createGameStateTests();
TestSuite createEndingTests();

int main()
{
    std::cout << "======================================\n";
    std::cout << "  Villainess of the Empire Test Suite  \n";
    std::cout << "======================================\n";

    TestSuite utilities = createUtilityTests();
    runSuite(utilities);

    TestSuite gameState = createGameStateTests();
    runSuite(gameState);

    TestSuite endings = createEndingTests();
    runSuite(endings);

    std::cout << "\n======================================\n";
    std::cout << "  TOTAL: " << g_totalPassed << " passed, " << g_totalFailed << " failed\n";
    std::cout << "======================================\n";

    if (g_totalFailed > 0)
    {
        std::cout << "  SOME TESTS FAILED!\n";
        return 1;
    }
    else
    {
        std::cout << "  ALL TESTS PASSED!\n";
        return 0;
    }
}
