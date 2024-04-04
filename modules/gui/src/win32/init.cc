#pragma once

#include <modmaid/gui/init.hh>

#include <imgui.h>
#include <imgui_impl_win32.h>

#define GetDX11Export(name) \
    dx::GetExport<decltype(name)*>(D3D11, #name)


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace modmaid::gui::win32
{
    WNDPROC gOriginalWndProc = nullptr;
    HWND gWindowHandle = nullptr;

    LRESULT CALLBACK WindowProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) > 0)
            return 1;

        return CallWindowProcA(gOriginalWndProc, hWnd, uMsg, wParam, lParam);
    }

    void Initialize(HWND windowHandle)
    {
        gWindowHandle = windowHandle;
        gOriginalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcHook)));
    }

    void Exit()
    {
        SetWindowLongPtrA(gWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(gOriginalWndProc));
    }
}