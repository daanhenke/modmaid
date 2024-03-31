#include <modmaid/core/entrypoint.hh>

#ifdef OS_WINDOWS
#include <Windows.h>
#endif

namespace modmaid
{
  DWORD InitThread(LPVOID callback)
  {
    auto load = reinterpret_cast<LoadMod_t>(callback);
    load();
    return 0;
  }

  Entrypoint::Entrypoint(LoadMod_t load, UnloadMod_t unload)
  {
    LoadMod = load;
    UnloadMod = unload;

    if (LoadMod != nullptr)
    {
#ifdef OS_WINDOWS
      CreateThread(nullptr, 0, InitThread, LoadMod, 0, nullptr);
#endif
      IsModLoaded = true;
    }
  }
}
