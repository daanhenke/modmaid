#pragma once

#include <maid/memory.hh>

#include <cstdint>

namespace modmaid::hooks
{
  using Hook_t = std::size_t;

  void Initialize();
  void Exit();

  template<typename T>
  Hook_t RegisterVTableHook(void* instance, std::size_t index, T* original, T hook)
  {
    // Get the vtable and make it writable (it's in .rodata for sure)
    auto vtable = *static_cast<void***>(instance);
    memory::ReprotectMemory(vtable, 64, memory::MemoryProtection::All);

    // Hook
    *original = reinterpret_cast<T>(vtable[0]);
    vtable[0] = reinterpret_cast<void*>(hook);

    // TODO: RETURN HANDLE FOR UNHOOKING
    return 0;
  }

  Hook_t RegisterTrampolineHook(void* address, void** original, void* hook);

  void Unhook(Hook_t hookDescriptor);
}
