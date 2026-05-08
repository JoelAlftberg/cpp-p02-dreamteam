#pragma once

#include <cstdint>
#include <memory>

// Fördeklarationer av alla drivargränssnitt, så att vi kan returnera pekare till dem i 
// fabriksgränssnittet utan att behöva inkludera deras fulla definitioner här.
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

    virtual std::unique_ptr<adc::Interface> adc() noexcept = 0;

    virtual std::unique_ptr<gpio::Interface> gpio() noexcept = 0;

    virtual std::unique_ptr<serial::Interface> serial() noexcept = 0;

    virtual std::unique_ptr<timer::Interface> timer() noexcept = 0;

    virtual std::unique_ptr<tempsensor::Interface> tempsensor() noexcept = 0;

    virtual std::unique_ptr<config::Interface> config() noexcept = 0;
};

}
