/**
 * @file Machine learning definitions and types.
 */
#pragma once

#include <cstdint>
#include <vector>

namespace ml
{
/** One-dimensional matrix. */
using Matrix1d = std::vector<double>;

/** Two-dimensional matrix. */
using Matrix2d = std::vector<Matrix1d>;

/** Three-dimensional matrix. */
using Matrix3d = std::vector<Matrix2d>;

/** Matrix holding unsigned integers. */
using MatrixU32 = std::vector<std::uint32_t>;

} // namespace ml
