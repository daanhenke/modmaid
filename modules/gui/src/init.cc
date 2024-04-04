#include <modmaid/gui/init.hh>
#include <modmaid/core/memory.hh>
#include <modmaid/core/logging.hh>

namespace modmaid::gui
{
    RenderingBackend DetectRenderingApi()
    {
        auto dx9Base = memory::GetExecutableBase("d3d9");
        if (dx9Base != nullptr)
        {
            log::Trace("Detected DirectX9");
            return RenderingBackend::DirectX9;
        }

        auto dx10Base = memory::GetExecutableBase("d3d10");
        if (dx10Base != nullptr)
        {
            log::Trace("Detected DirectX10");
            return RenderingBackend::DirectX10;
        }

        auto dx11Base = memory::GetExecutableBase("d3d11");
        if (dx11Base != nullptr)
        {
            log::Trace("Detected DirectX11");
            return RenderingBackend::DirectX11;
        }

        auto dx12Base = memory::GetExecutableBase("d3d12");
        if (dx12Base != nullptr)
        {
            log::Trace("Detected DirectX12");
            return RenderingBackend::DirectX12;
        }

        // TODO: PANIC
        return RenderingBackend::Invalid;
    }

    const char* RenderingBackendName(const RenderingBackend& backend)
    {
        switch (backend)
        {
            case RenderingBackend::DirectX9:
                return "DirectX9";

            case RenderingBackend::DirectX10:
                return "DirectX10";

            case RenderingBackend::DirectX11:
                return "DirectX11";

            case RenderingBackend::DirectX12:
                return "DirectX12";

            case RenderingBackend::AutoDetect:
            case RenderingBackend::Invalid:
                return "Invalid";

            default:
                return "Unsupported";
        }
    }

    RenderingBackend gRenderingBackend = RenderingBackend::Invalid;
    RenderCallback gRenderCallback = nullptr;
    void Initialize(RenderCallback renderCallback, RenderingBackend renderingBackend)
    {
        gRenderCallback = renderCallback;

        if (renderingBackend == RenderingBackend::AutoDetect)
        {
            renderingBackend = DetectRenderingApi();
        }

        switch (renderingBackend)
        {
            case RenderingBackend::DirectX11:
                dx11::Initialize();
                break;

            default:
                log::Panic("Unsupported rendering backend :(");
                break;
        }

        log::Message("Using rendering backend: %s", RenderingBackendName(renderingBackend));
        gRenderingBackend = renderingBackend;
    }

    void Exit()
    {
        switch (gRenderingBackend)
        {
            case RenderingBackend::DirectX11:
                dx11::Exit();
                break;

            default:
                break;
        }
    }
}