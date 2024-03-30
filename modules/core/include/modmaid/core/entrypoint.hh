#pragma once

namespace modmaid
{
  using LoadMod_t = void(*)();
  using UnloadMod_t = void(*)();

  class Entrypoint
  {
  public:
    Entrypoint(LoadMod_t load, UnloadMod_t unload);

    LoadMod_t LoadMod;
    UnloadMod_t UnloadMod;
    bool IsModLoaded = false;
  };
}

extern modmaid::Entrypoint gEntrypoint;
