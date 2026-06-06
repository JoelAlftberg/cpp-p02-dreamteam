#pragma once

namespace driver::wifi
{
struct Settings{};

class Interface 
{
public:
    virtual ~Interface() noexcept = default;
    virtual bool connect() noexcept = 0;
    virtual bool disconnect() noexcept = 0;
    virtual bool isConnected() const noexcept = 0;
};
}// namespace driver::wifi
