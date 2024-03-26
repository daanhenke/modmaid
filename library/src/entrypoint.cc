#include <maid/entrypoint.hh>

namespace modmaid
{
  Entrypoint::Entrypoint(LoadMod_t load, UnloadMod_t unload)
  {
    _load = load;
    _unload = unload;

    if (! _isLoaded && _load != nullptr)
    {
      _load();
    }
  }

  Entrypoint::~Entrypoint()
  {
    if (_isLoaded && _unload != nullptr)
    {
      _unload();
    }
  }
}
