#pragma once

#include <cstdint>
#include "driver/tempsensor/interface.h"
#include "temperature_sensor.h"

namespace driver::tempsensor{

class Esp32s3 final : public Interface{
public:
    /**
     * @brief Constructor.
     */
    explicit Esp32s3() noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override = default;
    std::int16_t readCelsius() const noexcept override;
    void start() noexcept override;
    void stop() noexcept override;

private:
    temperature_sensor_handle_t handle;
};

} // namespace driver::tempsensor