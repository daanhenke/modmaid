#pragma once

#if OS_WINDOWS
#include <Windows.h>
#endif

namespace modmaid::gui
{
    enum class RenderingBackend
    {
        Invalid,
        AutoDetect,
        DirectX9,
        DirectX10,
        DirectX11,
        DirectX12,
    };

    using RenderCallback = void (*)();
    extern RenderCallback gRenderCallback;
    void Initialize(RenderCallback renderCallback, RenderingBackend renderingBackend = RenderingBackend::AutoDetect);
    void Exit();

#if OS_WINDOWS
    namespace win32
    {
        void Initialize(HWND windowHandle);
        void Exit();
    }

    namespace dx9
    {
        void Initialize();
        void Exit();
    }

    namespace dx10
    {
        void Initialize();
        void Exit();
    }

    namespace dx11
    {
        void Initialize();
        void Exit();
    }

    namespace dx12
    {
        void Initialize();
        void Exit();
    }
#endif
}