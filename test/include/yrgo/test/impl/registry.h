/**
 * @file Test registry.
 */
#pragma once

#include <vector>

#include "yrgo/test/impl/case.h"

namespace yrgo::test::impl
{
/** Test case list. */
using CaseList = std::vector<Case>;

/**
 * @brief Singleton registry of test cases.
 */
class Registry final
{
public:
    /**
     * @brief Get test registry.
     *
     * @return Reference to the singleton test registry.
     */
    [[nodiscard]] static Registry& instance() noexcept;

    /**
     * @brief Add new test case.
     *
     * @param[in] testCase Test case to add.
     *
     * @return True if the test case was added, false otherwise.
     */
    bool add(const Case& testCase) noexcept;

    /**
     * @brief Get test cases.
     *
     * @return Stored test cases.
     */
    const CaseList& testCases() const noexcept;

    Registry(const Registry&)            = delete; // No copy constructor.
    Registry(Registry&&)                 = delete; // No move constructor.
    Registry& operator=(const Registry&) = delete; // No copy assignment.
    Registry& operator=(Registry&&)      = delete; // No move assignment.

private:
    Registry() noexcept;
    ~Registry() noexcept = default;

    bool caseExists(const Case& testCase) const noexcept;

    /** Stored test cases. */
    CaseList myTestCases;
};
} // namespace yrgo::test::impl
