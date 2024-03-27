#pragma once

#include <maid/memory.hh>

#include <cstdint>

namespace modmaid::hooks
{
  using HookHandle = std::size_t;
  using HookDescriptor = struct
  {
  };

  void Initialize();
  void Exit();

  HookHandle RegisterVTableHook(void* instance, std::size_t index, void** original, void* hook);
  HookHandle RegisterTrampolineHook(void* address, void** original, void* hook);

  HookHandle AllocateHookHandle();

  void Unhook(HookHandle hookDescriptor);
}
