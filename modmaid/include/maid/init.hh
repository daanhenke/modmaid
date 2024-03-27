#pragma once

#include <cstddef>

namespace modmaid
{
    using InitComponent = std::size_t;

    namespace init
    {
        constexpr InitComponent Logging = 0x1;
        constexpr InitComponent WindowsConsoleHost = 0x2;

        constexpr InitComponent Hooks = 0x4;
        constexpr InitComponent Configuration = 0x8;

        constexpr InitComponent Base = Logging | Hooks | Configuration;
    }

    void InitializeModMaid(InitComponent flags);
    void ExitModMaid();

    void Unload();
}
