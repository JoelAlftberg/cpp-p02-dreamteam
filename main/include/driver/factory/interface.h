#pragma once

#include <cstdint>
#include <memory>

namespace driver
{
    namespace adc { class Interface; }
    namespace gpio { class Interface; }
    namespace serial { class Interface; }
    namespace timer { class Interface; }
    namespace tempsensor { class Interface; }
    namespace config { class Interface; }
} // namespace driver

namespace driver::factory
{

class Interface
{
public:

    virtual ~Interface() noexcept = default;

    virtual std::unique_ptr<adc::Interface> adc(const config::Interface& config) noexcept = 0;

    virtual std::unique_ptr<gpio::Interface> gpio(const config::Interface& config) noexcept = 0;

    virtual std::unique_ptr<serial::Interface> serial(const config::Interface& config) noexcept = 0;

    virtual std::unique_ptr<timer::Interface> timer(const config::Interface& config) noexcept = 0;

    virtual std::unique_ptr<tempsensor::Interface> tempsensor(
            const config::Interface& config,
            adc::Interface& adc
            ) noexcept = 0;

};

}
