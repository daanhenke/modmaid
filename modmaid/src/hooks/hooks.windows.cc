#include <maid/hooks.hh>
#include <maid/logging.hh>

#include <MinHook.h>

namespace modmaid::hooks
{
    void Initialize()
    {
        MH_Initialize();
    }

    HookHandle RegisterTrampolineHook(void* address, void** original, void* hook)
    {
        auto res1 = MH_CreateHook(address, hook, original);
        auto res2 = MH_EnableHook(address);

        // TODO: RETURN HANDLE FOR UNHOOKING
        return 0;
    }
}
