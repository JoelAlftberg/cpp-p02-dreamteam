/**
 * @file Linear regression model interface.
 */
#pragma once
#include <cstddef>

#include "driver/ml/lin_reg/interface.h"
#include "driver/ml/types.h"

namespace ml::lin_reg
{
/**
 * @brief Linear regression model interface.
 */
class Adaptive final : public Interface 
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] trainIn Training input data.
     * @param[in] trainOut Training output data.
     */
    explicit Adaptive(const Matrix1d& trainIn, const Matrix1d& trainOut) noexcept;

    /**
     * @brief Destructor.
     */
    ~Adaptive() noexcept = default;

    /**
     * @brief Predict based on the given input.
     *
     * @param[in] input Input to predict with.
     *
     * @return Predicted output.
     */
    [[nodiscard]] double predict(double input) const noexcept override;
     /**
     * @brief Train the model for the given number of epochs.
     *
     * @param[in] epochCount Number of epochs to train the model. Must be greater than 0.
     * @param[in] learningRate Learning rate to use. Must be in range (0.0, 1.0), non-inclusive.
     * @param[in] precisionThreshold
     *
     * @return True if training was performed, false if input argument is invalid.
     */
    bool train(std::size_t epochCount, double learningRate = 0.01,
                double precisionThreshold = 0.999999) noexcept;

    Adaptive()                           = delete; // No default constructor.
    Adaptive(const Adaptive&)            = delete; // No copy constructor.
    Adaptive(Adaptive&&)                 = delete; // No move constructor.
    Adaptive& operator=(const Adaptive&) = delete; // No copy assignment.
    Adaptive& operator=(Adaptive&&)      = delete; // No move assignment.
private:
    /**
     * @brief Adjust the trainable parameters.
     *
     * @param[in] input Input value (x).
     * @param[in] output Output value (yref).
     * @param[in] learningRate Learning rate.
     */
    void optimize(double input, double output, double learningRate) noexcept;

    /**
     * @brief Shuffle training order index list.
     */
    void shuffle() noexcept;
    [[nodiscard]] double computePrecision() const noexcept;

    /** Matrix holding the training order via index. */
    MatrixU32 myTrainOrder;

    /** Matrix holding training inputs. */
    const Matrix1d& myTrainIn;

    /** Matrix holding training outputs. */
    const Matrix1d& myTrainOut;

    /** Bias value (m). */
    double myBias;

    /** Weight value (k). */
    double myWeight;

};
} // namespace ml::lin_reg
