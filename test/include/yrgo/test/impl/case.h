/**
 * @file Test case.
 */
#pragma once

#include <string>

namespace yrgo::test::impl
{
/** Test function. */
using Func = void (*)();

/**
 * @brief Test case implementation.
 */
class Case final
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] suite Test suite.
     * @param[in] name Test name.
     * @param[in] func Test function.
     */
    explicit Case(const std::string& suite, const std::string& name, Func func) noexcept;

    /**
     * @brief Destructor.
     */
    ~Case() noexcept = default;

    /**
     * @brief Copy constructor.
     */
    Case(const Case& other) noexcept = default;

    /**
     * @brief Move constructor.
     */
    Case(Case&& other) noexcept = default;

    /**
     * @brief Match test cases.
     *
     * @param[in] other Test case to compare with.
     *
     * @return True on match, otherwise false.
     */
    bool operator==(const Case& other) const noexcept;

    /**
     * @brief Check if the test case is valid.
     *
     * @return True if valid, false otherwise.
     */
    bool isValid() const noexcept;

    /**
     * @brief Run test case.
     *
     * @return True on success, false on failure.
     */
    [[nodiscard]] bool run() const;

    Case& operator=(const Case&) = delete; // No copy assignment.
    Case& operator=(Case&&)      = delete; // No move assignment.

private:
    /** Test suite. */
    const std::string mySuite;

    /** Test name. */
    const std::string myName;

    /** Test function. */
    Func myFunc;
};
} // namespace yrgo::test::impl
