<<<<<<< HEAD
#pragma once
#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/interface.h"

namespace driver::tempsensor{

struct StubSettings final : public Settings 
{

};                     

class Stub final : public Interface {
public:
    Stub() noexcept
        : status{false},
        myTemp{0U}
    {
        std::printf("Stub temperature sensor created.\n");
    }

    ~Stub() noexcept override
    {
        std::printf("Stub temperature sensor destroyed.\n");
    }
   
    std::int16_t readCelsius() const noexcept override{
        if (!status) return 0;
        return myTemp;

    }

    void start() noexcept override {
        status = true;
    }

    void stop() noexcept override {
        status = false;

    }
    void simulatemyTemp(std::int16_t temp) noexcept { 
        myTemp = temp;
    }
 
    Stub(const Stub&)                   = delete;
    Stub(Stub&&)                        = delete;
    Stub& operator=(const Stub&)        = delete;
    Stub& operator=(Stub&&)             = delete;

private:
    bool status;
    std::int16_t myTemp;
};
} // namespace driver::tempsensor
=======
#pragma once
#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/interface.h"

namespace driver::tempsensor{

struct StubSettings final : public Settings 
{

};                     

class Stub final : public Interface {
public:
    explicit Stub() noexcept
        : status{false},
        myTemp{0U}
    {
        std::printf("Stub temperature sensor created.\n");
    }

    ~Stub() noexcept override
    {
        std::printf("Stub temperature sensor destroyed.\n");
    }
   
    std::int16_t readCelsius() const noexcept override{
        if (!status) return 0;
        return myTemp;

    }

    void start() noexcept override {
        status = true;
    }

    void stop() noexcept override {
        status = false;

    }
    void simulatemyTemp(std::int16_t temp) noexcept { 
        myTemp = temp;
    }
 
    Stub(const Stub&)                   = delete;
    Stub(Stub&&)                        = delete;
    Stub& operator=(const Stub&)        = delete;
    Stub& operator=(Stub&&)             = delete;

private:
    bool status;
    std::int16_t myTemp;
};
} // namespace driver::tempsensor
>>>>>>> f06c0de (did som changes)
