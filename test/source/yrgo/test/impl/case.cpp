/**
 * @file Test case implementation details.
 */
#include <iostream>
#include <stdexcept>
#include <string>

#include "yrgo/test/impl/case.h"

namespace yrgo::test::impl
{
// -----------------------------------------------------------------------------
Case::Case(const std::string& suite, const std::string& name, Func func) noexcept
    : mySuite{suite}
    , myName{name}
    , myFunc{func}
{}

// -----------------------------------------------------------------------------
bool Case::operator==(const Case& other) const noexcept
{
    return (other.mySuite == mySuite) && (other.myName == myName);
}

// -----------------------------------------------------------------------------
bool Case::isValid() const noexcept
{
    return !mySuite.empty() && !myName.empty() && (nullptr != myFunc);
}

// -----------------------------------------------------------------------------
[[nodiscard]] bool Case::run() const
{
    constexpr const char* green{"\033[32m"};
    constexpr const char* red{"\033[31m"};
    constexpr const char* noColor{"\033[0m"};
    const std::string name{mySuite + "." + myName};
    if (!isValid()) { return false; }

    // Run test, print success message in green on success.
    try
    {
        myFunc();
        std::cout << green << "Test case " << name << " succeeded!" << noColor << "\n";
        return true;
    }
    // Print red error message on failure.
    catch (std::exception& e)
    {
        std::cout << red << "Test case " << name << " failed: " << e.what() << noColor << "\n";
        return false;
    }
}
} // namespace yrgo::test::impl
