#include <maid/entrypoint.hh>

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

  Entrypoint::~Entrypoint()
  {
    if (UnloadMod != nullptr && IsModLoaded)
    {
      UnloadMod();
      IsModLoaded = false;
    }
  }
}
