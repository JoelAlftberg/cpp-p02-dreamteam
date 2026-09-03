#pragma once

// Note: std::size_t is defined in <cstddef>. Don't rely on indirect includes from other 
// headers, include <cstddef> explicitly when using std::size_t.
#include <cstddef>

namespace driver::utils 
{
template <typename T>
constexpr std::size_t to_idx(const T e) noexcept 
{
    return static_cast<std::size_t>(e);
}
} driver::utils 
