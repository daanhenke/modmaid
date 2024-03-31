#pragma once

#include <modmaid/core/logging.hh>
#include <dxcommon/dxcommon.hh>

#include <dxgi.h>
#include <d3d11.h>

#define GetDX11Export(name) \
    dx::GetExport<decltype(name)*>(D3D11, #name)

namespace modmaid::gui::dx11
{
    void Initialize()
    {
        auto windowHandle = dx::CreateDummyWindow();
        log::Trace("Window handle: %llx", windowHandle);

        auto D3D11 = GetModuleHandleA("d3d11");
        auto createDeviceAndSwapChain = GetDX11Export(D3D11CreateDeviceAndSwapChain);

        D3D_FEATURE_LEVEL featureLevel;
        constexpr D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        DXGI_RATIONAL refreshRate;
        refreshRate.Numerator = 60;
        refreshRate.Denominator = 1;

        DXGI_MODE_DESC bufferDesc;
        bufferDesc.Width = 100;
        bufferDesc.Height = 100;
        bufferDesc.RefreshRate = refreshRate;
        bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        DXGI_SAMPLE_DESC sampleDesc;
        sampleDesc.Count = 1;
        sampleDesc.Quality = 0;

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        swapChainDesc.BufferDesc = bufferDesc;
        swapChainDesc.SampleDesc = sampleDesc;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.OutputWindow = windowHandle;
        swapChainDesc.Windowed = 1;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        IDXGISwapChain* swapChain;
        ID3D11Device* device;
        ID3D11DeviceContext* deviceContext;

        log::Trace("Creating dx11 swapchain...");
        auto createResult = createDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
            featureLevels, 2,
            D3D11_SDK_VERSION, &swapChainDesc,
            &swapChain, &device, &featureLevel, &deviceContext
        );

        if (createResult >= 0)
        {
            auto swapChainVtable = dx::GetVTable(swapChain);
            log::Trace("Swapchain vtable @ %llx", swapChainVtable);
            auto deviceVtable = dx::GetVTable(device);
            log::Trace("Device vtable @ %llx", deviceVtable);
            auto deviceContextVtable = dx::GetVTable(deviceContext);
            log::Trace("Context vtable @ %llx", deviceContextVtable);

            swapChain->Release();
            device->Release();
            deviceContext->Release();
        }
        else
        {
            log::Critical("Failed to create dx11 swapchain: %llx", createResult);
        }

        dx::DestroyDummyWindow(windowHandle);
    }

    void Exit()
    {

    }
}