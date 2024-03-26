#pragma once

#include <cstdint>
#include <string>

namespace modmaid::memory
{
  using MemoryProtection_t = std::uint32_t;
  namespace MemoryProtection
  {
    const MemoryProtection_t Read = 1;
    const MemoryProtection_t Write = 2;
    const MemoryProtection_t Execute = 4;

    const MemoryProtection_t ReadWrite = Read | Write;
    const MemoryProtection_t All = Read | Write | Execute;
  }

  using MemoryInformation = struct
  {
    std::uintptr_t BlockStart;
    std::uintptr_t BlockEnd;

    std::uint32_t MemoryProtection;

    std::string ExecutablePath;
  };

  void* GetExecutableBase(const char* executableName);

  template<typename T>
  T* TranslateOffset(const char* executableName, std::size_t offset)
  {
    return reinterpret_cast<T*>(
      reinterpret_cast<std::uintptr_t>(GetExecutableBase(executableName)) + offset
    );
  }

  void QueryMemory(const void* pointer, MemoryInformation* result);

  void CopyMemory(const void* original, void* destination, std::size_t size);

  MemoryProtection_t ReprotectMemory(void* pointer, std::size_t size, MemoryProtection_t newProtection);

  inline void* PageAlign(const void* pointer)
  {
    return reinterpret_cast<void*>(
      reinterpret_cast<std::uintptr_t>(pointer)
        & (~0xFFF)
    );
  }

  template <typename T>
  inline std::uint32_t ReprotectMemory(const T* pointer, std::size_t size, std::uint32_t newProtection)
  {
    return ReprotectMemory(reinterpret_cast<void*>(const_cast<T*>(pointer)), size, newProtection);
  }

  inline bool IsValidPointer(const void* pointer)
  {
    MemoryInformation info;
    QueryMemory(pointer, &info);
    return info.MemoryProtection & MemoryProtection::Read;
  }

  inline bool IsValidCodePointer(const void* pointer)
  {
    MemoryInformation info;
    QueryMemory(pointer, &info);
    return (info.MemoryProtection & MemoryProtection::Read)
      && (info.MemoryProtection & MemoryProtection::Execute);
  }
}
