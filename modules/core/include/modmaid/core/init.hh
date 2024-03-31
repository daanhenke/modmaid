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

        constexpr InitComponent All = Logging | Hooks | Configuration;
    }

    /**
     * Initializes the core library
     * @param flags A bitfield specifying which components need to be initialized
     */
    void InitializeModMaid(InitComponent flags);
    void ExitModMaid();

    void Unload();
}
