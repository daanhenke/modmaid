#pragma once

#include <modmaid/core/logging.hh>
#include <modmaid/core/hooks.hh>
#include <dxcommon/dxcommon.hh>

#include <modmaid/gui/init.hh>

#include <dxgi.h>
#include <d3d11.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <filesystem>

#define GetDX11Export(name) \
    dx::GetExport<decltype(name)*>(D3D11, #name)

namespace modmaid::gui::dx11
{
    ID3D11RenderTargetView* gRenderTarget = nullptr;
    ID3D11Device* gDevice = nullptr;
    ID3D11DeviceContext* gDeviceContext = nullptr;

    HRESULT (__fastcall *PresentOriginal)(IDXGISwapChain*, UINT, UINT) = nullptr;
    HRESULT __fastcall PresentHook(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags)
    {
        static bool firstRun = true;
        if (firstRun)
        {
            log::Critical("DX11 Setup!");
            DXGI_SWAP_CHAIN_DESC desc;
            pSwapChain->GetDesc(&desc);

            ID3D11Device* device;
            pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));

            ID3D11DeviceContext* context;
            device->GetImmediateContext(&context);

            gDevice = device;
            gDeviceContext = context;

            ID3D11Texture2D* buffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));
            device->CreateRenderTargetView(buffer, nullptr, &gRenderTarget);
            buffer->Release();

            ImGui::CreateContext();

            auto io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

            ImGui::StyleColorsDark();

            win32::Initialize(desc.OutputWindow);
            ImGui_ImplWin32_Init(desc.OutputWindow);
            ImGui_ImplDX11_Init(device, context);

            firstRun = false;
        }

        ImGui_ImplWin32_NewFrame();
        ImGui_ImplDX11_NewFrame();
        ImGui::NewFrame();

        if (gRenderCallback != nullptr)
        {
            gRenderCallback();
        }

        ImGui::EndFrame();
        ImGui::Render();

        gDeviceContext->OMSetRenderTargets(1, &gRenderTarget, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        return PresentOriginal(pSwapChain, syncInterval, flags);
    }
    hooks::HookHandle gPresentHandle;

    HRESULT (__stdcall* ResizeBuffersOriginal)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT) = nullptr;
    HRESULT __stdcall ResizeBuffersHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT format, UINT flags)
    {
        log::Critical("DX11 Resize!");
        if (gRenderTarget)
        {
            gDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
            gRenderTarget->Release();
        }

        ImGui_ImplDX11_Shutdown();
        auto result = ResizeBuffersOriginal(swapChain, bufferCount, width, height, format, flags);

        ID3D11Texture2D* buffer;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));

        gDevice->CreateRenderTargetView(buffer, nullptr, &gRenderTarget);
        buffer->Release();

        gDeviceContext->OMSetRenderTargets(1, &gRenderTarget, nullptr);

        D3D11_VIEWPORT vp;
        vp.Width = width;
        vp.Height = height;
        vp.MinDepth = 0.;
        vp.MaxDepth = 1.;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        gDeviceContext->RSSetViewports(1, &vp);

        ImGui_ImplDX11_Init(gDevice, gDeviceContext);

        return result;
    }
    hooks::HookHandle gResizeBuffersHandle;

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

            gPresentHandle = hooks::RegisterVTableHook(swapChainVtable, 8, reinterpret_cast<void**>(&PresentOriginal), PresentHook);
            gResizeBuffersHandle = hooks::RegisterVTableHook(swapChainVtable, 13, reinterpret_cast<void**>(&ResizeBuffersOriginal), ResizeBuffersHook);

            swapChain->Release();
            device->Release();
        }
        else
        {
            log::Critical("Failed to create dx11 swapchain: %llx", createResult);
        }

        dx::DestroyDummyWindow(windowHandle);
    }

    void Exit()
    {
        ImGui_ImplDX11_Shutdown();
        win32::Exit();
        ImGui_ImplWin32_Shutdown();
        log::Message("Exiting DirectX11");
        hooks::UnregisterHook(gResizeBuffersHandle);
        hooks::UnregisterHook(gPresentHandle);
    }
}