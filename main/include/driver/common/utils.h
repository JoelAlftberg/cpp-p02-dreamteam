#pragma once

namespace driver::utils 
{

template <typename T>
constexpr size_t to_idx(T e) noexcept {
    return static_cast<size_t>(e);
}
}
