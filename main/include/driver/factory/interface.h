#pragma once

#include <cstdint>
#include <memory>

namespace driver
{
    namespace adc { class Interface; struct Settings; }
    namespace gpio { class Interface; struct Settings; }
    namespace serial { class Interface; struct Settings; }
    namespace timer { class Interface; struct Settings; }
    namespace tempsensor { class Interface; struct Settings;}
    namespace config { class Interface; struct Settings;}
} // namespace driver

namespace driver::factory
{

class Interface
{
public:

    virtual ~Interface() noexcept = default;

    virtual std::unique_ptr<adc::Interface> adc(const adc::Settings& settings) const noexcept = 0;

    virtual std::unique_ptr<gpio::Interface> gpio(const gpio::Settings& settings) const noexcept = 0;

    virtual std::unique_ptr<serial::Interface> serial(const serial::Settings& settings) const noexcept = 0;

    virtual std::unique_ptr<timer::Interface> timer(const timer::Settings& settings) const noexcept = 0;

    virtual std::unique_ptr<tempsensor::Interface> tempsensor(
            const tempsensor::Settings& settings
            ) const noexcept = 0;

};

}
