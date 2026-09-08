/**
 * @file Linear regression model interface.
 */
#pragma once

namespace ml::lin_reg
{
/**
 * @brief Linear regression model interface.
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Predict based on the given input.
     *
     * @param[in] input Input to predict with.
     *
     * @return Predicted output.
     */
    [[nodiscard]] virtual double predict(double input) const noexcept = 0;
};
} // namespace ml::lin_reg