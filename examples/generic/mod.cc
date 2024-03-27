#include <modmaid.hh>
using namespace modmaid;

#include <Windows.h>

void OnLoad()
{
  InitializeModMaid(init::Base | init::WindowsConsoleHost);
  logging::Trace("Hello %s", "world!");

  MessageBoxA(nullptr, "Ayy", "lmao", MB_OK);
  Unload();
}

void OnUnload()
{
  logging::Trace("Goodbye!");
}

Entrypoint gEntrypoint(OnLoad, OnUnload);
