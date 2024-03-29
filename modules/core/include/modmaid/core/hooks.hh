#pragma once

#include <modmaid/core/memory.hh>

#include <cstdint>
#include <map>

namespace modmaid::hooks
{
  using HookHandle = std::size_t;

  enum class HookType
  {
    VTable,
    Trampoline
  };

  using HookDescriptor = struct
  {
    HookType Type;
    bool IsEnabled;

    union
    {
      struct
      {
        void** VTable;
        unsigned long long Index;
        void* Original;
        void* Hook;
      } VTableHook;

      struct
      {
        void* Address;
      } TrampolineHook;
    };
  };

  void Initialize();
  void ExitArch();
  void Exit();

  std::map<HookHandle, HookDescriptor>* GetMap();
  HookHandle AllocateHookHandle();

  HookHandle RegisterVTableHook(void** vtable, std::size_t index, void** original, void* hook);
  HookHandle RegisterVTableHookFromInstance(void* instance, std::size_t index, void** original, void* hook);
  HookHandle RegisterTrampolineHook(void* address, void** original, void* hook);

  void UnregisterHook(HookHandle handle);
  void UnregisterVTableHook(void** vtable, std::size_t index, void* original, void* hook);
  void UnregisterTrampolineHook(void* address);

  void Unhook(HookHandle hookDescriptor);
}
