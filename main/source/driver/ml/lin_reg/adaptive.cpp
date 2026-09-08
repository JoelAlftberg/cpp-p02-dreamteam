/**
 * @file Linear regression model with fixed learning rate.
 */
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <cmath>

#include "driver/ml/lin_reg/adaptive.h"
#include "driver/ml/types.h"

namespace ml::lin_reg
{
namespace
{
// -----------------------------------------------------------------------------
void initRandom() noexcept
{
    // Only initialize the random generator once.
    static bool initialized{false};
    if (initialized) { return; }

    // Initialize the random generator with the current timestamp as seed.
    std::srand(std::time(nullptr));
    initialized = true;
}
} // namespace

// -----------------------------------------------------------------------------
Adaptive::Adaptive(const Matrix1d& trainIn, const Matrix1d& trainOut) noexcept
    : myTrainOrder{}
    , myTrainIn{trainIn}
    , myTrainOut{trainOut}
    , myBias{}
    , myWeight{}
{
    const auto setCount = std::min(trainIn.size(), trainOut.size());

    if (0U == setCount)
    {
        std::fprintf(stderr, "Cannot create regression model without training data!\n");
        std::terminate();
    }

    // Initialize training order vector with indexes of the training sets.
    myTrainOrder.resize(setCount);

    for (std::uint32_t i{}; i < setCount; ++i)
    {
        myTrainOrder[i] = i;
    }

    // Initialize random generator (occurs only once).
    initRandom();
}

// -----------------------------------------------------------------------------
double Adaptive::predict(const double input) const noexcept { return myWeight * input + myBias; }

// -----------------------------------------------------------------------------
bool Adaptive::train(const std::size_t epochCount, 
                    const double learningRate, 
                    const double precisionThreshold) noexcept
{
    
    // Check epoch count, return false if 0.
    if (0U == epochCount) { return false; }

    // Check learning rate, return false if outside range (0.0, 1.0).
    if ((0.0 >= learningRate) || (1.0 <= learningRate)) { return false; }

    if((0.0 >= precisionThreshold) || (1.0 <= precisionThreshold)) { return false; }
    double currentLearningRate = learningRate;
    double previousPrecision{};

    for (std::size_t epoch{}; epoch < epochCount; ++epoch){

        shuffle();

        for (const auto i : myTrainOrder){
            const auto input  = myTrainIn[i];
            const auto output = myTrainOut[i];
            optimize(input, output, currentLearningRate);
        }
        const auto precision = computePrecision();

        // Check if precision threshold has been reached.
        if (precision >= precisionThreshold){
            std::printf(
                "Finished training with precision %g after %zu epochs!\n",
                precision,
                epoch + 1U);
            return true;
        }
        // Adapt learning rate.
        if (precision > previousPrecision){
            currentLearningRate *= 1.05;
        }else{
            currentLearningRate *= 0.5;
        }

        // Save precision for next epoch.
        previousPrecision = precision;
    }

    return true;
}

// -----------------------------------------------------------------------------
void Adaptive::optimize(const double input, const double output, const double learningRate) noexcept
{
    // m == yref if x == 0.
    if (0.0 == input)
    {
        myBias = output;
        return;
    }

    const auto prediction = predict(input);      // yp = kx + m.
    const auto error      = output - prediction; // e  = yref - yp.
    myBias += error * learningRate;              // m  = m + e * LR
    myWeight += error * learningRate * input;    // k  = k + e * LR * x
}

// -----------------------------------------------------------------------------
void Adaptive::shuffle() noexcept
{
    // Iterate through all training sets, swap each index i with a random index r.
    for (std::size_t i{}; i < myTrainOrder.size(); ++i)
    {
        const auto r    = std::rand() % myTrainOrder.size();
        const auto temp = myTrainOrder[i];
        myTrainOrder[i] = myTrainOrder[r];
        myTrainOrder[r] = temp;
    }
}
double Adaptive::computePrecision() const noexcept{
    double sum{};

    for(std::size_t i{}; i < myTrainOrder.size(); ++i){
        const auto input            = myTrainIn[i];
        const auto output           = myTrainOut[i];
        const auto prediction       = predict(input);

        const auto error     =  std::abs(output - prediction);
        sum += error;
    }
    const auto avgError = sum / myTrainOrder.size();
    return 1.0 - avgError;
}
} // namespace ml::lin_reg
