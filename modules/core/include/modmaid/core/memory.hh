#pragma once

#include <cstdint>
#include <string>

namespace modmaid::memory
{
  using MemoryProtection_t = std::uint32_t;
  namespace MemoryProtection
  {
    constexpr MemoryProtection_t Read = 1;
    constexpr MemoryProtection_t Write = 2;
    constexpr MemoryProtection_t Execute = 4;

    constexpr MemoryProtection_t ReadWrite = Read | Write;
    constexpr MemoryProtection_t All = Read | Write | Execute;
  }

  using MemoryInformation = struct
  {
    std::uintptr_t BlockStart;
    std::uintptr_t BlockEnd;

    std::uint32_t MemoryProtection;

    std::string ExecutablePath;
  };

  void* GetExecutableBase(const char* executableName);
  std::size_t GetExecutableSize(void* executableBase);
  std::string GetExecutablePath(void* pointerIntoExecutable);

  template<typename T>
  T* TranslateOffset(const char* executableName, const std::size_t offset)
  {
    auto base = reinterpret_cast<std::uintptr_t>(GetExecutableBase(executableName));
    if (base == 0) return nullptr;

    return reinterpret_cast<T*>(
      base + offset
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
