#include <modmaid/core/hooks.hh>
#include <modmaid/core/logging.hh>

namespace modmaid::hooks
{
  std::map<HookHandle, HookDescriptor>* GetMap()
  {
    static std::map<HookHandle, HookDescriptor> map;
    return &map;
  }

  HookHandle AllocateHookHandle()
  {
    static HookHandle nextHandle = 0;
    return nextHandle++;
  }

  HookHandle RegisterVTableHook(void** vtable, std::size_t index, void** original, void* hook)
  {
    memory::ReprotectMemory(vtable, (index + 1) * sizeof(void*), memory::MemoryProtection::All);

    *original = vtable[0];
    vtable[0] = hook;

    auto handle = AllocateHookHandle();
    (*GetMap())[handle] =
    {
      .Type = HookType::VTable,
      .IsEnabled = true,
      .VTableHook = {
        .VTable = vtable,
        .Index = index,
        .Original = vtable[0],
        .Hook = hook,
      }
    };

    return handle;
  }

  HookHandle RegisterVTableHookFromInstance(void* instance, std::size_t index, void** original, void* hook)
  {
    auto vtable = reinterpret_cast<void**>(
      *reinterpret_cast<void***>(instance)
    );

    return RegisterVTableHook(vtable, index, original, hook);
  }

  void UnregisterHook(HookHandle handle)
  {
    auto& entry = (*GetMap())[handle];

    switch (entry.Type)
    {
    case HookType::VTable:
      UnregisterVTableHook(entry.VTableHook.VTable, entry.VTableHook.Index, entry.VTableHook.Original,
                           entry.VTableHook.Hook);
      break;
    case HookType::Trampoline:
      UnregisterTrampolineHook(entry.TrampolineHook.Address);
      break;
    }

    (*GetMap()).erase(handle);
  }

  void UnregisterVTableHook(void** vtable, std::size_t index, void* original, void* hook)
  {
    vtable[index] = original;
  }

  void Exit()
  {
    for (auto& hook : *GetMap())
    {
      log::Critical("Unhooking hook");
      UnregisterHook(hook.first);
    }

    ExitArch();
  }
}
