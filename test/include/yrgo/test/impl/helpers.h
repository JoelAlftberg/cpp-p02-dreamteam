/**
 * @file Test framework helpers.
 */
#pragma once

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace yrgo::test::impl
{
/**
 * @brief Format a value for a failure message, promoting narrow character types to an integer.
 *
 *        A std::uint8_t (unsigned char) otherwise streams as a character glyph rather than a
 *        number, which is unhelpful in an assertion message.
 *
 * @tparam T Type of the value.
 *
 * @param[in] value The value to format.
 *
 * @return The value cast to int if it is a character type, otherwise the value unchanged.
 */
template<typename T>
[[nodiscard]] inline auto forDisplay(const T value) noexcept
{
    // 8-bit integers cannot be printed with std::ostream: convert to int.
    if constexpr (std::is_same<T, char>::value || std::is_same<T, unsigned char>::value ||
                  std::is_same<T, signed char>::value)
    {
        return static_cast<int>(value);
    }
    else { return value; }
}

/**
 * @brief Expect values to match.
 *
 * @tparam A Type of the first value.
 * @tparam B Type of the second value.
 *
 * @param[in] a The first value.
 * @param[in] b The second value.
 * @param[in] assertion Stringized assertion expression.
 * @param[in] file Source file of the assertion.
 * @param[in] line Source line of the assertion.
 */
template<typename A, typename B>
inline void expectEq(const A& a, const B& b, const char* assertion, const char* file,
                     const int line)
{
    // Compare a and b, throw an error if not equal.
    if (a != b)
    {
        std::ostringstream ostream{};
        ostream << std::boolalpha << assertion << " failed: " << forDisplay(a)
                << " != " << forDisplay(b) << " (" << file << ":" << line << ")";
        throw std::runtime_error(ostream.str());
    }
}

/**
 * @brief Expect values to not match.
 *
 * @tparam A Type of the first value.
 * @tparam B Type of the second value.
 *
 * @param[in] a The first value.
 * @param[in] b The second value.
 * @param[in] assertion Stringized assertion expression.
 * @param[in] file Source file of the assertion.
 * @param[in] line Source line of the assertion.
 */
template<typename A, typename B>
inline void expectNe(const A& a, const B& b, const char* assertion, const char* file,
                     const int line)
{
    // Compare a and b, throw an error if equal.
    if (a == b)
    {
        std::stringstream ostream{};
        ostream << std::boolalpha << assertion << " failed: " << forDisplay(a)
                << " == " << forDisplay(b) << " (" << file << ":" << line << ")";
        throw std::runtime_error(ostream.str());
    }
}

/**
 * @brief Expect values to be within the given threshold.
 *
 * @tparam A Type of the first value.
 * @tparam B Type of the second value.
 * @tparam T Type of the tolerance values.
 *
 * @param[in] a The first value. Must be arithmetic.
 * @param[in] b The second value. Must be arithmetic.
 * @param[in] tol Tolerance. Must be arithmetic.
 * @param[in] assertion Stringized assertion expression.
 * @param[in] file Source file of the assertion.
 * @param[in] line Source line of the assertion.
 */
template<typename A, typename B, typename T>
inline void expectNear(const A& a, const B& b, const T& tol, const char* assertion,
                       const char* file, const int line)
{
    // Check value types, generate a compiler error if at least one of them is not arithmetic.
    constexpr auto arithmetic = std::is_arithmetic<A>::value && std::is_arithmetic<B>::value &&
                                std::is_arithmetic<T>::value;
    static_assert(arithmetic, "EXPECT_NEAR() supports arithmetic values only!");

    // Compute the absolute value of the difference between a and b.
    const auto diff = std::abs(a - b);

    // Throw an error if the difference exceeds the tolerance.
    if (diff > tol)
    {
        std::ostringstream ostream{};
        ostream << assertion << " failed: |" << forDisplay(a) << " - " << forDisplay(b)
                << "| = " << forDisplay(diff) << " > " << forDisplay(tol) << " (" << file << ":"
                << line << ")";
        throw std::runtime_error(ostream.str());
    }
}
} // namespace yrgo::test::impl
