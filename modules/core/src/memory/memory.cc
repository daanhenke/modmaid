#include <modmaid/core/memory.hh>

#include <cstring>

namespace modmaid::memory
{
  void CopyMemory(const void* original, void* destination, std::size_t size)
  {
    std::memcpy(destination, original, size);
  }
}
