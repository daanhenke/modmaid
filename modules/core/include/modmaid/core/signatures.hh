#pragma once

#include <cstdlib>

namespace modmaid::signature
{
    void* FindInRange(void* base, std::size_t size, const char* pattern);
    void* FindInModule(const char* moduleName, const char* pattern);
}