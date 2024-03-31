#pragma once

#include <Windows.h>

namespace modmaid::gui::dx
{
    HWND CreateDummyWindow();
    void DestroyDummyWindow(HWND handle);

    template <typename T>
    T GetExport(HMODULE module, const char* name)
    {
        return reinterpret_cast<T>(GetProcAddress(module, name));
    }

    inline void** GetVTable(void* instance)
    {
        return *static_cast<void***>(instance);
    }
}