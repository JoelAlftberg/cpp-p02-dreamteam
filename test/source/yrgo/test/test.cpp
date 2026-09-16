/**
 * @file Test framework implementation details.
 */
#include <cstddef>
#include <iostream>

#include "yrgo/test/impl/case.h"
#include "yrgo/test/impl/registry.h"
#include "yrgo/test/test.h"

namespace yrgo::test
{
// -----------------------------------------------------------------------------
bool runAllTests()
{
    // Retrieve stored test cases, return false if missing.
    const auto& testCases = impl::Registry::instance().testCases();
    if (testCases.empty()) { return false; }
    std::size_t failedTests{};

    // Run each test case one by one, mark failure if at least one test failed.
    for (const auto& testCase : testCases)
    {
        if (!testCase.run()) { failedTests++; }
    }

    // Print summary, then return true if all tests succeeded.
    const auto succeededTests = testCases.size() - failedTests;
    std::cout << succeededTests << " out of " << testCases.size() << " test cases succeeded!\n";
    return 0U == failedTests;
}
} // namespace yrgo::test
