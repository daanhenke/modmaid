#include <dxcommon/dxcommon.hh>
#include <modmaid/core/logging.hh>

namespace modmaid::gui::dx
{
    WNDCLASSEXA gWindowClass;
    HWND CreateDummyWindow()
    {
        gWindowClass.lpszClassName = "dummy";
        gWindowClass.cbSize = sizeof(gWindowClass);
        gWindowClass.style = CS_HREDRAW | CS_VREDRAW;
        gWindowClass.lpfnWndProc = DefWindowProcA;
        gWindowClass.cbClsExtra = 0;
        gWindowClass.cbWndExtra = 0;
        gWindowClass.hInstance = GetModuleHandleA(nullptr);
        gWindowClass.hIcon = nullptr;
        gWindowClass.hIconSm = nullptr;
        gWindowClass.hbrBackground = nullptr;
        gWindowClass.lpszMenuName = nullptr;

        RegisterClassExA(&gWindowClass);

        log::Trace("Creating dummy directx window");
        return CreateWindowA(gWindowClass.lpszClassName, "dummy dx window",
            WS_OVERLAPPEDWINDOW, 0, 0, 100, 100,
            nullptr, nullptr, gWindowClass.hInstance, nullptr
        );
    }

    void DestroyDummyWindow(HWND handle)
    {
        DestroyWindow(handle);
        UnregisterClassA(gWindowClass.lpszClassName, gWindowClass.hInstance);
    }
}