/**
 * @file Test registry implementation details.
 */
#include <vector>

#include "yrgo/test/impl/case.h"
#include "yrgo/test/impl/registry.h"

namespace yrgo::test::impl
{
// -----------------------------------------------------------------------------
[[nodiscard]] Registry& Registry::instance() noexcept
{
    static Registry instance{};
    return instance;
}

// -----------------------------------------------------------------------------
bool Registry::add(const Case& testCase) noexcept
{
    // Check test case, return false if invalid or if it already exists.
    if (!testCase.isValid()) { return false; }
    if (caseExists(testCase)) { return false; }

    // Add new test case.
    myTestCases.push_back(testCase);
    return true;
}

// -----------------------------------------------------------------------------
const CaseList& Registry::testCases() const noexcept { return myTestCases; }

// -----------------------------------------------------------------------------
Registry::Registry() noexcept
    : myTestCases{}
{}

// -----------------------------------------------------------------------------
bool Registry::caseExists(const Case& testCase) const noexcept
{
    // Iterate through existing test cases, return true on match with the given test case.
    for (const auto& test : myTestCases)
    {
        if (testCase == test) { return true; }
    }
    return false;
}
} // namespace yrgo::test::impl
