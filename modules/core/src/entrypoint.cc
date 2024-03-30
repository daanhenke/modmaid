#include <modmaid/core/entrypoint.hh>
#include <modmaid/core/init.hh>

namespace modmaid
{
  Entrypoint::Entrypoint(LoadMod_t load, UnloadMod_t unload)
  {
    LoadMod = load;
    UnloadMod = unload;

    if (LoadMod != nullptr)
    {
      LoadMod();
      IsModLoaded = true;
    }
  }
}
