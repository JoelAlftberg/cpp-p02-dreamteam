#pragma once

#include <cstdint>
#include <memory>


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

};

}
