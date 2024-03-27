#include <maid/hooks.hh>
#include <maid/logging.hh>

#include <map>

namespace modmaid::hooks
{
  std::map<HookHandle, HookDescriptor> GetMap()
  {
    static std::map<HookHandle, HookDescriptor> map;
    return map;
  }

  HookHandle AllocateHookHandle()
  {
    static HookHandle nextHandle = 0;
    return nextHandle++;
  }

  HookHandle RegisterVTableHook(void* instance, std::size_t index, void** original, void* hook)
  {
    // Get the vtable and make it writable (it's in .rodata for sure)
    auto vtable = *static_cast<void***>(instance);
    memory::ReprotectMemory(vtable, (index + 1) * sizeof(void*), memory::MemoryProtection::All);

    // Hook
    *original = vtable[0];
    vtable[0] = hook;

    auto handle = AllocateHookHandle();
    // TODO: RETURN HANDLE FOR UNHOOKING
    return handle;
  }

  void Exit()
  {
    for (auto& hook : GetMap())
    {
      logging::Trace("Hook removed!");
    }
  }
}
