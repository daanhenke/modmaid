#pragma once


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

    void Initialize(RenderingBackend renderingBackend = RenderingBackend::AutoDetect);
    void Exit();

#if OS_WINDOWS
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