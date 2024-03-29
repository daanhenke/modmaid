#include <modmaid/core.hh>

using namespace modmaid;

void (*DebugLog_Original)(void*, const char*) = nullptr;
void DebugLog_Hook(void* unk, const char* message)
{
  log::Trace("GAME: %s", message);
}

void OnLoad()
{
  InitializeModMaid(init::All | init::WindowsConsoleHost);

  log::Message("Hello world from %s", memory::GetExecutablePath(&OnLoad).c_str());
  log::Message("Finding debug_log...");

  auto debugLogAddress = memory::TranslateOffset<void*>("ffxiv_dx11.exe", 0x683ca0);
  log::Message("Found @ %llx", debugLogAddress);

  log::Message("Hooking!");
  hooks::RegisterTrampolineHook(debugLogAddress, reinterpret_cast<void**>(&DebugLog_Original), DebugLog_Hook);
}

void OnUnload()
{
  log::Message("Goodbye world!");
}

Entrypoint gEntrypoint(OnLoad, OnUnload);
