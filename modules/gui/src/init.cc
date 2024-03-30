#include <modmaid/gui/init.hh>
#include <modmaid/core/memory.hh>
#include <modmaid/core/logging.hh>

namespace modmaid::gui
{
    void DetectRenderingApi()
    {
        auto dx9Base = memory::GetExecutableBase("d3d9");
        if (dx9Base != nullptr)
        {
            log::Trace("Detected DirectX9");
        }

        auto dx10Base = memory::GetExecutableBase("d3d10");
        if (dx10Base != nullptr)
        {
            log::Trace("Detected DirectX10");
        }

        auto dx11Base = memory::GetExecutableBase("d3d11");
        if (dx11Base != nullptr)
        {
            log::Trace("Detected DirectX11");
        }

        auto dx12Base = memory::GetExecutableBase("d3d12");
        if (dx12Base != nullptr)
        {
            log::Trace("Detected DirectX12");
        }
    }

    void Initialize()
    {
        DetectRenderingApi();
    }

    void Exit()
    {

    }
}