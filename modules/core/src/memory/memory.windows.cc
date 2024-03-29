#include <modmaid/core/memory.hh>

#include <Windows.h>

namespace modmaid::memory
{
  void QueryMemory(const void* pointer, MemoryInformation* info)
  {
    MEMORY_BASIC_INFORMATION buffer;
    VirtualQuery(pointer, &buffer, sizeof(buffer));

    info->BlockStart = reinterpret_cast<std::uintptr_t>(buffer.AllocationBase);
    info->BlockEnd = info->BlockStart + buffer.RegionSize;

    MemoryProtection_t protection = 0;
    switch (buffer.Protect)
    {
    case PAGE_READONLY: protection = MemoryProtection::Read;
      break;
    case PAGE_READWRITE: protection = MemoryProtection::Read | MemoryProtection::Write;
      break;
    case PAGE_EXECUTE_READ: protection = MemoryProtection::Read | MemoryProtection::Execute;
      break;
    case PAGE_EXECUTE_READWRITE: protection = MemoryProtection::Read | MemoryProtection::Write |
        MemoryProtection::Execute;
      break;
    }
    info->MemoryProtection = protection;
  }

  std::uint32_t ReprotectMemory(void* pointer, std::size_t size, std::uint32_t newProtection)
  {
    auto win32New = 0;
    if ((newProtection & MemoryProtection::Write) && (newProtection & MemoryProtection::Execute)) win32New =
      PAGE_EXECUTE_READWRITE;
    else if (newProtection & MemoryProtection::Write) win32New = PAGE_READWRITE;
    else if (newProtection & MemoryProtection::Execute) win32New = PAGE_EXECUTE_READ;

    MemoryInformation oldInfo;
    QueryMemory(pointer, &oldInfo);

    DWORD oldProtect;
    VirtualProtect(pointer, size, win32New, &oldProtect);

    return oldInfo.MemoryProtection;
  }

  void* GetExecutableBase(const char* executableName)
  {
    return GetModuleHandleA(executableName);
  }

  std::string GetExecutablePath(void* pointerIntoExecutable)
  {
    auto alignedPointer = reinterpret_cast<std::uintptr_t>(pointerIntoExecutable) & (~0xFFF);

    IMAGE_DOS_HEADER* dosHeader;
    do
    {
      dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(alignedPointer);
      alignedPointer -= 0x1000;
    }
    while (dosHeader->e_magic != IMAGE_DOS_SIGNATURE);

    char buffer[MAX_PATH];
    GetModuleFileNameA(reinterpret_cast<HMODULE>(dosHeader), buffer, MAX_PATH);

    return { buffer };
  }
}
