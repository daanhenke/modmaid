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
        MH_CreateHook(address, hook, original);
        MH_EnableHook(address);

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
