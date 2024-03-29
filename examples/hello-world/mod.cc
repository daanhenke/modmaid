#include <modmaid/core.hh>

using namespace modmaid;

void OnLoad()
{
  InitializeModMaid(init::All | init::WindowsConsoleHost);

  log::Message("Hello world from %s", memory::GetExecutablePath(&OnLoad).c_str());

  Unload();
}

void OnUnload()
{
  log::Message("Goodbye world!");
}

Entrypoint gEntrypoint(OnLoad, OnUnload);
