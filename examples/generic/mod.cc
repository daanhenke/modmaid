#include <modmaid.hh>

using namespace modmaid;

void OnLoad()
{
  modmaid::Initialize();
  logging::Trace("Hello %s", "world!");
}

void OnUnload()
{
  modmaid::Exit();
}

modmaid::Entrypoint gEntrypoint(OnLoad, OnUnload);
