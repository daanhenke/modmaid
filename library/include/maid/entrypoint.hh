#pragma once

namespace modmaid
{
  using LoadMod_t = void(*)();
  using UnloadMod_t = void(*)();

  class Entrypoint
  {
  public:
    Entrypoint(LoadMod_t load, UnloadMod_t unload);
    ~Entrypoint();

  private:
    LoadMod_t _load;
    UnloadMod_t _unload;
    bool _isLoaded = false;
  };
}

extern modmaid::Entrypoint gEntrypoint;
