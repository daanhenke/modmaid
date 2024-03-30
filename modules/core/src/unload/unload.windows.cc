#include <modmaid/core/init.hh>
#include <modmaid/core/entrypoint.hh>

#include <Windows.h>

// Always resolves to own module base / handle
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace modmaid
{
  DWORD UnloadCallback(LPVOID _)
  {
    gEntrypoint.UnloadMod();
    gEntrypoint.IsModLoaded = false;

    Sleep(1000);
    ExitModMaid();
    Sleep(1000);

    FreeLibraryAndExitThread(reinterpret_cast<HINSTANCE>(&__ImageBase), 0);
  }

  void Unload()
  {
    static bool firstCall = true;

    if (!firstCall)
    {
      return;
    }

    firstCall = false;

    CreateThread(
      nullptr,
      0,
      reinterpret_cast<LPTHREAD_START_ROUTINE>(UnloadCallback),
      nullptr,
      0,
      nullptr
    );
  }
}
