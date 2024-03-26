#include <maid/memory.hh>
#include <maid/logging.hh>

#include <cstdint>
#include <fstream>
#include <sstream>

#include <sys/mman.h>

namespace modmaid::memory
{
  void QueryMemory(const void* pointer, MemoryInformation* info)
  {
    auto fileStream = std::ifstream("/proc/self/maps");
    auto numericPointer = reinterpret_cast<unsigned long long>(pointer);

    std::string line;
    while (std::getline(fileStream, line))
    {
      auto lineStream = std::istringstream(line);

      unsigned long long startAddress;
      unsigned long long endAddress;
      char access[4];
      unsigned long long fileOffset;
      unsigned int unk1;
      unsigned int unk2;
      int unk3;

      std::sscanf(line.c_str(), "%llx-%llx %c%c%c%c %llx %x:%x %d", &startAddress, &endAddress, &access[0], &access[1], &access[2], &access[3], &fileOffset, &unk1, &unk2, &unk3);
      if (startAddress <= numericPointer && endAddress > numericPointer)
      {
        info->BlockStart = static_cast<std::uintptr_t>(startAddress);
        info->BlockEnd = static_cast<std::uintptr_t>(endAddress);

        std::uint32_t protection = 0;
        if (access[0] == 'r') protection |= MemoryProtection::Read;
        if (access[1] == 'w') protection |= MemoryProtection::Write;
        if (access[2] == 'x') protection |= MemoryProtection::Execute;
        info->MemoryProtection = protection;

        auto nameStartIndex = line.rfind(' ');
        if (nameStartIndex != std::string::npos)
        {
          info->ExecutablePath = line.substr(nameStartIndex + 1);
        }
        break;
      }
    }
  }

  std::uint32_t ReprotectMemory(void* pointer, std::size_t size, std::uint32_t newProtection)
  {
    auto unixNew = 0;
    if (newProtection & MemoryProtection::Read) unixNew |= PROT_READ;
    if (newProtection & MemoryProtection::Write) unixNew |= PROT_WRITE;
    if (newProtection & MemoryProtection::Execute) unixNew |= PROT_EXEC;

    auto alignedPointer = PageAlign(pointer);
    auto sizeDiffDueToAlignment = reinterpret_cast<std::uintptr_t>(pointer) - reinterpret_cast<std::uintptr_t>(alignedPointer);

    MemoryInformation oldInfo;
    QueryMemory(alignedPointer, &oldInfo);
    mprotect(PageAlign(pointer), size + sizeDiffDueToAlignment, unixNew);

    return oldInfo.MemoryProtection;
  }
}
