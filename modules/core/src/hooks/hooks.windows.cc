#include <modmaid/core/hooks.hh>
#include <modmaid/core/logging.hh>

#include <MinHook.h>

namespace modmaid::hooks
{
    void Initialize()
    {
        MH_Initialize();
    }

    HookHandle RegisterTrampolineHook(void* address, void** original, void* hook)
    {
        auto createStatus = MH_CreateHook(address, hook, original);
        if (createStatus != MH_OK)
        {
            log::Trace("Failed to create trampoline hook @ %llx: %llx", address, createStatus);
        }
        auto enableStatus = MH_EnableHook(address);
        if (enableStatus != MH_OK)
        {
            log::Trace("Failed to enable trampoline hook @ %llx: %llx", address, enableStatus);
        }

        auto handle = AllocateHookHandle();
        (*GetMap())[handle] =
        {
            .Type = HookType::Trampoline,
            .IsEnabled = true,
            .TrampolineHook = {
                .Address = address
            }
        };

        return handle;
    }

    void UnregisterTrampolineHook(void* address)
    {
        MH_RemoveHook(address);
    }

    void ExitArch()
    {
    }
}
