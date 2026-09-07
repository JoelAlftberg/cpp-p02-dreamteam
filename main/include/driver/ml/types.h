<<<<<<< HEAD
=======
<<<<<<< Updated upstream
=======
>>>>>>> 49dbbf0 (Fix: Unified file casing to lowercase adaptive.h/cpp)
/**
 * @file Machine learning definitions and types.
 */
#pragma once

#include <cstdint>
#include <vector>

<<<<<<< HEAD
namespace driver::ml
=======
namespace ml
>>>>>>> 49dbbf0 (Fix: Unified file casing to lowercase adaptive.h/cpp)
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
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
>>>>>>> 49dbbf0 (Fix: Unified file casing to lowercase adaptive.h/cpp)
