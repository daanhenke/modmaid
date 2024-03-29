#include <modmaid/core/init.hh>

#include <modmaid/core/logging.hh>
#include <modmaid/core/hooks.hh>

namespace modmaid
{
  InitComponent gFlagsForExit;

  void InitializeModMaid(InitComponent flags)
  {
    gFlagsForExit = 0;

    if (flags & init::Logging)
    {
      log::Initialize();
      gFlagsForExit |= init::Logging;

      if (flags & init::WindowsConsoleHost)
      {
        log::InitializeWindowsConsoleHost();
        gFlagsForExit |= init::WindowsConsoleHost;
      }
    }

    if (flags & init::Hooks)
    {
      hooks::Initialize();
      gFlagsForExit |= init::Hooks;
    }
  }

  void ExitModMaid()
  {
    if (gFlagsForExit & init::Hooks)
    {
      hooks::Exit();
    }

    if (gFlagsForExit & init::Logging)
    {
      if (gFlagsForExit & init::WindowsConsoleHost)
      {
        log::ExitWindowsConsoleHost();
      }

      log::Exit();
    }

    gFlagsForExit = 0;
  }
}
