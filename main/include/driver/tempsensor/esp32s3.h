#pragma once

#include <cstdint>
#include "driver/tempsensor/interface.h"
#include "hal/temperature_sensor_types.h"
#include "driver/temperature_sensor.h"


namespace driver::tempsensor
{

struct Esp32s3Settings final : public Settings
{

};                     

class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    explicit Esp32s3() noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override;
    std::int16_t readCelsius() const noexcept override;
    void start() noexcept override;
    void stop() noexcept override;
    Esp32s3()                         = delete;
    Esp32s3(const Esp32s3&)           = delete;
    Esp32s3(Esp32s3&&)                = delete;
    Esp32s3 operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)     = delete;

private:
    temperature_sensor_handle_t handle{};
    bool myState {false};
};

} // namespace driver::tempsensor
