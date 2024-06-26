#include <modmaid/core.hh>
#include <modmaid/gui.hh>

#include <chrono>
#include <thread>

#include <Windows.h>

using namespace modmaid;
using namespace std::chrono_literals;

const char* gBanner[] = {
  "-----------",
  "Hello World",
  "-----------",
};

void RenderUserInterface()
{
  ImGui::Begin("Example mod");
  for (auto& line : gBanner)
  {
    ImGui::Text(line);
  }
  ImGui::End();
}

void (*DebugLog_Original)(void*, const char*) = nullptr;
void DebugLog_Hook(void* unk, const char* message)
{
  log::Trace("GAME: %s", message);
}

std::thread* gInputThread;
void InputThread()
{
  while (true)
  {
    if (GetAsyncKeyState(VK_INSERT) < 0)
    {
      log::Warning("Unloading!");
      break;
    }

    std::this_thread::sleep_for(200ms);
  }

  Unload();
}

void OnLoad()
{
  InitializeModMaid(init::All | init::WindowsConsoleHost);
  gui::Initialize(RenderUserInterface, gui::RenderingBackend::AutoDetect);

  log::Message("Hello world from %s", memory::GetExecutablePath(&OnLoad).c_str());
  log::Message("Finding debug_log...");

  auto debugLogAddress = memory::TranslateOffset<void*>("ffxiv_dx11.exe", 0x683ca0);

  if (debugLogAddress != nullptr)
  {
    log::Message("Found @ %llx", debugLogAddress);

    log::Message("Hooking!");
    hooks::RegisterTrampolineHook(debugLogAddress, reinterpret_cast<void**>(&DebugLog_Original), DebugLog_Hook);
  }

  gInputThread = new std::thread(InputThread);
  log::Message("Spawned input thread");
}

void OnUnload()
{
  gui::Exit();
  log::Message("Goodbye world!");
}

Entrypoint gEntrypoint(OnLoad, OnUnload);
